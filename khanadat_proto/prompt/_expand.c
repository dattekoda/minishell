#include <stdio.h>
#include "ast.h"
#include "expand.h"
#include "status.h"
#include "libft.h"
#include "minishell_define.h"
#include "minishell_lib.h"
#include "minishell_err.h"

typedef enum s_WordKind
{
	WD_DOLLAR,
	WD_SINGLE,
	WD_DOUBLE,
	WD_DDOLLAR, // inside double dollar
	WD_OUTSIDE,
	WD_EOF
}	t_WordKind;

typedef struct s_dollar
{
	char			*value;
	size_t			value_len;
	t_WordKind		wkind;
	struct s_dollar	*next;
}	t_dollar;

// found var then return value
// else return NULL
// push forward var
char	*mini_getenv(char **var, t_mini *mini)
{
	size_t	len;
	size_t	i;
	char	*chr;

	i = 0;
	chr = *var;
	while (**var && !ft_strchr("\'\"$", **var))
		(*var)++;
	len = *var - chr;
	while (i < mini->envp_len)
	{
		if (!ft_strncmp(chr, mini->envp[i], len) \
		&& mini->envp[i][len] == '=')
			break ;
		i++;
	}
	if (!mini->envp[i])
		return (NULL);
	chr = ft_strchr(mini->envp[i], '=');
	if (chr)
		return (chr + 1);
	return (NULL);
}

void	free_dollar(t_dollar *head)
{
	t_dollar	*tmp;

	while (head)
	{
		tmp = (head)->next;
		free(head);
		head = tmp;
	}
}

// set the second arg, **word be '$' mark
// skip word and get expanded value
// return stack char *.
// if couldn't find any value then
// set value as "\0"
t_dollar	*add_dollar(t_dollar *cur, t_mini *mini, \
	char **word, t_WordKind kind)
{
	char		*value;
	t_dollar	*new;

	(*word)++;
	new = ft_calloc(1, sizeof(t_dollar));
	if (!new)
		return (NULL);
	cur->next = new;
	new->wkind = kind;
	if (**word == '?')
	{
		new->value = mini->status;
		new->value_len = ft_strlen(new->value);
		return ((*word)++, new);
	}
	value = mini_getenv(word, mini);
	if (!value)
		new->value = &(mini->status[3]);
	else
		new->value = value;
	new->value_len = ft_strlen(new->value);
	return (new);
}

t_dollar	*add_single(t_dollar *cur, char **word)
{
	t_dollar	*new;

	new = ft_calloc(1, sizeof(t_dollar));
	if (!new)
		return (NULL);
	cur->next = new;
	new->value = *word + 1;
	new->wkind = WD_SINGLE;
	*word = ft_strchr(new->value, '\'') + 1;
	new->value_len = (size_t)(*word - 1 - new->value);
	return (new);
}

t_dollar	*add_double(t_dollar *cur, char **word)
{
	t_dollar	*new;

	new = ft_calloc(1, sizeof(t_dollar));
	if (!new)
		return (NULL);
	cur->next = new;
	new->wkind = WD_DOUBLE;
	new->value = *word + (**word == '\"');
	new->wkind = WD_DOUBLE;
	while (**word && **word != '\"' \
	&& **word != '$')
	{
		(*word)++;
		new->value_len++;
	}
	return (new);
}

t_dollar	*classify_double(t_dollar **cur, t_mini *mini, char **tmp)
{
	(*tmp)++;
	while (**tmp && **tmp != '\"' && *cur)
	{
		if (**tmp == '$')
		{
			*cur = add_dollar(*cur, mini, tmp, WD_DDOLLAR);
			continue ;
		}
		*cur = add_double(*cur, tmp);
	}
	if (**tmp == '\"')
		(*tmp)++;
	return (*cur);
}

t_dollar	*add_outside(t_dollar *cur, char **word)
{
	t_dollar	*new;

	new = ft_calloc(1, sizeof(t_dollar));
	if (!new)
		return (NULL);
	cur->next = new;
	new->wkind = WD_OUTSIDE;
	new->value = *word;
	while (**word && !ft_strchr("\'\"$", **word))
	{
		(*word)++;
		new->value_len++;
	}
	return (new);
}

void	classify_dollar(t_dollar **cur, t_mini *mini, char **tmp)
{
	while (**tmp && *cur)
	{
		if (**tmp == '$')
		{
			*cur = add_dollar(*cur, mini, tmp, WD_DOLLAR);
			continue ;
		}
		if (**tmp == '\'')
		{
			*cur = add_single(*cur, tmp);
			continue ;
		}
		if (**tmp == '\"')
		{
			*cur = classify_double(cur, mini, tmp);
			continue ;
		}
		*cur = add_outside(*cur, tmp);
	}
}

int	search_dollar(t_word *word, t_mini *mini, t_dollar **dol)
{
	char		*tmp;
	t_dollar	head;
	t_dollar	*cur;

	ft_bzero(&head, sizeof(t_dollar));
	cur = &head;
	tmp = word->word;
	classify_dollar(&cur, mini, &tmp);
	if (!cur)
		return (free_dollar(head.next), ERR);
	*dol = head.next;
	return (SUCCESS);
}

void	dol_checker(t_dollar *dol)
{
	while (dol)
	{
		fprintf(stderr, "val:	%s\n", dol->value);
		fprintf(stderr, "len:	%zu\n", dol->value_len);
		if (dol->wkind == WD_SINGLE)
			fprintf(stderr, "kind:	%s\n", "single");
		else if (dol->wkind == WD_DOUBLE)
			fprintf(stderr, "kind:	%s\n", "double");
		else if (dol->wkind == WD_OUTSIDE)
			fprintf(stderr, "kind:	%s\n", "outside");
		else if (dol->wkind == WD_DOLLAR)
			fprintf(stderr, "kind:	%s\n", "dollar");
		else if (dol->wkind == WD_DDOLLAR)
			fprintf(stderr, "kind:	%s\n", "double dollar");
		fprintf(stderr, "\n");
		dol = dol->next;
	}
}

// need add t_word then true 
// else return false
bool	need_split(t_dollar **dol, size_t *len)
{
	size_t	i;

	while (*len == 0 && ft_isspace(*((*dol)->value)))
		(*dol)->value = (*dol)->value + 1;
	i = 0;
	while ((*dol)->value[i] && !ft_isspace((*dol)->value[i]))
		i++;
	*len += i;
	// 最後まで到達したらt_wordを作る必要なし。
	if ((*dol)->value[i] == '\0')
		return (false);
	return (true);
}

size_t	count_word_len(t_dollar **dol)
{
	size_t	len;

	len = 0;
	while ((*dol))
	{
		if ((*dol)->wkind == WD_DOLLAR \
		&& need_split(dol, &len))
			return (len);
		else if ((*dol)->wkind != WD_DOLLAR)
			len += (*dol)->value_len;
		(*dol) = (*dol)->next;
	}
	return (len);
}

void	set_word_word(t_word *new, t_dollar *dol_tail)
{
	size_t		i;

	i = 0;
	while (dol_tail)
	{
		if (dol_tail->wkind == WD_DOLLAR)
		{
			ft_strlcat(new->word, dol_tail->value, new->word_len + 1);
			while (*dol_tail->value && !ft_isspace(*(dol_tail->value)))
				(dol_tail->value) = (i++, dol_tail->value + 1);
			if (new->word[new->word_len - 1])
				break ;
		}
		else
		{
			ft_memmove(new->word + i, dol_tail->value, dol_tail->value_len);
			i += dol_tail->value_len;
		}
		dol_tail = dol_tail->next;
	}
}

t_word	*add_new_word(t_word *cur, t_dollar **dol)
{
	t_word		*new;
	t_dollar	*dol_tail;

	new = ft_calloc(1, sizeof(t_word));
	if (!new)
		return (NULL);
	dol_tail = *dol;
	new->word_len = count_word_len(dol);
	new->word = ft_calloc(new->word_len + 1, sizeof(char));
	cur->next = new;
	if (!new->word)
		return (free(new), NULL);
	set_word_word(new, dol_tail);
	return (new);
}

int	set_new_word(t_word **new, t_word *before, t_mini *mini)
{
	t_word		head;
	t_word		*cur;
	t_dollar	*dol;
	t_dollar	*dol_head;

	ft_bzero(&head, sizeof(t_word));
	cur = &head;
	while (before && cur)
	{
		if (search_dollar(before, mini, &dol))
			return (free_word(head.next), ERR);
		dol_head = dol;
		while (dol && cur)
			cur = add_new_word(cur, &dol);
		before = before->next;
		free_dollar(dol_head);
	}
	if (!new)
		return (free_word(head.next), ERR);
	*new = head.next;
	return (SUCCESS);
}

// if system call err, exit
int	expand_word(t_node *node, t_mini *mini)
{
	t_word	*before;
	t_word	*new;

	before = node->word;
	if (set_new_word(&new, before, mini))
		return (ERR);
	free_word(node->word);
	node->word = new;
	return (SUCCESS);
}

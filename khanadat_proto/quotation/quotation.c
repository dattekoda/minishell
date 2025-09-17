#include <readline/readline.h>
#include <readline/history.h>

#include "libft.h"
#include "status.h"
#include "minishell_err.h"

// free(*new) and joined *new and buffer pointer to *new
// and initialize buffer
int	safe_join(char **new, char *buffer)
{
	char	*tmp;

	tmp = ft_strjoin(*new, buffer);
	free(*new);
	if (!tmp)
		return (err_system_call("malloc"), ERR);
	*new = tmp;
	return (SUCCESS);
}

// still need to fix in order to get $?
int	dollar_join(char **new, char **before)
{
	char	*dollar_name;
	char	*env_var;

	dollar_name = ++(*before);
	// if (*dollar_name == '?')
	while (**before && **before != '\'' && **before != '\"' \
		&& !ft_isspace(**before))
		(*before)++;
	if (dollar_name == (*before) && safe_join(new, "$"))
		return (ERR);
	dollar_name = ft_strndup(dollar_name, *before - dollar_name);
	if (!dollar_name)
		return (free(*new), err_system_call("malloc"), ERR);
	env_var = getenv(dollar_name);
	free(dollar_name);
	if (!env_var)
		return (SUCCESS);
	if (safe_join(new, env_var))
		return (ERR);
	return (SUCCESS);
}

int	store_double(char **before, char **new, char *buffer, size_t *i)
{
	char	*chr;

	chr = ft_strchr(*before + 1, **before);
	if (!chr)
		return (free(*new), put_err(**before), ERR);
	(*before)++;
	while (*before < chr)
	{
		while (*before < chr && **before != '$' && *i < BUFFER_SIZE)
			buffer[(*i)++] = *((*before)++);
		if (safe_join(new, buffer))
			return (ERR);
		ft_bzero(buffer, BUFFER_SIZE + 1);
		(*i) = 0;
		if (**before == '$' && dollar_join(new, before))
			return (ERR);
	}
	*before = chr + 1;
	return (SUCCESS);
}

int	store_single(char **before, char **new, char *buffer, size_t *i)
{
	char	*chr;

	chr = ft_strchr(*before + 1, **before);
	if (!chr)
		return (free(*new), put_err(**before), ERR);
	(*before)++;
	while (*before < chr)
	{
		while (*before < chr && *i < BUFFER_SIZE)
			buffer[(*i)++] = *((*before)++);
		if (safe_join(new, buffer))
			return (ERR);
		ft_bzero(buffer, BUFFER_SIZE + 1);
		(*i) = 0;
	}
	*before = chr + 1;
	return (SUCCESS);
}

int	store_outside(char **before, char **new, char *buffer, size_t *i)
{
	while (**before && **before != '\'' && **before != '\"')
	{
		while (**before && **before != '\'' \
			&& **before != '\"'&& **before != '$' \
			&&*i < BUFFER_SIZE)
			buffer[(*i)++] = *((*before)++);
		if (safe_join(new, buffer))
			return (ERR);
		ft_bzero(buffer, BUFFER_SIZE + 1);
		(*i) = 0;
		if (**before == '$' && dollar_join(new, before))
			return (ERR);
	}
	return (SUCCESS);
}

int	store_new(char *before, char **new)
{
	char	buffer[BUFFER_SIZE + 1];
	size_t	i;

	i = 0;
	ft_bzero(buffer, BUFFER_SIZE + 1);
	while (*before)
	{
		if (*before == '\"')
		{
			if (store_double(&before, new, buffer, &i))
				return (ERR);
			continue ;
		}
		if (*before == '\'')
		{
			if (store_single(&before, new, buffer, &i))
				return (ERR);
			continue ;
		}
		if (store_outside(&before, new, buffer, &i))
			return (ERR);
	}
	if (i && safe_join(new, buffer))
		return (ERR);
	return (SUCCESS);
}

// 'hello' > hello h'ell'o"$HOME" > hello/home/khanadat
int	expand_quotation(char *before, char **new)
{
	if (BUFFER_SIZE < 1)
		return (ft_putendl_fd("Error: set the appropriate BUFFER_SIZE.", \
			STDERR_FILENO), ERR);
	*new = ft_strdup("");
	if (!*new)
		return (err_system_call("malloc"), ERR);
	if (store_new(before, new))
		return (ERR);
	return (SUCCESS);
}

#include <stdio.h>
int	main(void)
{
	char	*expanded;
	char	*line;

	while (1)
	{
		line = readline("$ ");
		if (!line)
			break;
		add_history(line);
		if (expand_quotation(line, &expanded))
			return (free(line), 1);
		free(line);
		printf("%s\n", expanded);
		free(expanded);
	}
	rl_clear_history();
	return 0;
}

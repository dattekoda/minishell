#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "libft.h"
#include "status.h"
#include "minishell_err.h"
#include "minishell_lib.h"
#include "expand.h"

// still need to fix in order to get $?
int	dollar_join(char **new, char **before)
{
	char	*dollar_name;
	char	*env_var;

	dollar_name = ++(*before);
	if (*dollar_name == '?')
	{
		env_var = ft_itoa(received_sig);
		safe_join(new, env_var);
		return (++(*before), free(env_var), SUCCESS);
	}
	while (**before && **before != '\'' && **before != '\"' \
		&& **before != '$' && !ft_isspace(**before))
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
		return (free(*new), put_syntax_err(**before), ERR);
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
		return (free(*new), put_syntax_err(**before), ERR);
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

// syntax err return 2
// system call err return -1
// success return 0
// 'hello' > hello h'ell'o"$HOME" > hello/home/khanadat
int	expand_quotation(char *before, char **new)
{
	if (BUFFER_SIZE < 1)
		return (ft_putendl_fd("Error: set the appropriate BUFFER_SIZE.", \
			STDERR_FILENO), ERR);
	if (valid_quote(before))
			return (SYNTAX_ERR);
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
	int		status;

	access_program_name("minishell");
	expanded = NULL;
	line = NULL;
	while (1)
	{
		line = readline("$ ");
		if (!line)
			break;
		add_history(line);
		ft_putendl_fd("hello", 2);
		status = expand_quotation(line, &expanded);
		safe_free((void **)&line);
		if (status < 0)
			return (rl_clear_history(), \
			access_program_name("free_program_name"), 1);
		if (status == SYNTAX_ERR)
			continue ;
		if (expanded)
			printf("%s\n", expanded);
		safe_free((void **)&expanded);
	}
	rl_clear_history();
	access_program_name("free_program_name");
	return 0;
}

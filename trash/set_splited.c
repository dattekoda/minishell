// void	concatenate(t_prompt *prompt, size_t *i, size_t *j)
// {
// 	char	*split;
// 	size_t	len;

// 	// おそらくここで上手く行っていない。
// 	split = prompt->splited_cmd_line[(*j) - 1];
// 	len = 0;
// 	if (prompt->cmd_line[*i] == '\'')
// 	{
// 		(*i)++;
// 		len = (size_t)(ft_strchr(&prompt->cmd_line[*i], '\'') \
// 		- &prompt->cmd_line[*i]);
// 	}
// 	else if(prompt->cmd_line[*i] == '\"')
// 	{
// 		(*i)++;
// 		len = (size_t)(ft_strchr(&prompt->cmd_line[*i], '\"') \
// 		- &prompt->cmd_line[*i]);
// 	}
// 	else
// 		skip_words(&prompt->cmd_line[*i], &len);
// 	ft_strlcat(split, &prompt->cmd_line[*i], len);
// 	*i += len;
// }

// void	handle_quotation(t_prompt *prompt, size_t *i, size_t *j)
// {
// 	char	*tmp;

// 	if (prompt->cmd_line[*i] == '\'')
// 	{
// 		prompt->splited_cmd_line[(*j)++] = &prompt->cmd_line[*i + 1];
// 		tmp = ft_strchr(&prompt->cmd_line[*i + 1], '\'');
// 		*i += tmp - &prompt->cmd_line[*i];
// 		return ;
// 	}
// 	prompt->splited_cmd_line[(*j)++] = &prompt->cmd_line[*i + 1];
// 	tmp = ft_strchr(&prompt->cmd_line[*i + 1], '\"');
// 	*i += tmp - &prompt->cmd_line[*i];
// }

// void	set_splited_cmd_line(t_prompt *prompt)
// {
// 	size_t	i;
// 	size_t	j;
// 	bool	space;

// 	i = 0;
// 	j = 0;
// 	space = true;
// 	while (prompt->cmd_line[i])
// 	{
// 		while (ft_isspace(prompt->cmd_line[i]))
// 			space = (i++, true);
// 		if (!prompt->cmd_line[i])
// 			break ;
// 		if (!space)
// 			concatenate(prompt, &i, &j);
// 		else if (prompt->cmd_line[i] == '\'' || prompt->cmd_line[i] == '\"')
// 			handle_quotation(prompt, &i, &j);
// 		else
// 		{
// 			prompt->splited_cmd_line[j++] = &prompt->cmd_line[i];
// 			skip_words(prompt->cmd_line, &i);
// 		}
// 		if (!prompt->cmd_line[i])
// 			break ;
// 		space = ft_isspace(prompt->cmd_line[i]);
// 		prompt->cmd_line[i] = '\0';
// 	}
// }

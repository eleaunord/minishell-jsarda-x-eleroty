// void	open_quote_error(t_list *token_list)
// {
// 	// need to look up what happens then
// 	ft_lstclear(&token_list, NULL);
// }

// void	set_quote_status(char *c, char *flag)
// {
// 	if ((*c == SINGLE_QUOTE || *c == DOUBLE_QUOTE) && *flag == 0)
// 		*flag = *c;
// 	else if (*c == SINGLE_QUOTE && *flag == SINGLE_QUOTE)
// 		*flag = 0;
// 	else if (*c == DOUBLE_QUOTE && *flag == DOUBLE_QUOTE)
// 		*flag = 0;
// }

// void	process_token(char *line, t_command **command, t_position_tracker *pos,
// 		t_list *minishell)
// {
// 	char	*copy;

// 	(void)command;
// 	(void)minishell;
// 	// copy = trim_separators(create_token(line, pos->start, pos->i), command);
// 	copy = create_token(line, pos->start, pos->i);
// 	// ft_lstadd_back_commands(command, line);
// 	printf("Token: %s\n", (char *)copy);
// 	free(copy);
// }

// t_list	*ft_split_identifier(char *str)
// {
// 	t_list	*lst;
// 	int		i;
// 	int		start;
// 	char	inside_quotes;
// 	char	*clean_node;

// 	lst = NULL;
// 	inside_quotes = 0;
// 	i = 0;
// 	while (str[i])
// 	{
// 		while (str[i] != '\0' && str[i] == SPACE_ && inside_quotes == 0)
// 			i++;
// 		start = i;
// 		if (str[i] == SINGLE_QUOTE || str[i] == DOUBLE_QUOTE)
// 		{
// 			// deal with quotes
// 			// set_quote_status(&str[i], &inside_quotes);
// 			i++;
// 		}
// 		while (str[i] != '\0' && str[i] != 32)
// 			i++;
// 		if ((str[i] == 32 && str[i - 1] != 32) || (str[i] == '\0' && str[i
// 				- 1] != 32))
// 		{
// 			clean_node = ft_substr(str, start, (i - start));
// 			ft_lstadd_back(&lst, ft_lstnew(clean_node, IDENTIFIER));
// 		}
// 	}
// 	// if (inside_quotes != 0)
// 	// 	open_quote_error(lst);
// 	return (lst);
// }


// void	ft_split_separators(t_list **token_list)
// {
// 	char	*s;
// 	t_list	*current;
// 	// int		i;
// 	// int		j;

// 	current = *token_list;
// 	s = current->content;
// 	while (current && s)
// 	{
// 		if (is_separator(s))
// 		{
// 			//insert_node(current, ft_lstnew(ft_substr(s, i, (j - i)), SEPARATOR), i);
// 		}
// 		current = current->next;
// 	}
// }

// t_list	*tokenizer(char *input)
// {
// 	t_list	*list_of_tokens;
// 	int		i;

// 	i = 0;
// 	list_of_tokens = ft_split_identifier(input);
// 	ft_split_separators(&list_of_tokens);
// 	return (list_of_tokens);
// }

// static void	set_input(t_list *minishell)
// {
// 	// minishell->inf.file = 0;
// 	// minishell->inf.eof = 0;
// 	// minishell->ouf.file = 0;
// 	// minishell->inf.flag = 0;
// 	// minishell->ouf.flag = 0;
// 	// minishell->cmds = 0;
// 	minishell->loop = 1;
// }
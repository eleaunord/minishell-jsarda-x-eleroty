
// #include "../../includes/minishell.h"

// char	*create_inside_quotes_token(char *str, int start, int end)
// {
// 	char	*substring;
// 	int		i;
// 	int		j;

// 	if (start > end)
// 		return (ft_strdup(""));
// 	substring = (char *)malloc(sizeof(char) * ((end - start) + 2));
// 	if (substring == NULL)
// 		exit(1);
// 	i = 0;
// 	j = start;
// 	while (j <= end)
// 	{
// 		if (str[j] == '\0')
// 			break ;
// 		substring[i++] = str[j];
// 		j++;
// 	}
// 	substring[i] = '\0';
// 	return (substring);
// }
// char	*process_single_quotes(char *line, t_position_tracker *pos,
// 		t_command **cmd, t_list *mini)
// {
// 	int		quote_pos;
// 	char	*single_quote_str;
// 	char	*temp;
// 	char	*token;

// 	(void)cmd;
// 	(void)mini;
// 	quote_pos = pos->i + 1;
// 	if (pos->i > pos->start)
// 	{
// 		temp = create_token(line, pos->start, pos->i - 1);
// 		// update mini
// 	}
// 	else
// 		temp = ft_strdup("");
// 	while (line[quote_pos] && line[quote_pos] != '\'')
// 		quote_pos++;
// 	if (line[quote_pos] == '\'')
// 	{
// 		single_quote_str = create_inside_quotes_token(line, pos->i + 1,
// 				quote_pos - 1);
// 		token = ft_strjoin(temp, single_quote_str);
// 		pos->i = quote_pos;
// 		pos->start = quote_pos + 1;
// 		free(temp);
// 		free(single_quote_str);
// 		temp = NULL;
// 		single_quote_str = NULL;
// 		return (token);
// 	}
// 	free(temp);
// 	return (NULL);
// }

// char	*process_double_quotes(char *line, t_position_tracker *pos,
// 		t_command **cmd, t_list *mini)
// {
// 	int		quote_pos;
// 	char	*double_quote_str;
// 	char	*temp;
// 	char	*token;

// 	(void)cmd;
// 	(void)mini;
// 	quote_pos = pos->i + 1;
// 	temp = create_token(line, pos->start, pos->i - 1);
// 	// update mini
// 	while (line[quote_pos] && line[quote_pos] != '"')
// 		quote_pos++;
// 	if (line[quote_pos] == '"')
// 	{
// 		double_quote_str = create_inside_quotes_token(line, pos->i + 1,
// 				quote_pos - 1);
// 		// update mini
// 		token = ft_strjoin(temp, double_quote_str);
// 		pos->i = quote_pos;
// 		pos->start = quote_pos + 1;
// 		free(temp);
// 		free(double_quote_str);
// 		temp = NULL;
// 		double_quote_str = NULL;
// 		return (token);
// 	}
// 	return (NULL);
// }

// char	*process_in_quotes(char *line, t_position_tracker *p, t_command **cmd,
// 		t_list *mini)
// {
// 	char				*temp;

// 	//"cat -ls" => cat -ls
// 	temp = NULL;
// 	if (line[p->i] == '\'')
// 		temp = process_single_quotes(line, p, cmd, mini);
// 	else
// 		temp = process_double_quotes(line, p, cmd, mini);
// 	// cat -ls => cat and -ls
// 	return (temp);
// 	// if ((!line[p->i + 1] || is_space(line[p->i + 1])) && *temp)
// 	//     //add command (cmd, *temp, QUOTED);
// 	// else
// 	// 	push_back(cmd, *temp, CONTINUE);
// }

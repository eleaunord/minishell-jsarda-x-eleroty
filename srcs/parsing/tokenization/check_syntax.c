
#include "../../includes/minishell.h"


/*
Syntax errors to check
	1. if there is a pipe at the end of the buffer
	2. if there is a redirection symbol ('<' or '>') at the end of the buffer
	3. for continuous pipes ('||') in the buffer
	4. unmatched quotes
	5. misplaced redirection
	4. ...
*/

// void	categorize(char *str, char *buf)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if ((str[i]) == SPACE_ || (str[i] >= 9 && str[i] <= 13))
// 			buf[i] = 's';
// 		else if (str[i] == SINGLE_QUOTE)
// 			buf[i] = 'q';
// 		else if (str[i] == DOUBLE_QUOTE)
// 			buf[i] = 'Q';
// 		else if (str[i] == '|')
// 			buf[i] = 'p';
// 		else if (str[i] == '<' || str[i] == '>')
// 			buf[i] = 'r';
// 		else if (str[i] == '$')
// 			buf[i] = 'V';
// 		else
// 			buf[i] = 'd';
// 		i++;
// 	}
// }

// int check_syntax(char *buf, t_tokens *minishell)
// {
	// categorize(input, buffer);
// 	return (0);
// }

// buffer : where the categorized characters will be sotred

// int	tokenizer(char *input, t_tokens *minishell, t_command **command)
// {
// 	char	*buffer;
// 	t_tokens	*token_list;

// 	token_list = NULL;
// 	buffer = (char *)malloc(sizeof(char) * ft_strlen(input) + 1);
// 	ft_bzero(buffer, ft_strlen(input) + 1);
// 	// if (!check_syntax(buffer, minishell))
// 	// {
// 	// 	free(buffer);
// 	// 	return (0);
// 	// }
// 	free(buffer);
// 	token_list = ft_split_tokens(input, minishell, command);
// 	if (token_list != NULL)
// 	{
// 		print_tokens(token_list);
// 		return (1);
// 	}
// 	else
// 	{
// 		printf("Token list is empty.\n");
// 		return (0);
// 	}
// 	return (1);
// }
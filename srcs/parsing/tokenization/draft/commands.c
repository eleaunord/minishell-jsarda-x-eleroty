#include "../../includes/minishell.h"

// void ft_lstadd_back_commands(t_command **cmd, char *token)
// {
// 	t_command *push;
// 	t_command *tmp;
	
// 	if (!token)
// 		return ;
// 	if (token[0] == '\0')
// 		return ;
// 	push = (t_command *)malloc(sizeof(t_command));
// 	push->token = ft_strdup(token);
// 	push->length = ft_strlen(token);
// 	push->next = NULL;
// 	if (*cmd == NULL)
// 		*cmd = push;
// 	else
// 	{
// 		tmp = *cmd;
// 		while(tmp->next)
// 			tmp = tmp->next;
// 		tmp->next = push;
// 	}
// }
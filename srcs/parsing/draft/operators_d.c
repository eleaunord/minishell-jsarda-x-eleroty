
// #include "../../includes/minishell.h"

// // >>, >, <, |, ;
// // void		quotes_onoff(char *q, char c)
// // {
// // 	if ((c == 39 || c == '"') && *q == 0)
// // 		*q = c;
// // 	else if ((c == 39 && *q == 39) || (c == '"' && *q == '"'))
// // 		*q = 0;
// // }

// char		set_q_flag(char *q, char c)
// {
// 	if ((c == 39 || c == '"') && *q == 0)
// 		*q = c;
// 	else if ((c == 39 && *q == 39) || (c == '"' && *q == '"'))
// 		*q = 0;
//     return (*q);
// }
// int	single_operator_check(const char *s, int c, int *index)
// {
// 	int	i;

// 	i = 0;
//     if (*index == 0 || s[*index - 1] != '\\')
//     {
//         return (1);
//     }        
// 	while (s[i])
// 	{
// 		if (s[i] == (char) c)
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }


// int contains_operators(char *str, int *start, int *end)
// {
//     char q_flag;
//     int i;
//     char *operators[5] = {"|", ">", ">>", "<", "<<"};

//     while (str[*start])
//     {
//         q_flag = set_q_flag(&q_flag, str[*start]);
//         //check for operator outside quotes
//         if (q_flag == 0 && single_operator_check(OPERATORS_STR, str[*start], start))
//         {
//             i = 0;
//             while (operators[i])
//             {
//                 *end = ft_strlen(operators[i]);
//                 //multi operator check 
//                 if (!ft_strncmp(&str[*start], operators[i], *end))
//                 {
//                     //set start and end to new pos 
//                     *end = *start + *end;
//                     return (1);
//                 }
//                 i++;
//             }
//         }
//         start++;
//     }
//     return (0);
// }
// // void	ft_split_operators(char *token)
// // {
// // 	// char	*token;
// //     char *before_op;
// //     char *after_op;
// // 	t_position_tracker	*pos;

// // 	pos = (t_position_tracker *)malloc(sizeof(t_position_tracker));
// // 	pos->i = 0;
// // 	pos->start = 0;
// // 	while (token[pos->i])
// // 	{
// // 		if (contains_operators(token, &pos->start, &pos->i))
// // 		{
// //             // Substring before operator exists
// //             if (pos->start != 0)
// //             {
// //                 // Insert substring before operator
// //                 // Create a new list node with substring from start to end and inserts it into the list after current
// //                 // insert_node(current, ft_lstnew(ft_substr(token, pos->start, (pos->i - pos->start)), STR));
// //                 before_op = ft_substr(token, 0, pos->start);
// //                 printf("Substring before operator: %s\n", before_op);
// //                 free(before_op);
// //                 // Insert remaining substring after operator
// //                 // Create another new node with the substring from 'end' to the end of 'conent' 
// //                 // and inserts it after the perviously inserted node
// //                 // (current->next).
// //                 if (token[pos->i])
// //                 {
// //                     after_op = ft_substr(token, pos->i, ft_strlen(token) - pos->i);
// //                     printf("Substring after operator: %s\n", after_op);
// //                      free(after_op);
// //                 }
// //                 //insert_node(current->next, ft_lstnew(ft_substr(token, pos->i, ft_strlen(token) - pos->i), STR));
// //                 token[pos->start] = '\0';
// //             }
// //             // Operator at the beg of the string
// //             else if (token[pos->i] != '\0')
// //             {
// //                 // Inserts substring from pos->i to end of token and inserts it after current
// //                 after_op = ft_substr(token, pos->i, ft_strlen(token) - pos->i);
// //                 printf("Substring after operator: %s\n", after_op);
// //                 free(after_op);
// //                 //insert_node(current, ft_lstnew(ft_substr(token, pos->i, ft_strlen(token) - pos->i), STR));
// //                 token[pos->i] = '\0';
// //             }
// // 		}
// // 		pos->i++;
// // 	}
// //     free(pos);
// // }

// /*
// ft_split_operators :
//     1. Check if we have operators
//     2. If substring before operator exists
//         -> Insert substring before operator 
//             : create a new list node with substring from start to end and inserts it into the list after current
//         -> Insert remaining substring after operator
//             : Create another new node with the substring from 'end' to the end of 'token' 
//             and inserts it after the perviously inserted node (current->next)
//     3. If operator at the beginning of the string
//         -> Inserts substring from pos->i to end of token and inserts it after current

// */
// void	ft_split_operators(t_list *token_list)
// {
// 	char	*token;
// 	t_list	*current;
// 	t_position_tracker	*pos;

// 	pos = (t_position_tracker *)malloc(sizeof(t_position_tracker));
// 	pos->i = 0;
// 	pos->start = 0;
// 	current = token_list;
// 	token = current->content;
//     print_list(current);
// 	// while (current && token)
// 	// {
// 	// 	if (contains_operators(token, &pos->start, &pos->i))
// 	// 	{
//     //         if (pos->start != 0)
//     //         {
//     //             insert_node(current, ft_lstnew(ft_substr(token, pos->start, (pos->i - pos->start)), STR));
//     //             if (token[pos->i])
//     //                 insert_node(current->next, ft_lstnew(ft_substr(token, pos->i, ft_strlen(token) - pos->i), STR));
//     //             token[pos->start] = 0;
//     //         }
//     //         else if (token[pos->i] != '\0')
//     //         {
//     //             insert_node(current, ft_lstnew(ft_substr(token, pos->i, ft_strlen(token) - pos->i), STR));
//     //             token[pos->i] = 0;
//     //         }
// 	// 	}
// 	// 	current = current->next;
// 	// }
//     free(pos);
// }

// // t_list	*tokenizer(char *input)
// // {
// // 	t_list	*list_of_tokens;
// // 	int		i;

// // 	i = 0;
// // 	list_of_tokens = ft_split_identifier(input);
// // 	ft_split_separators(&list_of_tokens);
// // 	return (list_of_tokens);
// // }


// // void str_before_separator(char *token, t_position_tracker *p, t_command **command)
// // {
// // 	char *new_token;
	
// // 	(void)command;
// // 	new_token = create_token(token, p->start, p->i - 1);
// // 	// if (new_token[0])
// // 	// 	ft_lstadd_back_commands(command, token);
// // 	free(new_token);
// // }
// // update_separator(token, &p->i, command, &p->start);
// // void update_separator(char *token, int *index, t_command **cmd, int *start)
// // {
// // 	char *new_token;

// // 	new_token = NULL;
// // 	(void)start;
// // 	(void)cmd;
// // 	if (token[*index] == '|')
// // 	{
// // 		new_token = create_token(token, *index, *index);
// // 		// ft_lstadd_back_commands(cmd, new_token);
// // 	}
// // 	free(new_token);
// // }
// // char *ft_split_operators(char *token)
// // {
// // 	char *new_token;
// // 	t_position_tracker *p;

// // 	p = malloc(sizeof(t_position_tracker));
// // 	p->i = 0;
// // 	p->start = 0;
// // 	while (!is_space(token[p->i]))
// // 	{
// // 		p->i++;
// // 		p->start++;
// // 	}
// // 	while (token[p->i])
// // 	{
// // 		if (contains_operators(token, &p->start, &p->i))
// // 		{
// // 			//substring before operator exists
// // 			if (p->start != 0)
// //             {
// //                 new_token = create_token(token, p->start, (p->i - p->start));
// //                 //add to commands
// //                 free(new_token);
// //                 if (token[p->i])
// //                    new_token = create_token(token, p->i, ft_strlen(token) - p->i);
// //                 token[p->start] = '\0';
// //             }
// //             else if (token[p->i] != '\0')
// //             {
// //                 new_token = create_token(token, p->i, ft_strlen(token) - p->i);
// //                 token[p->i] = '\0';
// //             }
// // 		}
// // 		p->i++;
// // 	}
// // 	free(p);
// // 	// free(token);
// // 	return (new_token);
// // }
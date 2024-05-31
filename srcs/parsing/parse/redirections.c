
#include "../../../includes/minishell.h"


/*

 > truncate mode
 >> append mode

*/

// void	handle_redirections(t_token *token)
// {
// 	t_token *temp;

// 	temp = token;

// 	// if (temp->type == REDIR_OUT_TOKEN || temp->type == APPEND_TOKEN)
// 	// {
// 	//     redir_out(temp);
// 	// }
// 	if (temp->type == REDIR_OUT_TOKEN)
// 	{
// 		temp = temp->next;
// 		while (token->value && token->value != (void *)0)
// 		{
//             // skip spaces and handle quotes
// 			temp->filename = temp->value;
// 			temp = temp->next;
// 		}
// 		if (!temp->filename)
// 			printf("No such file or directory");
// 		temp->sstdout = open(temp->filename, O_CREAT | O_RDWR | O_APPEND, 0644);
// 	}
// 	else if (temp->type == REDIR_OUT_TOKEN)
// 	{
// 		temp = temp->next;
// 		while (token->value && token->value != (void *)0)
// 		{
// 			temp->filename = temp->value;
// 			temp = temp->next;
// 		}
// 		if (!temp->filename)
// 			printf("No such file or directory");
// 		temp->sstdout = open(temp->filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
// 	}

// }

// OR HERE : 

// t_ast_node	*create_and_link_redirection(t_token **tokens, t_token *tmp)
// {
// 	t_ast_node	*redirect_node;

// 	redirect_node = new_ast_node((*tokens)->type);
// 	*tokens = (*tokens)->next->next;
// 	redirect_node->left = parse_redirection(tokens);
// 	redirect_node->right = create_file_node(tmp->next);
// 	free(tmp->value);
// 	free(tmp);
// 	return (redirect_node);
// }
// t_ast_node	*new_ast_node(t_token_type type)
// {
// 	t_ast_node		*node;

// 	node = malloc(sizeof(t_ast_node));
// 	if (!node)
// 		return (NULL);
// 	node->type = type;
// 	node->args = NULL;
// 	node->left = NULL;
// 	node->right = NULL;
// 	return (node);
// }

// t_ast_node	*create_file_node(t_token *token)
// {
// 	t_ast_node			*node;

// 	node = malloc(sizeof(t_ast_node));
// 	if (!node)
// 		return (NULL);
// 	node->type = token->type;
// 	node->args = malloc(sizeof(char *) * 2);
// 	if (!node->args)
// 	{
// 		free(node);
// 		return (NULL);
// 	}
// 	node->args[0] = token->value;
// 	node->args[1] = NULL;
// 	node->left = NULL;
// 	node->right = NULL;
// 	free(token);
// 	return (node);
// }

// t_ast_node	*parse_redirection(t_token **tokens)
// {
// 	t_token		*tmp;
// 	t_ast_node	*redirect_node;
// 	t_token		*next_token;

// 	if (!*tokens)
// 		return (NULL);
// 	tmp = *tokens;
// 	if ((*tokens)->type >= TOKEN_REDIR_IN
// 		&& (*tokens)->type <= TOKEN_REDIR_HEREDOC)
// 		return (create_and_link_redirection(tokens, tmp));
// 	while (*tokens && (*tokens)->next)
// 	{
// 		next_token = (*tokens)->next;
// 		if ((*tokens)->next->type >= TOKEN_REDIR_IN
// 			&& (*tokens)->next->type <= TOKEN_REDIR_HEREDOC)
// 		{
// 			redirect_node = new_ast_node((*tokens)->next->type);
// 			(*tokens)->next = next_token->next->next;
// 			redirect_node->left = parse_redirection(&tmp);
// 			redirect_node->right = create_file_node((next_token->next));
// 			return (free(next_token->value), free(next_token), redirect_node);
// 		}
// 		*tokens = next_token;
// 	}
// 	return (parse_command(&tmp));
// }
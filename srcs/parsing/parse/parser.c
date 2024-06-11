#include "../../../includes/minishell.h"

void	fill_args(t_token *tokens, t_node *node)
{
	t_token	*tok;
	int		i;

	tok = tokens;
	if (!tokens || !node)
		return ;
	i = -1;
	while (tok)
	{
		if (tok->type == TOKEN_WORD && !tok->processed)
		{
			node->args[++i] = ft_strdup(tok->value);
			if (!node->args[i])
			{
				while (i > 0)
				{
					free(node->args[--i]);
				}
				free(node->args);
				free(node->cmd);
				return ;
			}
		}
		tok = tok->next;
	}
}

void	parse_tokens(t_token *tokens, t_node *node)
{
	if (!tokens)
	{
		return ;
	}
	init_parsing(node);
	set_filename(&tokens, node);
	// SET ARGS and command
	init_args(tokens, node);
	set_cmd(tokens, node);
	// SET EXPANSION
	process_expansions(&tokens, node);
	// UPDATE NODE
	update_tokens(&tokens, node);
	// SET ARGS
	fill_args(tokens, node);
}
	
	// DEBUG

	// t_node	*head;
	// int		i;

	// head = node;
	// i = 0;
	// while (head)
	// {
	// 	printf("Node : %s\n", (char *)head->content);
	// 	// printf("Cmd : %s\n", head->cmd);
	// 	// printf("File name out: %s\n", head->filename_out);
	// 	while (i < node->limiter_hd_count)
	// 	{
	// 		if (head->filename_in)
	// 			printf("File name in: %s : %s\n", head->limiter_hd[i],
	// 				head->filename_in);
	// 		printf("File name heredoc: %s\n", head->limiter_hd[i++]);
	// 	}
	// 	// printf("Node expansion: %s\n", head->key_expansion);
	// 	// printf("Arg cunt : %d\n", head->arg_count);
	// 	// int x = 0;
	// 	// while (x < head->arg_count)
	// 	// {
	// 	// 	printf("Arg[x] : %s\n", head->args[x++]);
	// 	// }
	// 	head = head->next;
	// }
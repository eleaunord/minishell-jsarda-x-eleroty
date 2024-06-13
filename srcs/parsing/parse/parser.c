#include "../../../includes/minishell.h"
#include <stdbool.h>

void	count_heredocs(t_token **tokens, t_node *node)
{
	t_token	*current;
	int		i;

	if (!tokens || !*tokens)
		return ;
	current = *tokens;
	i = 0;
	while (current)
	{
		if (current->type == HEREDOC_TOKEN)
		{
			if (current->next && current->next->type == TOKEN_WORD)
			{
				i++;
			}
		}
		current = current->next;
	}
	node->limiter_hd_count = i;
}
// A reduire apres merge exec
void	set_filename(t_token **tokens, t_node *node)
{
	t_token	*current;
	t_token	*tok;
	int		i;

	if (!tokens || !*tokens || !node)
		return ;
	tok = *tokens;
	count_heredocs(&tok, node);
	i = 0;
	node->limiter_hd = (char **)calloc(node->limiter_hd_count + 1,
			sizeof(char *));
	if (!node->limiter_hd)
	{
		return ;
	}
	current = *tokens;
	while (current)
	{
		if (current->type >= APPEND_TOKEN && current->type <= REDIR_IN_TOKEN)
		{
			if (current->next && current->next->type == TOKEN_WORD)
			{
				if (current->type == REDIR_IN_TOKEN)
				{
					node->filename_in = current->next->value;
					current->next->processed = 1;
				}
				else if (current->type == REDIR_OUT_TOKEN)
				{
					node->filename_out = current->next->value;
					current->next->processed = 1;
				}
				else if (current->type == HEREDOC_TOKEN)
				{
					if (i < node->limiter_hd_count) {
                        node->limiter_hd[i] = current->next->value;
                        i++;
                    }
                    node->here_doc = 1;
					printf("node->limiter_hd_count : %d\n", node->limiter_hd_count);
					printf("i : %d\n", i);
                    if (i == node->limiter_hd_count)
					{
						printf("creating file\n");
                        node->filename_in = get_tmp_file();
                    }
                    current->next->processed = 1;
				}
			}
		}
		current = current->next;
	}
	node->limiter_hd[node->limiter_hd_count] = NULL;
}

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
// taille ok si on enleve debug
void	parse_tokens(t_token *tokens, t_node *node)
{
	t_node	*head;
	int		i;

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
	head = node;
	i = 0;
	// while (head)
	// {
	// 	printf("Node : %s\n", (char *)head->content);
	// 	// printf("Cmd : %s\n", head->cmd);
	// 	// printf("File name out: %s\n", head->filename_out);
	// 	// while (i < node->limiter_hd_count)
	// 	// {
	// 	// 	if (head->filename_in)
	// 	// 		printf("File name in: %s : %s\n", head->limiter_hd[i],
	// 	// 			head->filename_in);
	// 	// 	printf("File name heredoc: %s\n", head->limiter_hd[i++]);
	// 	// }
	// 	// printf("Node expansion: %s\n", head->key_expansion);
	// 	// printf("Arg cunt : %d\n", head->arg_count);
	// 	// int x = 0;
	// 	// while (x < head->arg_count)
	// 	// {
	// 	// 	printf("Arg[x] : %s\n", head->args[x++]);
	// 	// }
	// 	head = head->next;
	// }
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_fonction.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:26:01 by jsarda            #+#    #+#             */
/*   Updated: 2024/07/29 14:53:57 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug_first_part_loop(t_node *datas)
{
	int	j;

	j = -1;
	printf("\tcmd = %s\n", datas->cmd);
	printf("\targs:\n");
	while (datas->args[++j])
		printf("\t\targs[%d] = %s\n", j, datas->args[j]);
	printf("\tredir_type_in = %d\n", datas->is_redir_in);
	printf("\tredir_type_out = %d\n", datas->is_redir_out);
	printf("\tnamein:\n");
	j = 0;
	while (datas->filename_in && datas->filename_in[j])
	{
		printf("\t\tnamein[%d] = %s\n", j, datas->filename_in[j]);
		j++;
	}
	j = 0;
	printf("\tnameout:\n");
	while (datas->filename_out && datas->filename_out[j])
	{
		printf("\t\tnameout[%d] = %s\n", j, datas->filename_out[j]);
		j++;
	}
}

void	debug_print_block(t_node **list)
{
	t_node	*datas;
	int		i;
	int		j;

	datas = *list;
	i = 0;
	while (datas)
	{
		printf("CMD %d\n", i);
		debug_first_part_loop(datas);
		printf("\tis_hd = %d\n", datas->is_here_doc);
		j = 0;
		printf("\tlimiters:\n");
		while (datas->limiter_hd && datas->limiter_hd[j])
		{
			printf("\t\tlimiters[%d] = %s\n", j, datas->limiter_hd[j]);
			j++;
		}
		datas = datas->next;
		i++;
	}
}

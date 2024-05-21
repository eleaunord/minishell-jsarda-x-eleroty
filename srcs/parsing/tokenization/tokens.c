// readline => Reads a line from the standard input and returns it.
// rl_clear_history =>	Clears the readline history list.
// rl_on_new_line =>	Prepares readline for reading input on a new line.
// rl_replace_line 	=> Replaces the content of the readline current line buffer.
// rl_redisplay =>	Updates the display to reflect changes to the input line.
// add_history =>	Adds the most recent input to the readline history list.

#include "../../includes/minishell.h"

/*

	1. Getting the string with READLINE
		- eg : "cat -e|grep>file.txt ' aliens';"

	2. Splitting input string into a linked list of tokens with ft_split_tokens
		- eg : {"cat"} -> {"-e|grep>file.txt"} -> {"' aliens';"} -> NULL

	3. Re-cutting according to the operators (symbols: >>, >, <, |,
		;) with trim_operators
		- eg : {"cat"} -> {"-e"} -> {"|"} -> {"grep"} -> {">"} -> {"file.txt"}
			-> {"' aliens'"} -> {";"} -> NULL

*/

char	*create_token(char *str, int start, int end)
{
	char	*substring;
	int		i;
	int		j;

	if (start > end)
		return (ft_strdup(""));
	substring = (char *)malloc(sizeof(char) * ((end - start) + 2));
	if (substring == NULL)
		exit(1);
	i = 0;
	j = start;
	while (j <= end)
	{
		if (str[j] == '\0')
			break ;
		if (!is_space(str[j]))
			substring[i++] = str[j];
		j++;
	}
	substring[i] = '\0';
	return (substring);
}

/*

ft_split_tokens : splitting the input on the command line into tokens

	INIT VARS
	1. allocate memory for a t_position_tracker structure
	2. pos->i is the index of the current line

	WHILE LOOP
	1. if the next char is the end of the line or current char is a space then it's the end of a token
	2. create_token to handle token creation
	3. update pos->start to the next char (after the current one)

*/
void	print_tokens(t_tokens *head)
{
	t_tokens	*current;

	current = head;
	while (current != NULL)
	{
		if (current->content != NULL && ((char *)current->content)[0] != '\0')
		{
			printf("Token : %s\n", (char *)current->content);
		}
		current = current->next;
	}
}

t_tokens	*ft_split_tokens(char *line, t_tokens *minishell, t_command **command)
{
	t_position_tracker	*pos;
	char				*token;
	t_tokens				*token_list;


	token_list = NULL;
	pos = (t_position_tracker *)malloc(sizeof(t_position_tracker));
	pos->i = 0;
	pos->start = 0;
	while (line[pos->i])
	{
		if (line[pos->i + 1] == '\0' || (is_space(line[pos->i])))
		{
			token = create_token(line, pos->start, pos->i);
			ft_lstadd_back(&token_list, ft_lstnew(token, STR));
			pos->start = pos->i + 1;
		}
		else if (line[pos->i] == '\'' || line[pos->i] == '"')
		{
			token = process_in_quotes(line, pos, command, minishell);
			ft_lstadd_back(&token_list, ft_lstnew(token, STR));
		}
		pos->i++;
	}
	free(pos);
	return (token_list);
}

int	tokenizer(char *input, t_tokens *minishell, t_command **command)
{
	t_tokens	*token_list;

	//check syntax
	token_list = ft_split_tokens(input, minishell, command);
	ft_split_operators(token_list);
	if (token_list != NULL)
	{
		print_tokens(token_list);
		ft_lstclear(&token_list, free);
		return (1);
	}
	else
	{
		printf("Token list is empty.\n");
		return (0);
	}
	free(token_list);
	return (1);
}

int	main(int argc, char *argv[])
{
	char		*input_line;
	t_tokens		*minishell;
	t_command	*command;
	int			flag;

	input_line = NULL;
	minishell = NULL;
	flag = 1;
	(void)argc;
	(void)argv;
	// set_input(&minishell);
	while (flag == 1)
	{
		input_line = readline("prompt> ");
		if (input_line == NULL)
		{
			rl_clear_history();
			// printf("exit\n");
			flag = 0;
			// handler_sigint(SIGTERM);
		}
		if (!tokenizer(input_line, minishell, &command))
		{
			add_history(input_line);
			free(input_line);
			return (0);
		}
		add_history(input_line);
		free(input_line);
		return (1);
		// exec command
		// free_input(&minishell);
	}
	ft_lstclear(&minishell, free);
	free(input_line);
	return (0);
}

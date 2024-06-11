
#include "../../../includes/minishell.h"

// Function to collapse multiple spaces into a single space,
	//ignoring spaces inside quotes

bool	toggle_quote_state(bool in_quote, char *quote_char, char current_char)
{
	if (in_quote && current_char == *quote_char)
	{
		*quote_char = '\0';
		return (false);
	}
	else if (!in_quote)
	{
		*quote_char = current_char;
		return (true);
	}
	return (in_quote);
}

void	handle_quote(char **dst, char **src, bool *in_quote, char *quote_char)
{
	*in_quote = toggle_quote_state(*in_quote, quote_char, **src);
	*(*dst)++ = *(*src)++;
}

void	handle_space(char **dst, bool in_quote, int *space)
{
	if (!in_quote)
	{
		if (!*space)
		{
			*(*dst)++ = ' ';
			*space = 1;
		}
	}
	else
	{
		*(*dst)++ = ' ';
	}
}

void	handle_non_space(char **dst, char **src, int *space)
{
	*(*dst)++ = *(*src)++;
	*space = 0;
}

char	*collapse_spaces(char *str)
{
	char *dst;
	char *src;
	bool in_quote;
	char quote_char;
	int space;

	dst = str;
	src = str;
	in_quote = false;
	quote_char = '\0';
	space = 0;
	while (*src != '\0')
	{
		if (is_quote(*src))
			handle_quote(&dst, &src, &in_quote, &quote_char);
		else if (isspace((unsigned char)*src))
		{
			handle_space(&dst, in_quote, &space);
			src++;
		}
		else
			handle_non_space(&dst, &src, &space);
	}
	*dst = '\0';
	return (str);
}

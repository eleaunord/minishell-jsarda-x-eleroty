#include "../../../includes/minishell.h"

char	*duplicate_string(const char *src)
{
	if (src == NULL)
		return (NULL);
	return (strdup(src));
}

static char	*extract_key(const char *src, char *equal_sign)
{
	if (src == NULL || equal_sign == NULL)
		return (NULL);
	return (strndup(src, equal_sign - src));
}

static char	*extract_value(const char *src, char *equal_sign)
{
	if (src == NULL || equal_sign == NULL)
		return (NULL);
	return (strdup(equal_sign + 1));
}

// Function to parse and assign key and value from an element string
int	parse_key_value(t_env **new, char *elem)
{
	char	*equal_sign;

	equal_sign = strchr(elem, '=');
	if (equal_sign)
	{
		(*new)->key = extract_key(elem, equal_sign);
		if ((*new)->key == NULL)
			return (0);
		(*new)->value = extract_value(elem, equal_sign);
		if ((*new)->value == NULL)
		{
			free_t_env(*new);
			return (0);
		}
	}
	else
	{
		(*new)->key = duplicate_string(elem);
		if ((*new)->key == NULL)
			return (0);
		(*new)->value = NULL;
	}
	return (1);
}


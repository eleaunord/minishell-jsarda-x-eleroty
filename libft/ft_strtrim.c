#include "../includes/minishell.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*start;
	char	*end;

	if (!s1 || !set)
		return (NULL);
	start = (char *)s1;
	while (*start && ft_strchr(set, *start))
		start++;
	end = (char *)(s1 + ft_strlen(s1) - 1);
	while (end > start && ft_strchr(set, *end))
		end--;
	return (ft_substr(start, 0, end - start + 1));
}
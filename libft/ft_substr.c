#include "../includes/minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_s;
	size_t	s_length;
	size_t	i;

	if (!s)
		return (NULL);
	s_length = ft_strlen(s);
	if (s_length <= len + start)
		len = s_length - start;
	if (s_length < start)
	{
		new_s = malloc(1);
		new_s[0] = '\0';
		return (new_s);
	}
	new_s = (char *)malloc((sizeof(*s) * (len + 1)));
	if (!new_s)
		return (NULL);
	i = 0;
	while (s[start] && i < len)
		new_s[i++] = s[start++];
	new_s[i] = '\0';
	return (new_s);
}
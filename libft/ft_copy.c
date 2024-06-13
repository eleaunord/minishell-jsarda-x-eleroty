#include "../includes/minishell.h"

char	*ft_strcpy(char *dest, const char *src)
{
	char	*start;

	start = dest;
	while ((*dest++ = *src++) != '\0')
		;
	return (start);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t src_size;

	src_size = ft_strlen(src);
	if (!dst || !src || !size)
		return (src_size);
	i = 0;
	while (i < (size - 1) && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_size);
}
#include "../includes/minishell.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t i;

	i = 0;
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		((char *)(dest))[i] = ((const char *)(src))[i];
		i++;
	}
	return (dest);
}
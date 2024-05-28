
#include "../includes/minishell.h"


size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
void	*ft_bzero(void *s, size_t bytes)
{
	size_t	i;

	i = 0;
	while (i < bytes)
	{
		((unsigned char *)(s))[i] = '\0';
		i++;
	}
	return (s);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mem;

	if (nmemb == 0 || size == 0)
	{
		mem = malloc(1);
		return (mem);
	}
	if ((nmemb * size) < size || (nmemb * size) < nmemb)
		return (0);
	mem = (void *)malloc(nmemb * size);
	if (!mem)
		return (NULL);
	ft_bzero(mem, nmemb * size);
	return (mem);
}
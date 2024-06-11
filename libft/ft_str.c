#include "../includes/minishell.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_size;

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
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (n && (str1[i] || str2[i]))
	{
		if (str1[i] != str2[i] || !str1[i] || !str2[i])
			return ((str1[i]) - (str2[i]));
		i++;
		n--;
	}
	return (0);
}
char	*ft_strdup(const char *s)
{
	char	*new_string;

	new_string = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!new_string)
		return (0);
	ft_strlcpy(new_string, s, (ft_strlen(s) + 1));
	return (new_string);
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*new_string;

	new_string = malloc(sizeof(char) * (n + 1));
	if (!new_string)
		return (0);
	ft_strlcpy(new_string, s, (n + 1));
	return (new_string);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total_length;
	size_t	i;
	size_t	j;
	char	*new_s;

	if (!s1 || !s2)
		return (NULL);
	total_length = ft_strlen(s1) + ft_strlen(s2);
	new_s = (char *)malloc(sizeof(char) * (total_length + 1));
	if (!new_s)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s1))
	{
		new_s[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < ft_strlen(s2))
		new_s[i++] = s2[j++];
	new_s[i] = '\0';
	return (new_s);
}
char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)s + i);
	return (0);
}
char	*ft_strcpy(char *dest, const char *src)
{
	char	*start;

	start = dest;
	while ((*dest++ = *src++) != '\0')
		;
	return (start);
}

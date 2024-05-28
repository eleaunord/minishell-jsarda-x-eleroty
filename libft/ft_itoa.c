#include "../includes/minishell.h"

static int	get_size(int n)
{
	int	size;

	size = 1;
	if (n < 0)
		size++;
	while (n <= -10)
	{
		n /= 10;
		size++;
	}
	while (n >= 10)
	{
		n /= 10;
		size++;
	}
	return (size);
}

static char	*ft_malloc(int n)
{
	char	*s;
	int		size;

	size = get_size(n);
	s = (char *)malloc(sizeof(char) * (size + 1));
	if (!s)
		return (NULL);
	ft_bzero(s, size + 1);
	return (s);
}

static void	ft_recursive(int n, char *res)
{
	if (n == -2147483648)
	{
		res[1] = '2';
		ft_recursive(147483648, res);
	}
	else
	{
		if (n < 0)
			n = -n;
		if (n > 9)
		{
			ft_recursive((n / 10), res);
			ft_recursive((n % 10), res);
		}
		else
			res[ft_strlen(res)] = (n + '0');
	}
}

char	*ft_itoa(int n)
{
	char	*res;

	res = ft_malloc(n);
	if (!res)
		return (NULL);
	if (n < 0)
	{
		res[0] = '-';
	}
	ft_recursive(n, res);
	return (res);
}
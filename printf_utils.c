#include <stdlib.h>
#include "libft.h"
#include "printf_utils.h"

int	ft_is_in(char const *set, char c)
{
	if (!set)
		return (0);
	while (*set)
		if (c == *(set++))
			return (1);
	return (0);
}

int ft_abs(int n)
{
	if (n < 0)
		return (-n);
	else
		return (n);
}

char	*ft_strofc(char c)
{
	char	*out;

	out = malloc(sizeof(char) * 2);
	if (!out) 
		return (NULL);
	out[0] = c;
	out[1] = '\0';
	return (out);
}

char	*ft_join3(char const *s1, char const *s2, char const *s3)
{
	char	*out;
	size_t	i;
	size_t	n;

	if (!s1)
		return (ft_strjoin(s2, s3));
	if (!s2)
		return (ft_strjoin(s1, s3));
	if (!s3)
		return (ft_strjoin(s2, s1));
	n = 1 + ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	out = malloc(sizeof(char) * (1 + n));
	if (!out)
		return (NULL);
	i = 0;
	while (*s1)
		out[i++] = *(s1++);
	while (*s2)
		out[i++] = *(s2++);
	while (*s3)
		out[i++] = *(s3++);
	out[i] = '\0';
	return (out);
}

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	t_uint	i;

	i = 0;
	while (i < n)
	{
		if (*((t_uchar *)s + i) == (t_uchar) c)
			return ((void *)s + i);
		++i;
	}
	return (NULL);
}

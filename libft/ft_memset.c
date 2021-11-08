#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	t_uint	i;

	i = 0;
	while (i < len)
	{
		*((t_uchar *)b + i) = c;
		++i;
	}
	return (b);
}

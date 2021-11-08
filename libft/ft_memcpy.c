#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	t_uint	i;

	if (!dst && !src)
		return (NULL);
	i = 0;
	while (i < len)
	{
		*((t_uchar *)dst + i) = *((t_uchar *)src + i);
		++i;
	}
	return (dst);
}

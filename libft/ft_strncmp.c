#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n != 0 && *s1)
	{
		if (*s1 != *s2)
			return ((t_uchar)(*s1) - (t_uchar)(*s2));
		++s1;
		++s2;
		--n;
	}
	if (n != 0)
		return ((t_uchar)(*s1) - (t_uchar)(*s2));
	else
		return (0);
}

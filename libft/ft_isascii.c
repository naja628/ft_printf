#include "libft.h"

int	ft_isascii(int c)
{
	if (0 <= c && c < 128)
		return (1);
	else
		return (0);
}

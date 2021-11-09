#include <limits.h>
#include "ft_printf.h"
#include "libft.h"
#include <stdio.h>

int	main()
{
	ft_printf("_%#x_\n", LONG_MIN);
	printf("_%#x_\n", LONG_MIN);
	return (0);
}

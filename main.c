#include "ft_printf.h"
#include <stdio.h>

int	main()
{
	printf("%p\n", NULL);
	ft_printf("%p\n", NULL);
	ft_printf("%01d\n", 0);
	printf("%01d\n", 0);
	ft_printf("%s", (char *) NULL);
	printf("%s", (char *) NULL);
}

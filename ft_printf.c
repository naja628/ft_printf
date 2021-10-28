#include <unistd.h>
#include <stdarg.h>
#include "libft.h"
#include "ft_format_one.h"
#include "constants.h"
#include "printf_utils.h"
//#inculde "ft_printf.h"
#include <stdio.h>

static int	ft_printf_helper(char const *s, va_list va)
{
	size_t	i;
	int		j;

	if (!s)
		return (0);
	i = 0;
	while (s[i] && s[i] != '%')
		++i;
	write(1, s, i);
	if (!s[i])
		return (i);
	s += i + 1;
	printf("passed to format one: %s\n", s);
	j = ft_format_one(s, va);
	if (j == -1)
		return (-1);
	i += j;
	while (*s && !ft_is_in(SPECIFIERS, *s))
		++s;
	return (i + ft_printf_helper(s + 1, va));
}

int	ft_printf(char const *s, ...)
{
	int	ret;
 
	if (s == NULL)
		return (-1);
	va_list	to_format;
	va_start(to_format, s);
	ret = ft_printf_helper(s, to_format);
	va_end(to_format);
	return (ret);
}

#include <stdlib.h>

int	main(int ac, char **av)
{
	if (ac != 3)
		exit (-1);
	//ft_printf(av[1]);
	ft_printf("** %s ** %s **", av[1], av[2]);
	ft_printf("\n");
	return (0);
}

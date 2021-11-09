#include <unistd.h>
#include <stdarg.h>
#include "libft.h"
#include "ft_format_one.h"
#include "definitions.h"
#include "printf_utils.h"
#include "ft_printf.h"

#include <stdio.h>
static int	ft_printf_helper(char const *s, va_list va)
{
	size_t	i;
	int		j;
	char	spec;

	if (!s)
		return (0);
	i = 0;
	while (s[i] && s[i] != '%')
		++i;
	write(1, s, i);
	if (!s[i])
		return (i);
	s += i + 1;
	j = ft_format_one(s, &spec, va);
	//printf("formatted str len : %d\n", j);
	if (j == -1)
		return (-1);
	i += j;
	while (*s && *s != spec) //change if we wanna copy the thingy
		++s;
//	printf("\nremains to be printed : %s\n", s);
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

#include <unistd.h>
#include <stdlib.h> // can do without?
#include <stdarg.h>
#include <errno.h>
//temporary !!
#include "libft.h"

#define SPECIFIERS "spidxX%"

void	ft_error(int errcode, char const *msg)
{
	if (msg)
		ft_putstr_fd((char *) msg, 2); // TODO change put*.c to take const args
	errno = errcode;
}

int	ft_is_in(char const *set, char c)
{
	if (!set)
		return (0);
	while (*set)
		if (c == *(set++))
			return (1);
	return (0);
}

/* formats and print the first arg,
 * consuming the appropriate num of args,
 * (typically 1)
 * returns the length of the printed str
 */
char	*ft_arg_to_str(char spec, va_list args)
{
	if (spec == '%')
		return ("%");
	if (spec == 'd' || spec == 'i')
		return (ft_itoa(va_arg(args, int)));
	if (spec == 's')
		return (va_arg(args, char *));
	// etc
	write(2, &spec, 1);
	ft_error(-1, " is not a specifier");
	return (NULL);
}


int	ft_format_one(char const *s, va_list args)
{
	char	*out;

	if (!*s)
		ft_error(-1, "nothing after %");
	out = ft_arg_to_str(*s, args);
	ft_putstr_fd(out, 1);
	return (ft_strlen(out));
}

#include <stdio.h>
int ft_printf_helper(char const *s, va_list va)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] && s[i] != '%')
		++i;
	write(1, s, i);
	if (!s[i])
		return (i);
	s += i + 1;
	i += ft_format_one(s, va);
	//printf("\n|rest of str : %s|\n", s);
	while (*s && !ft_is_in(SPECIFIERS, *s))
		++s;
	if (errno == -1)
		return (i);
	return (i + ft_printf_helper(s + 1, va));
}

int	ft_printf(char const *s, ...)
{
	int	ret;

	va_list	to_format;
	va_start(to_format, s);
	ret = ft_printf_helper(s, to_format);
	va_end(to_format);
	return (ret);
}

int	main(int ac, char **av)
{
	if (ac != 3)
		exit (-1);
	//ft_printf(av[1]);
	ft_printf("** %s ** %s **", av[1], av[2]);
	ft_printf("\n");
	return (0);
}

#include "libft.h"
#include "printf_utils.h"
#include "definitions.h"
#include "t_fspec.h"

/* take what comes after a % in a format string 
 * (eg "+5.2d...")
 * and make a t_fspec out of it */
void	ft_parse_spec(char const *s, t_fspec *f)
{
	size_t	i;

	f->width = -1;
	i = 0;
	while (*s && ft_is_in(FLAGS, *s) && *s != '.')
		f->flags[i++] = *(s++);
	if (ft_isdigit(*s))
		f->width = ft_atoi(s);
	while (*s && ft_isdigit(*s))
		++s;
	if (*s == '.' && ft_isdigit(s[1]))
	{
		f->flags[i++] = '.';
		f->precision = ft_atoi(++s);
	}
	while (*s && ft_isdigit(*s))
		++s;
	f->spec = *s;
	f->flags[i] = '\0';
}

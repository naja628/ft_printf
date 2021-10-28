#include "libft.h"
#include "printf_utils.h"
#include "constants.h"
#include "t_fspec.h"

#include <stdio.h>

/* take what comes after a % in a format string 
 * (eg "+5.2d...")
 * and make a t_fspec out of it
 *
 * return 0 upon success or -1 upon error */
void	ft_parse_spec(char const *s, t_fspec *f)
{
	size_t	i;
	char	*s_save;

	s_save = (char *) s;
	f->width = -1;
	i = 0;
	while (*s && ft_is_in(FLAGS, *s))
		f->flags[i++] = *(s++);
	if (ft_isdigit(*s))
		f->width = ft_atoi(s);
	while (*s && ft_isdigit(*s))
		++s;
	if (*s == '.' && ft_isdigit(s[1]))
		f->precision = ft_atoi(++s);
	while (*s && ft_isdigit(*s))
		++s;
	f->spec = *(s++);
	f->slen = s - s_save; // maybe needs 1 more or less...
	f->flags[i] = '\0';
	printf("exiting ft_parse_spec w width = %d\n", f->width);
}

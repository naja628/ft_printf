#ifndef T_FSPEC_H
# define T_FSPEC_H

# include <stddef.h>
# include "constants.h"

/* fspec : format specifier
 * spec is the specifier character (i, d etc)
 * slen is the len of the format specifier (% excluded)
 * negative width means width means unspecified */
typedef struct
{
	char	flags[NFLAGS + 1];
	int		width; // TODO change type to smth else
	t_uint	precision;
	char	spec;
	size_t	slen;
}	t_fspec;

/* take what comes after a % in a format string 
 * (eg "+5.2d...")
 * and make a t_fspec out of it */
void	ft_parse_spec(char const *s, t_fspec *f);

#endif

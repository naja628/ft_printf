#include <stdarg.h>
#include <stdlib.h>
#include "libft.h"
#include "t_fspec.h"
#include "printf_utils.h"
#include "ft_hexstr.h"
#include "ft_format_one.h"

#include <stdio.h>

/* sarg : pieces to build a string out of an argument */
typedef struct
{
	char	*base;
	char	*prefix;
}	t_sarg;

/* consume 1 arg and convert it to a t_sarg 
 * ignoring flags.
 *
 * % is handled elsewhere (as it doesn't consume an arg).
 * 
 * num_arg is useful for the d/i case where the conversion is
 * a bit tricky due to signedness.
 * 
 * errors are indicated by sarg->base being NULL upon exit */
static void	ft_set_sarg(t_sarg *sarg, char spec, va_list args)
{
	int	num_arg;

	sarg->prefix = "";
	sarg->base = NULL;
	if (spec == 'd' || spec == 'i')
	{
		num_arg = va_arg(args, int);
		if (num_arg < 0)
			sarg->prefix = "-";
		sarg->base = ft_itoa(ft_abs(num_arg));
	}
	else if (spec == 's')
		sarg->base = ft_strdup(va_arg(args, char *));
	else if (spec == 'x')
		sarg->base = ft_hexstr(va_arg(args, t_uint));
	else if (spec == 'X')
		sarg->base = ft_heXstr(va_arg(args, t_uint));
	else if (spec == 'p')
	{
		sarg->prefix = "0x";
		sarg->base = ft_hexstr((size_t) va_arg(args, void *));
	}
	else if (spec == 'c')
		sarg->base = ft_strofc(va_arg(args, int));
	printf("set : %p\n", sarg->base);
}

/* set sarg->base to a new str taking the precision into account
 * frees the previous base (which is always alloced)
 * return 0 upon success
 * -1 upon error */
static int	ft_handle_precision(t_sarg *sarg, t_uint p, char spec)	
{
	char	*new_base;
	size_t 	len;

	if (!ft_is_in("sdixX", spec) || !sarg || !sarg->base)
		return (0);
	len = ft_strlen(sarg->base);
	new_base = sarg->base;
	if (spec == 's')
		new_base = ft_substr(sarg->base, 0, p);
	else if (p > len || (!ft_strncmp("0", sarg->base, 2) && p == 0))
		new_base = malloc(sizeof(char) * (p + 1));
	if (!new_base)
		return (-1);
	ft_memset(new_base, '0', p);
	if (p > len)
		ft_strlcpy(new_base + (p - len), sarg->base, len + 1); //indices ok?
	else if (!ft_strncmp("0", sarg->base, 2) && p == 0)
		*new_base = '\0';
	if (new_base == sarg->base)
		return (0);
	free(sarg->base);
	sarg->base = new_base;
	return (0);
}

/* combine a into a the final string to be output (returned)
 * taking width into consideration 
 * return (NULL) upon failure */
static char	*ft_handle_width(t_sarg const *a, t_fspec const *f)
{
	char		*ret;
	char		*pad;
	ptrdiff_t	pad_len;

	printf("bah: %d\n", f->width);
	pad_len = f->width - ft_strlen(a->prefix) - ft_strlen(a->base);
	printf("wpbr: %u %ld %ld %ld\n", f->width, ft_strlen(a->prefix), ft_strlen(a->base),  pad_len);
	if (pad_len <= 0)
		return (ft_strjoin(a->prefix, a->base));
	pad = malloc(sizeof(char) * (pad_len + 1));
	if (!pad)
		return (NULL);
	ft_memset(pad, ' ', pad_len);
	pad[pad_len] = '\0';
	if (ft_is_in(f->flags, '-'))
		ret = ft_join3(a->prefix, a->base, pad);
	else if (ft_is_in(f->flags, '0') && !ft_is_in(f->flags, '.')
			&& ft_is_in("idxX", f->spec))
	{
		ft_memset(pad, '0', pad_len);
		ret = ft_join3(a->prefix, pad, a->base);
	}
	else 
		ret = ft_join3(pad, a->prefix, a->base);
	free(pad);
	printf("bibouh\n");
	return (ret);
}

/* take pointers to a properly initialized t_sarg and t_fspec, 
 * and what follows a % in a format string (1)
 * and returns the string to be output by ft_format_one 
 *
 * (1) this is needed when an invalid specifier is given 
 */
static char	*ft_prep_output(t_sarg *a, t_fspec *f, char const *s)
{
	if (!ft_is_in(SPECIFIERS, f->spec))
	{
		a->prefix = "%";
		a->base = ft_substr(s, 0, f->slen);
	}
	if (ft_is_in(f->flags, '.'))
	   ft_handle_precision(a, f->precision, f->spec);
	if (!a->base)
		return (NULL);
	if ((f->spec == 'i' || f->spec == 'd') && ft_strncmp(a->prefix, "-", 2))
	{
		if (ft_is_in(f->flags, '+'))
			a->prefix = "+";
		else if (ft_is_in(f->flags, ' '))
			a->prefix = " ";
	}
	if (f->spec == 'x' && ft_is_in(f->flags, '#'))
		a->prefix = "0x";
	if (f->spec == 'X' && ft_is_in(f->flags, '#'))
		a->prefix = "0X";
	printf("po : before exit \n");
	return (ft_handle_width(a, f));
}
	
/* prints 1 arg (or %), and return len of output string 
 * if pb do nothing and return -1 */
int	ft_format_one(char const *s, va_list va)
{
	char 	*out;
	t_fspec	f;
	t_sarg	a;
	int 	ret;

	if (*s == '%')
	{
		ft_putchar_fd(1, '%');
		return (1);
	}
	ft_parse_spec(s, &f);
	ft_set_sarg(&a, f.spec, va);
	printf("fo : thingies set\n");
	if (!a.base)
		return (-1);
	out = ft_prep_output(&a, &f, s);
	printf("fo : out set\n");
	ft_putstr_fd(out, 1);
	printf("%s %p\n", a.base, a.base);
	free(a.base);
	printf("2\n");
	if (!out)
		return (-1);
	ret = ft_strlen(out);
	free(out);
	return (ret);
}

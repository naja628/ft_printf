#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "t_fspec.h"
#include "printf_utils.h"
#include "ft_hexstr.h"
#include "ft_format_one.h"
#include "definitions.h"

/*a : pieces to build a string out of an argument
 * u prefix means not necessarily terminated (unterminated)
 * (hence the need for a len)
 * this is so we can output '\0' without too much
 * trouble and to avoid some unnecessary copying 
 */
typedef struct
{
	char	*ubasic;
	size_t	base_len;
	char	*prefix;
	char	*upad;
	size_t	pad_len;
}	t_sarg;

/* if terminated len is ignored and strlen is used instead */
void	ft_set_basic(t_sarg *a, char *ubasic, int terminated, size_t len)
{
	a->ubasic = ubasic;
	if (terminated)
		a->base_len = ft_strlen(ubasic);
	else 
		a->base_len = len;
}


/* wrapper around strdup that handles the case 
 * where s is NULL */
static void	ft_strdup_wrapper(t_sarg *a, char const *s)
{
	ft_set_basic(a, ft_strdup(s), 1, 0);
	if (!a->ubasic)
	{
		a->prefix = "(null)";
		ft_set_basic(a, malloc(0), 0, 0);
	}
}

/* consume 1 arg and convert it to a t_sarg 
 * ignoring flags.
 *
 * % is handled elsewhere (as it doesn't consume an arg).
 * 
 * num_arg is useful for the d/i case where the conversion is
 * a bit tricky due to signedness.
 * 
 * errors are indicated bya->base being NULL upon exit */
#include <stdio.h>
static void	ft_basic_ofarg(t_sarg *a, char spec, va_list args)
{
	int	num_arg;

	if (spec == 'd' || spec == 'i')
	{
		num_arg = va_arg(args, int);
		if (num_arg < 0)
			a->prefix = "-";
		ft_set_basic(a, ft_uitoa(ft_abs(num_arg)), 1, 0);
	}
	else if (spec == 'u')
		ft_set_basic(a, ft_uitoa(va_arg(args, t_uint)), 1, 0);
	else if (spec == 'x')
		ft_set_basic(a, ft_hexstr(va_arg(args, t_uint)), 1, 0);
	else if (spec == 'X')
		ft_set_basic(a, ft_heXstr(va_arg(args, t_uint)), 1, 0);
	else if (spec == 'p')
		ft_set_basic(a, ft_hexstr((size_t) va_arg(args, void *)), 1, 0);
	else if (spec == 'c')
		ft_set_basic(a, ft_challoc(va_arg(args, int)), 0, 1);
	else if (spec == 's')
		ft_strdup_wrapper(a, va_arg(args, char *));
}

/* set a->base to a new str taking the precision into account
 * if something wrong happensa->ubasic will always be NULL */
static void	ft_handle_precision(t_sarg *a, t_uint p, char spec)	
{
	char	*new_base;

	if (!a->ubasic || !ft_is_in("s" NUMERIC, spec))
		return ;
	if (spec == 's')
	{
		new_base = ft_substr(a->ubasic, 0, p);
		free(a->ubasic);
		ft_set_basic(a, new_base, 1, 0);
		return ;
	}
	if (!ft_strncmp(a->ubasic, "0", 2) && p == 0)
		a->base_len = 0;
	else if (p > a->base_len)
	{
		new_base = malloc(sizeof(char) * (p + 1));
		if (new_base)
		{
			ft_memset(new_base, '0', p);
			ft_strlcpy(new_base + p - a->base_len, a->ubasic, p - a->base_len);
		}
		free(a->ubasic);
		ft_set_basic(a, new_base, 1, p);
	}
}

static void	ft_set_prefix(t_sarg *a, t_fspec *f)
{
	if (f->spec == 'p' || (ft_is_in(f->flags, '#') && f->spec == 'x'))
		a->prefix = "0x";
	else if ((ft_is_in(f->flags, '#') && f->spec == 'X'))
		a->prefix = "0X";
	else if (ft_is_in("di", f->spec) && ft_strncmp(a->prefix, "-", 2))
	{
		if (ft_is_in(f->flags, '+'))
			a->prefix = "+";
		else if (ft_is_in(f->flags, ' '))
			a->prefix = " ";
	}
}

/* set the padding to be printed
 * return -1 when malloc error
 * 0 otherwise */
static int	ft_set_pad(t_sarg *a, t_fspec *f)
{
	char		*pad;
	ptrdiff_t	pad_len;

	pad_len = f->width - ft_strlen(a->prefix) - a->base_len;
	if (pad_len <= 0)
	{
		a->upad = malloc(0);
		a->pad_len = 0;
		return (0);
	}
	pad = malloc(sizeof(char) * pad_len);
	if (!pad)
		return (-1);
	if (ft_is_in(NUMERIC, f->spec) && ft_is_in(f->flags, '0')
		&& !ft_is_in(f->flags, '.') && !ft_is_in(f->flags, '-'))
		ft_memset(pad, '0', pad_len);
	else
		ft_memset(pad, ' ', pad_len);
	a->upad = pad;
	a->pad_len = (size_t) pad_len;
	return (0);
}

static void	ft_consume_sarg(t_sarg *a, t_fspec *f)
{
	if (ft_is_in(f->flags, '-'))
	{
		ft_putstr_fd(a->prefix, 1);
		write(1, a->ubasic, a->base_len);
		write(1, a->upad, a->pad_len);
	}
	else if (ft_is_in(f->flags, '0') && ft_is_in(NUMERIC, f->spec))
	{
		ft_putstr_fd(a->prefix, 1);
		write(1, a->upad, a->pad_len);
		write(1, a->ubasic, a->base_len);
	}
	else 
	{
		write(1, a->upad, a->pad_len);
		ft_putstr_fd(a->prefix, 1);
		write(1, a->ubasic, a->base_len);
	}
	free(a->upad);
	free(a->ubasic);
	return ;
}
		
/* prints 1 arg (or %), and return len of output string 
 * if pb do nothing and return -1 */
int	ft_format_one(char const *s, char *spec, va_list va)
{
	t_fspec	f;
	t_sarg	a;

	a.prefix = "";
	if (*s && *s == '%')
	{
		write(1, "%", 1);
		*spec = '%';
		return (1);
	}
	ft_parse_spec(s, &f);
	if (!ft_is_in(SPECIFIERS, f.spec))
		return (-1);
	ft_basic_ofarg(&a, f.spec, va);
	if (ft_is_in(f.flags, '.'))
		ft_handle_precision(&a, f.precision, f.spec);
	if (!a.ubasic)
		return (-1);
	ft_set_prefix(&a, &f);
	//printf("prefix set: it is %s\n", a.prefix);
	if (ft_set_pad(&a, &f) == -1)
		return (-1);
	ft_consume_sarg(&a, &f);
	*spec = f.spec;
	return (ft_strlen(a.prefix) + a.base_len + a.pad_len);
}

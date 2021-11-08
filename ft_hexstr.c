#include <stdlib.h>
#include "ft_hexstr.h"

/* note : size of 0 needs to be 1 */
static size_t	ft_num_sz_hex(size_t n)
{
	if (n < 16)
		return (1);
	return (1 + ft_num_sz_hex(n / 16));
}

static void	ft_hexstr_helper(char *units_place, size_t n)
{
	char	*digits;

	digits = "0123456789abcdef";
	*units_place = digits[n % 16];
	if (n >= 16)
		ft_hexstr_helper(units_place - 1, n / 16);
}

char	*ft_hexstr(size_t n)
{
	char	*s;
	size_t	sz;

	sz = ft_num_sz_hex(n);
	s = malloc(sizeof(char) * (1 + sz));
	if (!s)
		return (NULL);
	ft_hexstr_helper(s + sz - 1, n);
	s[sz] = '\0';
	return (s);
}

static void	ft_heXstr_helper(char *units_place, size_t n)
{
	char	*digits;

	digits = "0123456789ABCDEF";
	*units_place = digits[n % 16];
	if (n >= 16)
		ft_heXstr_helper(units_place - 1, n / 16);
}


char	*ft_heXstr(size_t n)
{
	char	*s;
	size_t	sz;

	sz = ft_num_sz_hex(n);
	s = malloc(sizeof(char) * (1 + sz));
	if (!s)
		return (NULL);
	ft_heXstr_helper(s + sz - 1, n);
	s[sz] = '\0';
	return (s);
}

#ifdef TEST
# include <stdlib.h>
# include <stdio.h>

int main(int ac, char **av)
{
	if (ac != 2)
		exit (-1);
	size_t putme;
	char *out;
	putme = atoi(av[1]);
	out = ft_hexstr(putme);
	printf("%s\n", out);
	free (out);
	return (0);
}

#endif

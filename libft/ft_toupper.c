#include "libft.h"

int	ft_toupper(int c)
{
	int diff = 'A' - 'a';

	if ('a' <= c && c <= 'z')
		return (c + diff);
	else 
		return (c);
}

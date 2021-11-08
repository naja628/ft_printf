#include "libft.h"

int ft_tolower(int c)
{
	int diff = 'a' - 'A';

	if ('A' <= c && c <= 'Z')
		return (c + diff);
	else 
		return (c);
}

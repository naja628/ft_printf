#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*last_instance;

	last_instance = NULL;
	while (*s)
	{
		if (*s == (char) c)
			last_instance = (char *) s;
		++s;
	}
	if ((char) c == '\0')
		last_instance = (char *) s;
	return (last_instance);
}

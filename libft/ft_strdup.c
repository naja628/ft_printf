#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	n;
	char	*dup;

	if (!s)
		return (NULL);
	n = ft_strlen(s);
	dup = malloc(sizeof(char) * (n + 1));
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, s, n + 1);
	return (dup);
}

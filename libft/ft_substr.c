#include <stdlib.h>
#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	s_len;

	s_len = ft_strlen(s);
	if (start > s_len)
		len = 0;
	if (len > s_len - start)
		len = s_len - start;
	sub = malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	if (len == 0)
		*sub = '\0';
	else
		ft_strlcpy(sub, s + start, len + 1);
	return (sub);
}

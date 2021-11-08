#include <stdlib.h>
#include "libft.h"

/* note : using strlact makes us pass unnecessarily through 
 * s1 twice, but this seems pretty minor */
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*concat;
	size_t	sz;

	sz = ft_strlen(s1) + ft_strlen(s2) + 1;
	concat = malloc(sizeof(char) * sz);
	if (!concat)
		return (NULL);
	ft_strlcpy(concat, s1, sz);
	ft_strlcat(concat, s2, sz);
	return (concat);
}

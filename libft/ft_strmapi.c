#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char			*image;
	unsigned int	i;

	image = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!image)
		return (NULL);
	i = 0;
	while (s[i])
	{
		image[i] = f(i, s[i]);
		++i;
	}
	image[i] = '\0';
	return (image);
}

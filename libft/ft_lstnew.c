#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*createme;

	createme = malloc(sizeof(t_list));
	if (!createme)
		return (NULL);
	createme->content = content;
	createme->next = NULL;
	return (createme);
}

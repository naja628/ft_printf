#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	if (lst == NULL)
		return (0);
	return (1 + ft_lstsize(lst -> next));
}

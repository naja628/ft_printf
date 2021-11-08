#ifndef PRINTF_UTILS_H
# define PRINTF_UTILS_H

typedef unsigned int	t_uint;

int		ft_is_in(char const *set, char c);
t_uint	ft_abs(int n);
char	*ft_challoc(char c);
char	*ft_uitoa(t_uint n);

#endif

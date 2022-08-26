#include "libft.h"

char	*ft_firstword(char	*s)
{
	char	**str;

	str = ft_split(s, ' ');
	return (str[0]);
}

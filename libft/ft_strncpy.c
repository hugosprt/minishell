#include "libft.h"

char	*ft_strncpy(char *src, int size)
{
	int		i;
	char	*dst;

	i = 0;
	dst = malloc(sizeof(char) * size);
	while (i < size)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

#include "libft.h"

char	*n_strjoin(unsigned int n, ...)
{
	va_list			list;
	unsigned int	i;
	char			*str;
	char			*tmp1;
	char			*tmp2;

	va_start(list, n);
	i = 0;
	str = NULL;
	while (i < n)
	{
		tmp1 = va_arg(list, char *);
		if (str == NULL)
			str = ft_strdup(tmp1);
		else
		{
			tmp2 = ft_strjoin(str, tmp1);
			free(str);
			str = tmp2;
		}
		i++;
	}
	return (va_end(list), str);
}

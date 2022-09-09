#include "libft.h"

void	printtab_fd(char **t, int fd)
{
	int	i;

	i = 0;
	while (t[i])
	{
		ft_putstr_fd(t[i], fd);
		write(fd, "\n", 1);
		i++;
	}
}

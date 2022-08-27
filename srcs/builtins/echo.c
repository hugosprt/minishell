#include "../../includes/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
	{
		i++;
		if (i == 2)
			return (s1[i - 1] - s2[i - 1]);
	}
	return (s1[i] - s2[i]);
}

int	is_n(char *str, int n)
{
	int	i;

	i = 0;
	if (str[0] == '-' && str[1] == 'n')
	{
		i++;
		while (str[i] == 'n')
			i++;
		if (str[i] != ' ' && str[i] != '\0')
			return (n);
		while (str[i] == ' ')
			i++;
	}
	if (str[i] == '-' && str[i + 1] == 'n')
		i = is_n((str + i), i + n);
	return (i + n);
}

int	echo(t_shell *s)
{
	t_parsing	*p;
	int			n;
	char		*str;

	p = s->parsing;
	str = p->arg;
	n = 0;
	if (str)
	{
		n = is_n(str, 0);
		ft_putstr_fd((str + n), p->fd_out);
	}
	if (n == 0)
		ft_putstr_fd("\n", p->fd_out);
	if (p->fd_out != 1)
		close(p->fd_out);
	return (0);
}

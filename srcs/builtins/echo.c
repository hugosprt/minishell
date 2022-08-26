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

int is_flag(char *str)
{
	if (*str == '-')
	{
		while (str && is_empty(*str))
		{
			if (*str != 'n')
				return (0);
		}
	}
	else
		return (0);
	return (1);
}


int	is_n(char *str)
{
	int i;
	i = 0;
	while (*str)
	{
		i = is_flag(str);
		str++;
	}
	return (i);
}

int	echo(t_shell *s)
{
	t_parsing	*p;
	int	n;
	char *str;

	p = s->parsing;
	str = p->arg;
	n = 1;
	if (str)
	{
		n = is_n(str);
		
		ft_putstr_fd(str, p->fd_out);
		if (p->fd_out != 1)
			close(p->fd_out);
	}
	if (n == 1)
		ft_putstr_fd("\n", 1);
	return (0);
}

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

int	is_n(char *str)
{
	int	a;
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[0] != '-')
	{
		return (0);
	}
	else
	{
		i++;
		a = i;
		while (str[i])
		{
			if (str[i] != 'n' || !str[i])
				return (0);
			i++;
		}
		if (i == a)
			return (0);
	}
	return (1);
}

int	echo(t_shell *s)
{
	t_parsing	*p;
	int	i;
	int	n;

	p = s->parsing;
	i = 0;
	n = 1;
	i = 1;
	if (p->arg)
	{
		while (is_n(p->arg++))
			n = 0;
		if (p->arg)
		{
			while (p->arg)
			{
				ft_putstr_fd(p->arg, 1);
				i++;
				if (p->arg)
					ft_putstr_fd(" ", 1);
			}
		}
	}
	if (n == 1)
		ft_putstr_fd("\n", 1);
	return (0);
}

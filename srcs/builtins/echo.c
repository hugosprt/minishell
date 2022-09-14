#include "../../includes/minishell.h"

static char	**ft_free(char	**ret)
{
	int	k;

	k = 0;
	while (ret[k])
		k++;
	while (k >= 0)
	{
		free(ret[k]);
		k--;
	}
	free(ret);
	return (NULL);
}

void	free_stuff(t_parsing *p)
{
	ft_free(p->arg);
	p->arg = NULL;
	p->com = NULL;
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

void	echo(t_shell *shell, int i, int n)
{
	char	**str;

	str = shell->parsing->arg;
	if (str[i])
	{
		while (is_n(str[i]))
		{
			n = 0;
			i++;
		}
		if (str[i])
		{
			while (str[i])
			{
				ft_putstr_fd(str[i], 1);
				i++;
				if (str[i])
					ft_putstr_fd(" ", 1);
			}
		}
	}
	if (n == 1)
		ft_putstr_fd("\n", 1);
	s()->sig->ret = 0;
}

#include "../../includes/minishell.h"

int	is_good(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (!isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(char **str)
{
	int	sta;

	if (str[1])
	{
		if (!is_good(str[1]))
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("minishell: exit: status", 2);
			ft_putstr_fd("numeric argument required\n", 2);
			exit(2);
		}
		if (str[2])
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			s()->sig->ret = 1;
			return (0);
		}
		sta = ft_atoi(str[1]);
		ft_putstr_fd("exit\n", 2);
		exit(sta);
	}
	ft_putstr_fd("exit\n", 2);
	exit(0);
}

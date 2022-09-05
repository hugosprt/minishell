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

int	ft_exit(char *str)
{
	int	sta;

	if (str)
	{
		if (!is_good(str))
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("bash: exit: status numeric argument required\n", 2);
			exit(2);
		}
		sta = ft_atoi(str);
		ft_putstr_fd("exit\n", 2);
		exit(sta);
	}
	ft_putstr_fd("exit\n", 2);
	exit(0);
}

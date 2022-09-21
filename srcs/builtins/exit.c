#include "../../includes/minishell.h"

static void	print_err(int pipe, char **str)
{
	if (!pipe)
		ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(str[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	s()->sig->ret = 2;
	if (!pipe)
		exit(2);
}

static int	is_good(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(int pipe, char **str)
{
	int	sta;

	sta = 0;
	if (str[1])
	{
		if (!is_good(str[1]))
			print_err(pipe, str);
		else if (str[2])
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			s()->sig->ret = 1;
			return (0);
		}
		else
		{
			sta = ft_atoi(str[1]);
			s()->sig->ret = sta;
		}
	}
	if (!pipe)
		return (ft_putstr_fd("exit\n", 2), exit(sta), 0);
	return (0);
}

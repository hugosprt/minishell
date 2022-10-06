/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpol <rpol@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:39:55 by rpol              #+#    #+#             */
/*   Updated: 2022/10/06 14:07:56 by rpol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	int	ft_isdigit3(char str)
{
	if (str >= '0' && str <= '9')
		return (1);
	return (0);
}

static long long int	ft_atoll(const char *str)
{
	int				i;
	long long int	nb;
	int				sign;

	nb = 0;
	i = 0;
	sign = 1;
	while (str[i] && ((str[i] <= 13 && str[i] >= 9) || str[i] == ' '))
	{
		i++;
	}
	if (str[i] == '+' && ft_isdigit3(str[i + 1]))
		i++;
	if (str[i] == '-' && ft_isdigit3(str[i + 1]))
	{
		sign = -1;
		i++;
	}
	while (str[i] && ft_isdigit3(str[i]))
	{
		nb = str[i] - 48 + nb * 10;
		i++;
	}
	return (nb * sign);
}

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
	int				sta;
	long long int	nb;

	sta = 0;
	if (str[1])
	{
		nb = ft_atoll(str[1]);
		if (!is_good(str[1]) || nb > INT32_MAX || nb < INT32_MIN)
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

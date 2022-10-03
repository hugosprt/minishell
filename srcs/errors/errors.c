/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpol <rpol@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:40:55 by rpol              #+#    #+#             */
/*   Updated: 2022/10/03 13:43:50 by rpol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	syntax_problem(t_shell *shell, int error_value)
{
	const char	*error[6] = {"|", "<", ">", "<<", ">>", "newline"};

	ft_putstr_fd("minishell", 2);
	ft_putstr_fd(": syntax error near unexpected token `", 2);
	ft_putstr_fd((char *)error[error_value], 2);
	ft_putstr_fd("'\n", 2);
	shell->error = 1;
	s()->sig->ret = 2;
}

void	quote_problem(t_shell *shell, int error_value)
{
	const char	*error[2] = {"\'", "\""};

	ft_putstr_fd("minishell", 2);
	ft_putstr_fd(": unclosed token detected `", 2);
	ft_putstr_fd((char *)error[error_value], 2);
	ft_putstr_fd("'\n", 2);
	shell->error = 1;
	s()->sig->ret = 2;
}

void	path_not_set(t_parsing *p)
{
	write(2, "minishell:  no such file or directory: ", 39);
	write(2, p->com, ft_strlen(p->com));
	write(2, "\n", 1);
	exit (127);
}

void	path_error( char *path, char *cwd)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	free(cwd);
	s()->sig->ret = 1;
}

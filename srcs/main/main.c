/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hspriet <hspriet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:42:07 by rpol              #+#    #+#             */
/*   Updated: 2022/10/09 15:26:05 by hspriet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_List	init(t_List st)
{
	char		*test[4];
	char		cwd[1024];

	s()->i = 1;
	test[0] = "NULL";
	test[1] = "258";
	test[2] = "PATH=/bin";
	test[3] = ft_strjoin("PWD=", getcwd(cwd, sizeof(cwd)));
	test[4] = NULL;
	return (add_list(test, st));
}

void	freelex(t_lexer *l)
{
	t_lexer	*tmp;

	while (l->next)
	{
		tmp = l;
		l = l->next;
		if (tmp->koi == ARG)
			free(tmp->str);
		free(tmp);
	}
	free (l);
}

void	minishell(t_shell *shell, t_List st)
{
	while (1)
	{
		shell->error = 0;
		shell->lexer = NULL;
		shell->st = st;
		prompt(shell);
		lexer(shell);
		trimer(shell, st);
		if (parsing(shell))
			free(shell->parsing);
		if (shell->error || shell->lexer)
			freelex(shell->lexer);
	}
}

int	main(int ac, char **av, char **env)
{
	t_shell		*shell;
	t_List		st;

	if (isatty(1) == 0 || isatty(0) == 0)
		return (0);
	(void) ac;
	(void) av;
	st = NULL;
	shell = s();
	if (!shell)
		return (0);
	s()->i = 0;
	signal_gestion(shell);
	if (!env || !(*env))
		st = init(st);
	else
	{
		push_list_back(&st, "258", " ");
		st = add_list(env, st);
	}
	shell->str_env = env;
	shell->error = 0;
	minishell(shell, st);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpol <rpol@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:42:07 by rpol              #+#    #+#             */
/*   Updated: 2022/10/03 13:44:16 by rpol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	freelex(t_lexer *l)
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

void	print_lexer(t_lexer *s)
{
	int			i;
	const char	*token[8] = {"ARG", "END", "PIPE", "R_REDIR", "L_REDIR",
		"RR_REDIR", "LL_REDIR", NULL};

	i = 0;
	if (s == NULL)
		return ;
	while (s != NULL)
	{
		printf("%s ... ", token[s->koi]);
		if (s->koi == 0)
			printf(" : -%s- ... ", s->str);
		s = s->next;
		i++;
	}
	printf("\n");
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
	char		*test[5];
	char		cwd[1024];

	test[0] = "NULL";
	test[3] = "PATH=/bin";
	test[1] = ft_strjoin("PWD=", getcwd(cwd, sizeof(cwd)));
	test[2] = "_=/usr/bin/env";
	test[4] = NULL;
	(void) ac;
	(void) av;
	st = NULL;
	shell = s();
	if (!shell)
		return (0);
	signal_gestion(shell);
	if (!env || !(*env))
		st = add_list(test, st);
	else
		st = add_list(env, st);
	shell->str_env = env;
	shell->error = 0;
	minishell(shell, st);
	return (s()->sig->ret);
}

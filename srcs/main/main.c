#include "../../includes/minishell.h"

static void	freelex(t_lexer *l)
{
	t_lexer	*tmp;

	while (l->next)
	{
		tmp = l;
		l = l->next;
		free(tmp);
	}
	free (l);
}

void	print_lexer(t_lexer *s)
{
	int	i;
	const char	*token[8] = {"ARG", "END", "PIPE","R_REDIR", "L_REDIR",
		"RR_REDIR", "LL_REDIR",NULL};

	i = 0;
	if (s == NULL)
		return ;
	while (s != NULL)
	{
		printf("%s ... ", token[s->koi]);
		if(s->koi == 0)
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
		//(void) st;		
		shell->error = 0;
		shell->lexer = NULL;
		shell->st = st;
		prompt(shell);
		lexer(shell);
		trimer(shell, st);
		//print_lexer(s->lexer);
		parsing(shell);
		free(shell->parsing);
		freelex(shell->lexer);
	}
}

int	main(int ac, char **av, char **env)
{
	t_shell		*shell;
	t_List		st;

	(void) ac;
	(void) av;

	st = NULL;
	shell = s();
	if (!shell)
		return (0);
	signal_gestion(shell);
	if (!env || !(*env))
		env = NULL;
	else
		st = add_list(env, st);
	shell->str_env = env;
	shell->error = 0;
	minishell(shell, st);
	return (s()->sig->ret);
}

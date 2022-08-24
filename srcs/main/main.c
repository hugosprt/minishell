#include "../../includes/minishell.h"


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
		//printf("num %d  =",	s->koi);
		printf("%s ........ ", token[s->koi]);
		s = s->next;
		i++;
	}
	printf("\n");
}



void	minishell(t_shell *s)
{
	t_lexer	*lex;

	lex = malloc(sizeof(t_lexer));
	lex->prev = NULL;
	lex->next = NULL;
	while (1)
	{
		s->lexer = NULL;
		prompt(s);
		lexer(s);
		print_lexer(s->lexer);
		printf("%s\n", s->prompt);
		lex->str = s->prompt;
		parsing(lex);
	}
}

int	main(int ac, char **av, char **env)
{
	t_shell	*shell;

	(void) ac;
	(void) av;
	shell = s();
	if (!shell)
		return (0);
	if (!add_list(env, shell->env))
		return (0);
	minishell(shell);
}

#include "../../includes/minishell.h"

int	ft_csch(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

t_parsing	*parsing(t_lexer *lex)
{
	t_parsing	*par;

	if (!lex || !lex->str)
		return (NULL);
	par = init_par(lex);
	return (par);
}

t_parsing	*redir(t_parsing *par, t_lexer *lex)
{
	if (par->fd_out != 1)
		printf("closed fd out :%d__%d\n", par->fd_out, close(par->fd_out));
	if (par->fd_in != 0)
		printf("closed fd in :%d__%d\n", par->fd_in, close(par->fd_in));
	if (lex->prev->koi == R_REDIR)
	{
		par->fd_out = open(lex->str, O_CREAT | O_TRUNC | O_WRONLY, 00644);
		printf("fd out R name %s code %d\n", lex->str, par->fd_out);
	}
	else if (lex->prev->koi == RR_REDIR)
	{
		par->fd_out = open(lex->str, O_CREAT | O_APPEND | O_WRONLY, 00644);
		printf("fd out RR name %s code %d\n", lex->str, par->fd_out);
	}
	else if (lex->prev->koi == L_REDIR)
	{
		par->fd_in = open(lex->str, O_RDONLY);
		if (par->fd_in == -1)
			return (printf("%s: No such file or directory\n", lex->str), par);
		printf("fd in L name %s code %d\n", lex->str, par->fd_in);
	}
	return (par);
}

// t_parsing	*pipe(t_parsing *par)
// {

// }

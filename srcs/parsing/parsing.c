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

t_parsing	*redir(t_parsing *par, t_lexer *lex, int i, char *s)
{
	char *str;

	str = ft_firstword(lex->str);
	if (par->fd_out != 1)
		printf("closed fd :%d__%d\n", par->fd_out, close(par->fd_out));
	if (lex->prev->koi == R_REDIR)
	{
		par->fd_out = open(str, O_CREAT | O_RDWR | O_TRUNC);
		printf("fd out R name %s code %d\n", str, par->fd_out);
	}
	else if (lex->prev->koi == RR_REDIR)
	{
		par->fd_out = open(str, O_CREAT | O_RDWR | O_APPEND);
		printf("fd out RR name %s code %d\n", str, par->fd_out);
	}
	if (ft_csch(lex->str, ' '))
	{
		while (s[i] != ' ')
			i++;
		par->arg = ft_strjoin(par->arg, s + i);
	}
	return (par);
}

// t_parsing	*pipe(t_parsing *par)
// {

// }

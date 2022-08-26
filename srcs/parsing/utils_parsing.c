#include "../../includes/minishell.h"

static char	*find_com(char *str)
{
	char	*com;
	int		len;
	int		i;

	i = 0;
	len = 0;
	while (str[len] != ' ' && str[len])
		len++;
	com = malloc(sizeof(char) * (len + 1));
	while (i < len)
	{
		com[i] = str[i];
		i++;
	}
	com[i] = '\0';
	return (com);
}

static char	*cut_arg(char *str)
{
	int	i;

	i = 0;
	while (str[i] != ' ' && str[i])
		i++;
	if (str[i] == ' ' && str[i + 1] != '\0')
		return ((char *)(str + i + 1));
	return (NULL);
}

static t_parsing	*first_link(t_parsing *par, t_lexer *lex)
{

	while (lex->koi != END)
	{
		if (lex->koi == R_REDIR || lex->koi == RR_REDIR)
		{
			par = redir(par, lex->next, 0, lex->next->str);
			lex = lex->next;
		}
		else if (lex->koi == ARG)
		{
			par->arg = ft_strjoin(par->arg, ft_strjoin(" ", lex->str));
		}
		// if (lex->koi == PIPE)
		// 	par = ft_pipe(par);
		if (lex->koi != END)
			lex = lex->next;
	}
	return (par);
}

t_parsing	*init_par(t_lexer *lex)
{
	t_parsing	*par;

	par = malloc(sizeof(t_parsing));
	par->prev = NULL;
	par->next = NULL;
	par->com = find_com(lex->str);
	par->arg = cut_arg(lex->str);
	par->fd_out = 1;
	first_link(par, lex->next);
	printf("com :%s\n", par->com);
	printf("arg :%sR\n", par->arg);

	return (par);
}

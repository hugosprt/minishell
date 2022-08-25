#include "../../includes/minishell.h"

static int	firt_link(t_parsing *par, t_lexer *lex)
{
	par = malloc(sizeof(t_parsing));
	par->prev = NULL;
	par->next = NULL;
	par->com = find_com(lex->str);
	par->arg = cut_arg(lex->str);
	while(lex->next->koi != PIPE)
	{
	
	}
	return (0);
}

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

t_parsing	*init_par(t_lexer *lex)
{
	t_parsing	*tmp;
	t_parsing	*par;

	if (!lex->prev)
	{
		firts_link(par);
		lex = lex->next;
	}
	printf("com :%s\n", par->com);
	printf("arg :%sR\n", par->arg);
	while (lex)
	{
		tmp = par;
		par->next = malloc(sizeof(t_parsing));
		par = par->next;
		par->prev = tmp;
		par->next = NULL;
		par->com = find_com(lex->str);
		par->arg = cut_arg(lex->str);
		lex = lex->next;
	}
	return (par);
}

#ifndef STRUCT_H
# define STRUCT_H

enum{
	ARG,
	REDIR_D,
	REDIR_G,
	REDIR_DD,
	REDIR_GG,
};

typedef struct t_ListElement
{
	char			    	*var;
    char                    *value;
	struct t_ListElement	*next;
}t_ListElement,	*t_List;


typedef struct s_sig
{
	int				ret;
	int			sigint;
	int			sigquit;
	pid_t		pid;
}		t_sig;

typedef struct s_lexer
{
	char	*str;
}	t_lexer;

typedef	struct s_shell
{
	t_ListElement	*env;
	t_lexer			*lexer;
	t_sig			*sig;
	char	*prompt;

}	t_shell;

#endif
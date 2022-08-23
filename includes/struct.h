#ifndef STRUCT_H
# define STRUCT_H

typedef enum e_koi{
	ARG,
	REDIR_D,
	REDIR_G,
	REDIR_DD,
	REDIR_GG,
	PIPE,
} t_koi;


typedef struct s_lexer
{
	struct s_lexer	*prev;
	struct s_lexer	*next;
	char			*str;
	t_koi			koi;
}	t_lexer;

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

typedef	struct s_shell
{
	t_ListElement	*env;
	t_lexer			*lexer;
	t_sig			*sig;
	int				error;
	char	*prompt;

}	t_shell;

#endif
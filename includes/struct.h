#ifndef STRUCT_H
# define STRUCT_H

typedef enum e_koi{
	ARG,
	END,
	PIPE,
	R_REDIR,
	L_REDIR,
	RR_REDIR,
	LL_REDIR,
}	t_koi;

typedef enum e_quote{
	S_QUOTES = '\'',
	D_QUOTES = '\"',
	DOLLAR,
	MIX_QUOTES,
	NOT_YET,
}	t_quote;


typedef struct s_lexer
{
	struct s_lexer	*prev;
	struct s_lexer	*next;
	char			*str;
	t_koi			koi;
	t_quote			quote;
}	t_lexer;

typedef struct t_ListElement
{
	char					*var;
	char					*value;
	struct t_ListElement	*next;
}t_ListElement,	*t_List;

typedef struct s_parsing
{
	struct s_parsing	*prev;
	struct s_parsing	*next;
	char				*com;
	char				*arg;
	char				**car;
	int					*fd_in;
	int					fd_out;
}	t_parsing;

typedef struct s_sig
{
	int				ret;
	int				sigint;
	int				sigquit;
	pid_t			pid;
}		t_sig;

typedef struct s_shell
{
	t_ListElement	*env;
	t_lexer			*lexer;
	t_sig			*sig;
	int				error;
	char			*prompt;

}	t_shell;

#endif
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
	char				*com;
	char				**arg;
	int					std_in;
	int					std_out;
	int					prev_in;
	int					block[2];
	int					pipe[2];
	int					status;
	struct s_shell		*s;
	t_lexer				*l;
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
	char			**str_env;
	t_lexer			*lexer;
	t_parsing		*parsing;
	t_sig			*sig;
	int				error;
	char			*prompt;
	int				pid;
	t_List			st;

}	t_shell;

#endif
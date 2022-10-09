/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpol <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:37:28 by rpol              #+#    #+#             */
/*   Updated: 2022/10/09 14:39:02 by rpol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int					pipe[2];
	int					nb_pipe;
	int					status;
	int					fd;
	char				*error;
	struct s_shell		*sh;
	t_lexer				*l;
}	t_parsing;

typedef struct s_sig
{
	int				ret;
	int				sigint;
	int				sigquit;
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
	char			*tmp;
	int				t;
	int				i;
	int				b;
	int				fin;
}	t_shell;

#endif
#ifndef STRUCT_H
# define STRUCT_H

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
	char	*prompt;

}	t_shell;

extern	t_sig glob;

#endif
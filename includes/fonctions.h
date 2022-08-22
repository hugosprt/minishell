#ifndef FONCTIONS_H
# define FONCTIONS_H

/**
 * @brief builtins
 * 
 */

void	get_signal(int sig);

/**
**		unset.c
**/
void	ft_unset(t_List st, char **arg);
int		is_in_env(t_List st, char *var_name, char *var_value);

/**
**		pwd.c
**/
void	pwd(void);

/**
**		echo.c
**/
int		echo(char **str);

/**
**		cd.c
**/
void	cd(t_List st,  char *path);

char	**ft_trim_equal(char const *s, char charset);
void    ft_export(t_List st, char **arg);
void	push_list_back(t_List *st, char *var_name, char *var_value);


/**
**		env.c
**/
void is_var(char *str, t_List st);
void    ft_export(t_List st, char **arg);
void	create_env(char **envp);
void print_env(t_List st);
t_List	add_list(char **tab, t_List sta);

/**
**		utils_env.c
**/
char	**ft_trim_equal(char const *s, char charset);

void	prompt(t_shell *s);


#endif
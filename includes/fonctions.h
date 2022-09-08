#ifndef FONCTIONS_H
# define FONCTIONS_H

/**
 * @brief builtins
 * 
 */

int			ft_exit(char **str);

void		get_signal(int sig);

/**
**		unset.c
**/
void		ft_unset(t_List st, char **arg);
int			is_in_env(t_List st, char *var_name, char *var_value);

/**
**		pwd.c
**/
void		pwd(void);

/**
**		echo.c
**/
void		echo(t_shell *shell);

/**
**		cd.c
**/
void		cd(t_List st, char *path);
char		**ft_trim_equal(char const *s, char charset, int r, int k);
void		ft_export(t_List st, char **arg);
void		push_list_back(t_List *st, char *var_name, char *var_value);

/**
**		env.c
**/
void		is_var(char *str, t_List st);
void		ft_export(t_List st, char **arg);
void		create_env(char **envp);
void		print_env(t_shell *shell, t_List st);
t_List		add_list(char **tab, t_List sta);

/**
**		utils_env.c
**/
//char	**ft_trim_equal(char const *s, char charset);

void		prompt(t_shell *s);

t_shell		*s(void);
int			lexer(t_shell *s);
void		skip_white_space(t_shell *s);
int			is_empty(char c);
int			add_token_back(t_lexer **head, t_koi token, t_quote quote);

void		add_token_lr(t_shell *s);
void		add_token_rr(t_shell *s);
void		add_token_pip(t_shell *s);

int			is_separator(char c);
void		add_token_arg(t_shell *s);
int			first_arg(t_shell *s, t_lexer *l);
int			test_pipe(t_shell *s, t_lexer *l);
/**
**		parsing.c
**/

int			parsing(t_shell *s);
int			error(t_shell *sh, int i);

/**
**		utils_parsing.c
**/

int			make_block(t_shell *s);

/**
**		redir.c
**/

void		dup2_close(int fd, int old_fd);

t_lexer		*redir(t_parsing *par);

/**
**		redir.c
**/

void		ici_fichier(t_parsing *p);

//t_parsing	*ft_pipe(t_parsing *par);

int			find_last_elem(t_lexer *l);
t_lexer		*find_last_elem2(t_lexer *l);
void		index_quotes(t_shell *s);
int			find_last_elem(t_lexer *l);
t_lexer		*find_last_elem2(t_lexer *l);
void		index_quotes(t_shell *s);
char		*ft_strldup(const char *source, int size);
void		trimer(t_shell *s, t_List st);
void		exec(t_shell *s);
int			ft_strcmp_2(const char *str1, const char *str2);
void		syntax_problem(t_shell *shell, int error_value);
void		quote_problem(t_shell *shell, int error_value);
void		get_signal(int sig);
void		signal_gestion(t_shell *s);
void		ctrl_d_exit(void);
void	path_not_set(t_parsing *p);
void	path_error( char *path, char *cwd);
#endif
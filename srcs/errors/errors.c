#include "../../includes/minishell.h"

void syntax_problem(t_shell *shell, int error_value)
{
	const char	*error[6] = {"|", "<", ">", "<<", ">>", "newline"};

	ft_putstr_fd("minishell", 2);
	ft_putstr_fd(": syntax error near unexpected token `", 2);
	ft_putstr_fd((char *)error[error_value], 2);
	ft_putstr_fd("'\n", 2);
	shell->error = 1;
	s()->sig->ret = 2;
}

void	quote_problem(t_shell *shell, int error_value)
{
	const char	*error[2] = {"\'", "\""};

	ft_putstr_fd("minishell", 2);
	ft_putstr_fd(": unclosed token detected `", 2);
	ft_putstr_fd((char *)error[error_value], 2);
	ft_putstr_fd("'\n", 2);
	shell->error = 1;
	s()->sig->ret = 2;
}
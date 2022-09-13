#include "../../includes/minishell.h"

int	is_in_env(t_List st, char *var_name, char *var_value)
{

	t_List tmp;

	tmp = st;
	if (tmp == NULL)
		return (0);
	while (tmp != NULL)
	{
		if (!ft_strcmp_2(var_name, st->var))
		{
			tmp->var = var_name;
			tmp->value = var_value;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	is_var(char *str, t_List st)
{
	int		i;
	char	**ret;
	char	*var_name;
	char	*var_value;

	i = 0;
	if (!ft_isalpha(str[i]))
	{
		ft_putstr_fd("minishell: export: : not a valid identifier\n", 2);
		return ;
	}
	while (str[i] && (ft_isalnum(str[i]) || (str[i] == '_')))
		i++;
	if (str[i] && str[i] == '=')
	{
		ret = ft_trim_equal(str, '=', 1, -1);
		if (ret[0] == NULL)
		{
			ft_putstr_fd("bash: export: : not a valid identifier\n", 2);
			return ;
		}
		else
			var_name = ret[0];
		if (ret[1] == NULL)
			var_value = NULL;
		else
			var_value = ret[1];
		free(ret);
		if (!is_in_env(st, var_name, var_value))
			push_list_back(&st, var_name, var_value);
	}
}

void	export_only(t_List st)
{
	int	i;

	i = 0;
	if (st == NULL)
		return ;
	while (st != NULL)
	{
		printf("%s=", st->var);
		printf("%s\n", st->value);
		st = st->next;
		i++;
	}
}

void	ft_export(t_List st, char **arg)
{
	int	i;

	i = 0;
	if (arg == NULL)
	{
		printf("le tri\n");
		return ;
	}
	while (arg[i])
	{
		is_var(arg[i], st);
		i++;
	}
	s()->sig->ret = 0;
}

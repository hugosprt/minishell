#include "../../includes/minishell.h"

static void	fonction_du_sale(int i, char *str, char **ret, t_List st)
{
	char	*var_name;
	char	*var_value;

	while (str[i] && (ft_isalnum(str[i]) || (str[i] == '_')))
			i++;
	if (str[i] && str[i] == '=')
	{
		ret = ft_trim_equal2(str, '=', 1, ret);
		if (ret[0] == NULL)
			write(2, "minishell: export: : not a valid identifier\n", 44);
		else
			var_name = ret[0];
		i = 0;
		if (!ret[1])
			var_value = NULL;
		else
			var_value = ret[1];
		if (!is_in_env(st, var_name, var_value))
			push_list_back(&st, var_name, var_value);
	}
}

int	is_in_env(t_List st, char *var_name, char *var_value)
{
	t_List	tmp;

	tmp = st;
	if (tmp == NULL)
		return (0);
	while (tmp != NULL)
	{
		if (!ft_strcmp_2(var_name, tmp->var))
		{
			free(var_name);
			free(tmp->value);
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

	i = 1;
	ret = malloc(sizeof(char *) * (2));
	if (!ret)
		return ;
	if (!ft_isalpha(str[i]))
		write(2, "minishell: export: : Not a valid identifier\n", 44);
	else
		fonction_du_sale(i, str, ret, st);
	free(ret);
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

	i = 1;
	if (arg == NULL)
		return ;
	while (arg[i])
	{
		is_var(arg[i], st);
		i++;
	}
	s()->sig->ret = 0;
}

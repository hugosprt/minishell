#include "../../includes/minishell.h"

void	push_list_back(t_List *st, char *var_name, char *var_value)
{
	t_ListElement	*new_list;
	t_ListElement	*last;

	last = *st;
	new_list = malloc(sizeof(*new_list));
	if (new_list == NULL)
		return ;
	new_list->var = var_name;
	new_list->value = var_value;
	new_list->next = NULL;
	if (*st == NULL)
	{
		*st = new_list;
		return ;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new_list;
}

t_List	add_list(char **tab, t_List sta)
{
	int		j;
	char	**ret;
	char	*var_name;
	char	*var_value;

	j = 1;
	while (tab[j])
	{
		ret = ft_trim_equal(tab[j], '=', 1, -1);
		if (ret[0] == NULL)
		{
			ft_putstr_fd("bash: export: : not a valid identifier", 1);
			return (NULL);
		}
		else
			var_name = ret[0];
		if (ret[1] == NULL)
			var_value = " ";
		else
			var_value = ret[1];
		push_list_back(&sta, var_name, var_value);
		free(ret);
		j++;
	}
	return (sta);
}

void	print_env(t_List st, t_shell *s)
{
	int	i;

	i = 0;
	if (st == NULL)
		return ;
	while (st != NULL)
	{
		ft_putstr_fd(st->var, s->parsing->fd_out);
		ft_putstr_fd("=", s->parsing->fd_out);
		ft_putstr_fd(st->value, s->parsing->fd_out);
		ft_putstr_fd("\n", s->parsing->fd_out);
		st = st->next;
		i++;
	}
}

#include "../../headers/minishell.h"

void init_limit(t_pip *pip)
{
	int		i;
	int		j;

	j = 0;
	pip->limit = NULL;
	while (pip)
	{
		i = 0;
		while (pip->pip_arg[i])
		{
			if (!ft_strncmp(pip->pip_arg[i], "<<", 2) && pip->pip_arg[i + 1])
			{
				pip->limit = creat_linkdlist(pip->limit, pip->pip_arg[i + 1], j);
				j++;
			}
			i++;
		}
		pip = pip->next_pip;
	}
}

// void	free_herdoc(t_limit *limit)
// {
// 	t_limit *old_limit;
// 	t_limit	*new_limit;

// 	new_limit = limit;
// 	while (new_limit)
// 	{
// 		old_limit = new_limit;
// 		new_limit = new_limit->next_limit;
// 		old_limit->next_limit = NULL;
// 		free(old_limit->limit);
// 		free(old_limit);
// 	}
// }

void	free_stack_herdoc(t_limit **limit)
{
	t_limit	*tmp;

	if (!limit || !(*limit))
		return ;
	while (*limit)
	{
		tmp = (*limit)->next_limit;
		free((*limit)->limit);
		free(*limit);
		*limit = tmp;
	}
	*limit = NULL;
}
// void	free_stack_pip(t_pip **pip)
// {
// 	t_pip	*tmp;

// 	if (!pip || !(*pip))
// 		return ;
// 	while (*pip)
// 	{
// 		tmp = (*pip)->next_pip;
// 		free_pip_arg((*tmp).pip_arg);
// 		free(*pip);
// 		*pip = tmp;
// 	}
// 	*pip = NULL;
// }

int	free_pip_arg(char **str)
{
	int	i;

	i = 0;
	if (!str || !str[i])
		return (0);
	while (str[i])
		free(str[i++]);
	return (1);
}

void	free_stack_pip(t_pip *pip)
{
	t_pip	*tmp;

	if (pip)
		return ;
	while (pip)
	{
		tmp = pip->next_pip;
		free_pip_arg(tmp->pip_arg);
		free(pip);
		pip = tmp;
	}
	pip = NULL;
}

void	free_pip(t_pip *pip)
{
	t_pip	*old_pip;
	t_pip	*new_pip;

	new_pip = pip;
	while (new_pip)
	{
		old_pip = new_pip;
		new_pip = new_pip->next_pip;
		old_pip->next_pip = NULL;
		free_pip_arg(old_pip->pip_arg);
		free(old_pip);
	}
}

#include "../../headers/minishell.h"

int	ft_check_cmd_arg(char *str)
{
	if (!ft_strncmp(str, "<<", 2) || !ft_strncmp(str, "<", 1)
		|| !ft_strncmp(str, ">", 1) || !ft_strncmp(str, "", 1))
		return (0);
	return (1);
}

int		check_infile_herd(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!ft_strncmp(str[i], "<<", 2) && str[i + 1])
			return (1);
	return (0);
}

void		refine_args(t_pip *pip, int i)
{
	free(pip->pip_arg[i]);
	free(pip->pip_arg[i + 1]);
	pip->pip_arg[i] = NULL;
	pip->pip_arg[i + 1] = NULL;
	while (pip->pip_arg[i + 2] != NULL)
	{
		pip->pip_arg[i] = pip->pip_arg[i + 2];
		i++;
	}
	pip->pip_arg[i] = NULL;
}

void	file_red_pip(t_pip *pip, int i)
{
	int	state;

	if (!ft_strncmp(pip->pip_arg[i], "<<", 2))
		state = i;
	else if (!ft_strncmp(pip->pip_arg[i], "<", 1) && pip->pip_arg[i + 1])
		pip->pip_infile = creat_file1(pip->pip_arg[i + 1], 0);
	else if (!ft_strncmp(pip->pip_arg[i], ">>", 2) && pip->pip_arg[i + 1])
		pip->pip_outfile = creat_file1(pip->pip_arg[i + 1], 2);
	else if (!ft_strncmp(pip->pip_arg[i], ">", 1) && pip->pip_arg[i + 1])
		pip->pip_outfile =  creat_file1(pip->pip_arg[i + 1], 1);
	refine_args(pip, i);
}

void	child_red_pip(char **env, t_pip  *pip)
{
	char	**l;
	int		status;
	pid_t pid;

	pid = fork();
	if (!pid)
	{
		if (pip->access)
			dup2(pip->herd_in, 0);
		else if (pip->pip_infile > 0)
			dup2(pip->pip_infile, 0);
		if (pip->pip_outfile != 1)
			dup2(pip->pip_outfile, 1);
		if (ft_patht(pip->pip_arg[0], env) && pip->pip_arg[0])
			execve(ft_patht(pip->pip_arg[0], env), pip->pip_arg, env);
		else
			write(2, "command not fond\n", 18);
	}
	close_file(pip);
	waitpid(0, NULL, 0);
}

void	redir_pip(t_pip *pip, char **env)
{
	child_red_pip(env, pip);
}

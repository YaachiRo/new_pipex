/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelfag <idelfag@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 01:59:02 by idelfag           #+#    #+#             */
/*   Updated: 2023/03/14 11:50:57 by idelfag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	error(char *str, int i)
{
	write(2, str, ft_strlen(str));
	exit(i);
}

char	**get_path(char **env)
{
	int		i;
	char	*str;
	char	**paths;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
			str = env[i] + 5;
		i++;
	}
	if (!str)
		return (0);
	paths = ft_split(str, ':');
	return (paths);
}

char	*get_command(char **paths, char *cmd)
{
	char	*temp;
	char	*command;
	int		i;

	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		command = ft_strjoin(temp, cmd);
		free(temp);
		if (!access(command, X_OK))
			return (command);
		free(command);
		i++;
	}
	return (NULL);
}

void	start(int ac, char **av, char **env, t_vars *vars)
{
	vars->env = env;
	vars->in_file = open(av[1], O_RDONLY);
	vars->out_file = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (vars->in_file == -1)
		perror("");
	if (vars->out_file == -1)
	{
		perror("");
		exit(1);
	}
	vars->paths = get_path(env);
	if (vars->paths == NULL)
		error("command not found\n", 127);
}

int	main(int ac, char **av, char **env)
{
	t_vars	vars;

	vars.index = 2;
	if (ac < 5)
		error("Arguments are not Valid\n", 1);
	start(ac ,av , env, &vars);
	while (vars.index < (ac - 2))
	{
		if (pipe(vars.fd) == -1)
			error("Pipe failed\n", 1);
		vars.pid = fork();
		if (vars.pid == -1)
			error("failed to fork child process\n", 1);
		else if (vars.pid == 0)
			child_process(&vars, av, vars.index);
		else
		{
			waitpid(vars.pid, NULL, 0);
			vars.index++;
		}
	}
	if (pipe(vars.fd) == -1)
		error("Pipe failed\n", 1);
	vars.pid = fork();
	if (vars.pid == -1)
		error("failed to fork child process\n", 1);
	else if (vars.pid == 0)
		second_child(&vars ,ac ,av);
	else
	{
		close(vars.fd[0]);
		close(vars.fd[1]);
		waitpid(vars.pid, &vars.status, 0);
		if (WIFEXITED(vars.status))
				exit(WEXITSTATUS(vars.status));
	}
}

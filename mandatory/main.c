/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelfag <idelfag@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 01:59:02 by idelfag           #+#    #+#             */
/*   Updated: 2023/04/06 10:45:38 by idelfag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		if (!access(command, F_OK))
			return (command);
		free(command);
		i++;
	}
	return (NULL);
}

void	start(char **av, char **env, t_vars *vars)
{
	vars->env = env;
	vars->in_file = open(av[1], O_RDONLY);
	vars->out_file = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (vars->in_file == -1)
		perror("");
	if (vars->out_file == -1)
	{
		perror("");
		exit(1);
	}
	vars->paths = get_path(env);
	if (!vars->paths)
		error("path is empty",1);
	if (pipe(vars->fd) == -1)
		error("Pipe failed\n", 1);
}

int	main(int ac, char **av, char **env)
{
	t_vars	vars;

	if (ac != 5)
		error("arguments are not valid\n", 1);
	start(av, env, &vars);
	vars.pid_1 = fork();
	if (vars.pid_1 == -1)
		error("Failed to fork first child\n", 1);
	if (vars.pid_1 == 0)
	{
		if (vars.in_file != -1)
			first_child(&vars, av);
	}
	else
	{
		vars.pid_2 = fork();
		if (vars.pid_2 == -1)
			error("Failed to fork second child\n", 1);
		if (vars.pid_2 == 0)
			second_child(&vars, av);
		else
		{
			close(vars.fd[0]);
			close(vars.fd[1]);
			waitpid(vars.pid_1 ,NULL, 0);
			waitpid(vars.pid_2 ,&vars.status,0);
			if (WIFEXITED(vars.status))
				exit(WEXITSTATUS(vars.status));
		}
	}
	return (0);
}

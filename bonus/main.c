/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelfag <idelfag@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 01:59:02 by idelfag           #+#    #+#             */
/*   Updated: 2023/04/10 09:55:58 by idelfag          ###   ########.fr       */
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
		if (!access(command, F_OK))
			return (command);
		free(command);
		i++;
	}
	return (NULL);
}

void	start(int ac, char **av, char **env, t_var *var)
{
	var->env = env;
	var->in_file = open(av[1], O_RDONLY);
	var->out_file = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (var->in_file == -1)
		perror("");
	if (var->out_file == -1)
	{
		perror("");
		exit(1);
	}
	var->ffd = var->in_file;
	var->paths = get_path(env);
	if (var->paths == NULL)
		error("path is empty\n", 1);
	var->index = 2;
}

int	main(int ac, char **av, char **env)
{
	t_var	var;

	if (!ft_strncmp(av[1], "here_doc", 8))
		here_doc(ac, av, env);
	if (ac < 5)
		error("Arguments are not Valid\n", 1);
	start(ac, av, env, &var);
	while (var.index <= (ac - 2))
	{
		if (pipe(var.fd) == -1)
			error("Pipe failed\n", 1);
		var.pid = fork();
		if (var.pid == -1)
			error("failed to fork child process\n", 1);
		else if (var.pid == 0)
			child_process(&var, ac, av);
		else
		{
			(waitpid(var.pid, &var.status, 0), close(var.fd[1]));
			var.ffd = var.fd[0];
			var.index++;
		}
	}
	system("leaks pipex");
	if (WIFEXITED(var.status))
		exit(WEXITSTATUS(var.status));
}

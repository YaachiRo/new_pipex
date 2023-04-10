/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelfag <idelfag@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 16:22:57 by idelfag           #+#    #+#             */
/*   Updated: 2023/04/09 16:22:57 by idelfag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	heredoc_process(int ac, char **av, t_var *var)
{
	char	*line;

	(void)ac;
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(0);
		if (!line)
		{
			perror("");
			exit(1);
		}
		if (!ft_strncmp(av[2], line, ft_strlen(av[2]))
			&& ft_strlen(av[2]) == ft_strlen(line) - 1)
			break ;
		else
		{
			write(var->in_file, line, ft_strlen(line));
			free(line);
		}
	}
	free(line);
	close(var->in_file);
}

void	init(int ac, char **av, char **env, t_var *var)
{
	var->env = env;
	var->in_file = open(".tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	var->out_file = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (var->out_file == -1 || var->in_file == -1)
	{
		unlink(".tmp");
		error("failed to open files", 1);
	}
	heredoc_process(ac, av, var);
	var->in_file = open(".tmp", O_RDONLY);
	var->paths = get_path(env);
	if (var->paths == NULL)
		error("path is empty\n", 1);
	var->ffd = var->in_file;
	var->index = 3;
}

void	here_doc(int ac, char **av, char **env)
{
	t_var	var;

	if (ac < 6)
		error("heredoc Arguments are not Valid\n", 1);
	init(ac, av, env, &var);
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
			waitpid(var.pid, &var.status, 0);
			close(var.fd[1]);
			var.ffd = var.fd[0];
			var.index++;
		}
	}
	unlink(".tmp");
	if (WIFEXITED(var.status))
		exit(WEXITSTATUS(var.status));
}

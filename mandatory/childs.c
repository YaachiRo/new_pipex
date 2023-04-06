/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelfag <idelfag@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 02:19:37 by idelfag           #+#    #+#             */
/*   Updated: 2023/04/06 10:41:21 by idelfag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child(t_vars *vars, char **av)
{
	dup2(vars->in_file, 0);
	close(vars->fd[0]);
	dup2(vars->fd[1], 1);
	vars->cmd_args = ft_split(av[2], ' ');
	if (ft_strnstr(vars->cmd_args[0], "/", ft_strlen(vars->cmd_args[0])))
	{
		if (!access(vars->cmd_args[0], X_OK))
			vars->cmd_path = vars->cmd_args[0];
		else
		{
			perror("");
			exit(1);
		}
	}
	else
		vars->cmd_path = get_command(vars->paths, vars->cmd_args[0]);
	if (!vars->cmd_path)
		error("command not found\n", 127);
	execve(vars->cmd_path, vars->cmd_args, vars->env);
}

void	second_child(t_vars *vars, char **av)
{
	dup2(vars->fd[0], 0);
	close(vars->fd[1]);
	dup2(vars->out_file, 1);
	vars->cmd_args = ft_split(av[3], ' ');
	if (ft_strnstr(vars->cmd_args[0], "/", ft_strlen(vars->cmd_args[0])))
	{
		if (!access(vars->cmd_args[0], X_OK))
			vars->cmd_path = vars->cmd_args[0];
		else
		{
			perror("");
			exit(1);
		}
	}
	else
		vars->cmd_path = get_command(vars->paths, vars->cmd_args[0]);
	if (!vars->cmd_path)
		error("command not found\n", 127);
	execve(vars->cmd_path, vars->cmd_args, vars->env);
}

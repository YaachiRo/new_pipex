/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelfag <idelfag@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 02:19:37 by idelfag           #+#    #+#             */
/*   Updated: 2023/04/04 08:22:04 by idelfag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	child_process(t_vars *vars, char **av, int index)
{
	vars->old_fd = dup(vars->in_file);
	dup2(vars->in_file, 0);
	close(vars->fd[0]);
	dup2(vars->fd[1], 1);
	vars->cmd_args = ft_split(av[index + 2], ' ');
	if (ft_strnstr(vars->cmd_args[0], "./", 2))
	{
		if (!access(vars->cmd_args[0], X_OK))
			vars->cmd_path = vars->cmd_args[0];
		else
			error("permission denied\n", 1);
	}
	else
		vars->cmd_path = get_command(vars->paths, vars->cmd_args[0]);
	if (!vars->cmd_path)
		error("command not found\n", 127);
	execve(vars->cmd_path, vars->cmd_args, vars->env);
}

void	second_child(t_vars *vars,int ac, char **av)
{
	dup2(vars->fd[0], 0);
	close(vars->fd[1]);
	dup2(vars->out_file, 1);
	vars->cmd_args = ft_split(av[ac - 2], ' ');
	if (ft_strnstr(vars->cmd_args[0], "./", 2))
	{
		if (!access(vars->cmd_args[0], X_OK))
			vars->cmd_path = vars->cmd_args[0];
		else
			error("permission denied\n", 1);
	}
	else
		vars->cmd_path = get_command(vars->paths, vars->cmd_args[0]);
	if (!vars->cmd_path)
		error("command not found\n", 127);
	execve(vars->cmd_path, vars->cmd_args, vars->env);
}

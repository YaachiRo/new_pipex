/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelfag <idelfag@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 02:19:37 by idelfag           #+#    #+#             */
/*   Updated: 2023/04/06 10:40:49 by idelfag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	child_process(t_var *var, int ac, char **av)
{
	dup2(var->old_fd, 0);
	if (var->index == ac - 2)
		dup2(var->out_file, 1);
	else
		dup2(var->fd[1], 1);
	var->cmd_args = ft_split(av[var->index], ' ');
	if (ft_strnstr(var->cmd_args[0], "./", 2))
	{
		if (!access(var->cmd_args[0], X_OK))
			var->cmd_path = var->cmd_args[0];
		else
		{
			perror("");
			exit(1);
		}
	}
	else
		var->cmd_path = get_command(var->paths, var->cmd_args[0]);
	if (!var->cmd_path)
		error("command not found\n", 1);
	execve(var->cmd_path, var->cmd_args, var->env);
}

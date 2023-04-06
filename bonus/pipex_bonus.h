/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelfag <idelfag@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 01:58:54 by idelfag           #+#    #+#             */
/*   Updated: 2023/04/06 10:47:48 by idelfag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../tools/tools.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <sys/wait.h>

typedef struct s_var
{
	int		fd[2];
	int		in_file;
	int		out_file;
	char	**cmd_args;
	char	*cmd_path;
	char	**paths;
	pid_t	pid;
	char **env;
	int status;
	int index;
	int old_fd;
}			t_var;

void		child_process(t_var *var, int ac, char **av);

#endif
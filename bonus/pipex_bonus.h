/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelfag <idelfag@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 01:58:54 by idelfag           #+#    #+#             */
/*   Updated: 2023/03/14 11:56:36 by idelfag          ###   ########.fr       */
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

typedef struct s_vars
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
}			t_vars;

void		child_process(t_vars *vars, char **av, int index);
char		*get_command(char **paths, char *cmd);
void		second_child(t_vars *vars, int ac, char **av);
void		error(char *str, int i);

#endif
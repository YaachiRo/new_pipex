/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelfag <idelfag@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 01:58:54 by idelfag           #+#    #+#             */
/*   Updated: 2023/04/09 16:02:04 by idelfag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../tools/tools.h"
# include "get_next_line/get_next_line.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_var
{
	int		fd[2];
	int		in_file;
	int		out_file;
	char	**cmd_args;
	char	*cmd_path;
	char	**paths;
	pid_t	pid;
	char	**env;
	int		status;
	int		index;
	int		ffd;
}			t_var;

void		child_process(t_var *var, int ac, char **av);
char		*get_command(char **paths, char *cmd);
char		**get_path(char **env);
void		error(char *str, int i);
void		here_doc(int ac, char **av, char **env);

#endif
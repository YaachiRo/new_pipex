/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelfag <idelfag@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 01:58:54 by idelfag           #+#    #+#             */
/*   Updated: 2023/03/14 08:46:31 by idelfag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

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
	pid_t	pid_1;
	pid_t	pid_2;
	char **env;
	int status;
}			t_vars;

char		*get_command(char **paths, char *cmd);
void		first_child(t_vars *vars, char **av);
void		second_child(t_vars *vars, char **av);
void		error(char *str, int i);

#endif
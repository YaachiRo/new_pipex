/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelfag <idelfag@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 05:14:51 by idelfag           #+#    #+#             */
/*   Updated: 2022/12/18 08:53:17 by idelfag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

char	*str_join(char *str1, char *str2);
char	*str_cpy(char *dst, char *src);
size_t	str_len(char *str);
void	*put_zero(size_t size, size_t count);
char	*str_search(char *str, char c);
char	*get_next_line(int fd);
#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelfag <idelfag@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 05:14:08 by idelfag           #+#    #+#             */
/*   Updated: 2022/12/18 08:56:51 by idelfag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdint.h>

#include "get_next_line.h"

size_t	str_len(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*str_cpy(char *dst, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*str_join(char *str1, char *str2)
{
	char	*join;
	char	*begginning;

	join = malloc(sizeof(char) * (str_len(str1) + str_len(str2) + 1));
	if (!join)
		return (NULL);
	begginning = join;
	join = str_cpy(join, str1);
	join += str_len(str1);
	join = str_cpy(join, str2);
	join += str_len(str2);
	free(str1);
	return (begginning);
}

void	*put_zero(size_t size, size_t count)
{
	char	*ptr;
	size_t	i;

	i = 0;
	if (count > 0 && size > SIZE_MAX / count)
		return (NULL);
	ptr = malloc(size * count);
	if (!ptr)
		return (NULL);
	while (i < (size * count))
	{
		ptr[i] = '\0';
		i++;
	}
	return (ptr);
}

char	*str_search(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (&str[i]);
		i++;
	}
	if (str[i] == c)
		return (&str[i]);
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelfag <idelfag@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 10:04:10 by idelfag           #+#    #+#             */
/*   Updated: 2023/03/11 03:36:09 by idelfag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	char	*start;

	if (!s1 || !s2)
		return (0);
	join = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!join)
		return (NULL);
	start = join;
	join = ft_memcpy(join, s1, ft_strlen(s1));
	join += ft_strlen(s1);
	join = ft_memcpy(join, s2, ft_strlen(s2));
	join += ft_strlen(s2);
	join[0] = '\0';
	return (start);
}

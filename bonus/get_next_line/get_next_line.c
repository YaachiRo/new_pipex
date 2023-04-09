/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelfag <idelfag@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 07:05:09 by idelfag           #+#    #+#             */
/*   Updated: 2022/12/18 07:17:34 by idelfag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*reader(char *text_holder)
{
	char	*line;
	int		i;

	i = 0;
	if (!text_holder[i])
		return (NULL);
	while (text_holder[i] && text_holder[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (text_holder[i] && text_holder[i] != '\n')
	{
		line[i] = text_holder[i];
		i++;
	}
	if (text_holder[i] == '\n')
	{
		line[i] = text_holder[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*organizer(int fd, char *text_h)
{
	char	*line;
	int		readed;

	if (!text_h)
		text_h = put_zero(1, 1);
	readed = 1;
	line = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!line)
		return (NULL);
	while (!str_search(text_h, '\n') && readed != 0)
	{
		readed = read(fd, line, BUFFER_SIZE);
		if (readed == -1)
		{
			free(line);
			free(text_h);
			return (NULL);
		}
		line[readed] = 0;
		text_h = str_join(text_h, line);
		if (!text_h)
			return (NULL);
	}
	free(line);
	return (text_h);
}

char	*update(char *text_h)
{
	char	*str;
	int		i;
	int		x;

	i = 0;
	x = 0;
	while (text_h[i] && text_h[i] != '\n')
		i++;
	if (!text_h[i])
	{
		free(text_h);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (str_len(text_h) - i + 1));
	if (!str)
		return (NULL);
	i++;
	while (text_h[i])
		str[x++] = text_h[i++];
	str[x] = '\0';
	free(text_h);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*text;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	text = organizer(fd, text);
	if (!text)
		return (NULL);
	line = reader(text);
	text = update(text);
	return (line);
}

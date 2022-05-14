/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whazami <whazami@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 20:19:40 by whazami           #+#    #+#             */
/*   Updated: 2021/06/18 22:24:26 by whazami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	fill_buffer_with_read(char *buffer, int fd, char **line)
{
	ssize_t		read_ret;

	read_ret = read(fd, buffer, BUFFER_SIZE);
	if (read_ret <= 0)
	{
		if (!*line)
		{
			*line = ft_strdup_gnl("", 1);
			if (!*line)
				return (-1);
		}
		if (read_ret == -1)
		{
			free(*line);
			*line = NULL;
		}
		return (read_ret);
	}
	buffer[read_ret] = '\0';
	return (1);
}

static int	manage_line(char **line, char *buffer)
{
	int		len_line;
	char	*tmp;

	if (ft_strlen_gnl(buffer, '\n') < ft_strlen_gnl(buffer, '\0'))
		len_line = ft_strlen_gnl(buffer, '\n') + 1;
	else
		len_line = ft_strlen_gnl(buffer, '\0');
	if (!*line)
	{
		*line = ft_strdup_gnl("", 1);
		if (!*line)
			return (-1);
	}
	tmp = ft_strdup_gnl(*line, ft_strlen_gnl(*line, '\0'));
	if (!tmp)
		return (-1);
	free(*line);
	*line = ft_strdup_gnl(tmp, ft_strlen_gnl(tmp, '\0') + len_line);
	if (!*line)
		return (-1);
	free(tmp);
	return (1);
}

static int	fill_line_with_buf(char **line, char *buf, int *line_i, int *buf_i)
{
	while (buf[*buf_i])
	{
		if (buf[*buf_i] == '\n')
		{
			(*line)[*line_i] = '\0';
			(*buf_i)++;
			return (1);
		}
		(*line)[*line_i] = buf[*buf_i];
		(*line_i)++;
		(*buf_i)++;
	}
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char	buffer[BUFFER_SIZE + 1];
	int			i;
	static int	j;
	int			ret;

	if (BUFFER_SIZE <= 0 || !line)
		return (-1);
	*line = NULL;
	i = 0;
	while (1)
	{
		if (!buffer[j])
		{
			ret = fill_buffer_with_read(buffer, fd, line);
			if (ret != 1)
				return (ret);
			j = 0;
		}
		if (manage_line(line, buffer + j) == -1)
			return (-1);
		if (fill_line_with_buf(line, buffer, &i, &j))
			return (1);
	}
}

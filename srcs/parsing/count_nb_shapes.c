/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_nb_shapes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whazami <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 06:45:58 by whazami           #+#    #+#             */
/*   Updated: 2022/04/24 17:16:18 by whazami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

static int	init_count(char *filename, int *fd, int *ret, char **line)
{
	int		i;
	t_free	free;

	free.shapes = NULL;
	free.tmp = NULL;
	i = 0;
	*fd = open(filename, 0);
	if (*fd == -1)
		error_msg("file doesn't exist", NULL, free);
	*ret = get_next_line(*fd, line);
	return (i);
}

int	brief(char **line, int *ret, char **tmp, int fd_end[2])
{
	free_tab(tmp);
	tmp = NULL;
	if (*ret == 0 && !fd_end[1])
		return (1);
	free(*line);
	*line = NULL;
	*ret = get_next_line(fd_end[0], line);
	return (0);
}

/*
** Functions to count the number of shapes in the file .rt.
*/

int	count_nb_shapes(char *filename)
{
	char	*line;
	char	**tmp;
	int		i;
	int		fd;
	int		ret;

	i = init_count(filename, &fd, &ret, &line);
	while (ret >= 0)
	{
		tmp = ft_split(line, ' ');
		if (!tmp[0])
		{
			if (brief(&line, &ret, tmp, (int [2]){fd, 0}))
				break ;
			continue ;
		}
		if (!ft_strcmp(tmp[0], "sp") || !ft_strcmp(tmp[0], "cy")
			|| !ft_strcmp(tmp[0], "pl"))
			i++;
		brief(&line, &ret, tmp, (int [2]){fd, 1});
	}
	free(line);
	close(fd);
	return (i);
}

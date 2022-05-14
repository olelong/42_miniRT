/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olelong <olelong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 19:35:02 by olelong           #+#    #+#             */
/*   Updated: 2022/04/28 17:58:54 by olelong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

/*
** Functions to check file .rt extension.
*/

int	check_file(char *filename, int argc)
{
	int		i;
	int		fd;
	t_free	free;

	free.shapes = NULL;
	free.tmp = NULL;
	free.line = NULL;
	if (argc != 2)
		error_msg("Bad number argument", NULL, free);
	i = ft_strlen(filename);
	if (ft_strcmp(&filename[i - 3], ".rt") != 0)
		error_msg("Bad extension file", NULL, free);
	fd = open(filename, 0);
	if (fd == -1)
		error_msg("File doesn't exist", NULL, free);
	return (fd);
}

/*
** Functions to check each line in file.
*/

static int	check_line(t_free f, t_scene *scene)
{
	static int	i_shapes;

	if (ft_strcmp(f.tmp[0], "A") == 0 || ft_strcmp(f.tmp[0], "L") == 0)
		add_light(f, scene);
	else if (ft_strcmp(f.tmp[0], "C") == 0 && scene->cam.fov == -1)
		add_cam(f, scene);
	else if (ft_strcmp(f.tmp[0], "sp") == 0 || ft_strcmp(f.tmp[0], "pl") == 0
		|| ft_strcmp(f.tmp[0], "cy") == 0)
		i_shapes = add_shape(f, scene, i_shapes);
	else
		error_msg("in file .rt", NULL, f);
	return (i_shapes);
}

/*
** In this function, we duplicate what is in the file in a char *,
** line by line (check_line()) with gnl and check according to the
** identifier if it is a light or other informations
** then save the data in the corresponding structs.
*/

void	parsing(int fd, t_scene *scene)
{
	int		i_shapes;
	int		ret;
	t_free	f;

	i_shapes = 0;
	ret = get_next_line(fd, &f.line);
	f.shapes = scene->shapes;
	f.tmp = NULL;
	while (ret >= 0)
	{
		f.tmp = ft_split(f.line, ' ');
		if (!f.tmp[0])
		{
			if (brief(&f.line, &ret, f.tmp, (int [2]){fd, 0}))
				break ;
			continue ;
		}
		i_shapes = check_line(f, scene);
		brief(&f.line, &ret, f.tmp, (int [2]){fd, 1});
	}
	check_end(i_shapes, scene, f);
	free(f.line);
	f.line = NULL;
	close(fd);
}

/*
** Add this line to check leaks at the end of the function
** parsing() :
** system("leaks miniRT");
*/

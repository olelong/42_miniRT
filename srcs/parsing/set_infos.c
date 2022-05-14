/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_infos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olelong <olelong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 20:09:46 by olelong           #+#    #+#             */
/*   Updated: 2022/04/28 18:03:32 by olelong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

/*
** Function to set brightness.
*/

void	set_brightness(int i, float *brightness, char *shape_name, t_free f)
{
	if (ft_strchr(f.tmp[i], ','))
		error_msg("Wrong brightness of ", shape_name, f);
	*brightness = ft_atof(f.tmp, i, f);
	if (*brightness < 0.0 || *brightness > 1.0 || ft_strchr(f.tmp[i], '-'))
		error_msg("Wrong brightness of ", shape_name, f);
}

/*
** Function to set color.
*/

void	set_color(int i, t_point *color, char *shape_name, t_free f)
{
	char	**color_tmp;

	check_comma(f.tmp[i], ',', shape_name, f);
	color_tmp = ft_split(f.tmp[i], ',');
	if (f.tmp[i][0] == ',' || f.tmp[i][ft_strlen(f.tmp[i]) - 1] == ',')
	{
		free_tab(color_tmp);
		error_msg("Incorrect syntax for color of ", shape_name, f);
	}
	if (color_tmp[0] && color_tmp[1] && color_tmp[2])
	{
		if (ft_strchr(color_tmp[0], '.') || ft_strchr(color_tmp[1], '.')
			|| ft_strchr(color_tmp[2], '.'))
		{
			free_tab(color_tmp);
			error_msg("in color ", f.tmp[i], f);
		}
	}
	if (in_range(color_tmp, (float [2]){0, 255}, "color Out of Range", f))
		add(color, color_tmp, f);
}

/*
** Function to set 3d vectors and coords.
*/

void	set_point(int i, t_point *vec_or_coord, float range[2], t_free f)
{
	char	**vec_coord;

	check_comma(f.tmp[i], ',', f.tmp[i], f);
	vec_coord = ft_split(f.tmp[i], ',');
	if (f.tmp[i][0] == ',' || f.tmp[i][ft_strlen(f.tmp[i]) - 1] == ',')
	{
		free_tab(vec_coord);
		error_msg("Incorrect syntax for vector or coords", NULL, f);
	}
	if (in_range(vec_coord, range, "Rotation or coord Out of Range", f))
		add(vec_or_coord, vec_coord, f);
}

/*
** Function to check at the end of the parsing if there
** is the right number of shapes.
*/

void	check_end(int i_shapes, t_scene *scene, t_free f)
{
	f.tmp = NULL;
	if (i_shapes != scene->nb_shapes)
		error_msg("Bad number of nb_shapes", NULL, f);
	if (scene->ambiant.brightness == -1)
		error_msg("There must be at least an ambiant light", NULL, f);
}

/*
** Function to search in a string the number of comma
** for the case where two commas follow each other.
*/

void	check_comma(char *str, char c, char *shape_name, t_free f)
{
	int	i;

	i = ft_strlen(str);
	while (i > 0)
	{
		if (str[i] == c && str[i - 1] == c && i > 1)
			error_msg("Two commas follow each other in ", shape_name, f);
		i--;
	}
}

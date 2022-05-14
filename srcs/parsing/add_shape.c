/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_shape.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olelong <olelong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 21:32:18 by olelong           #+#    #+#             */
/*   Updated: 2022/04/24 16:26:32 by whazami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

/*
** The purpose of this function is to record information from the cylinder.
*/

static void	add_cy(t_free f, t_scene *scene, int i_shapes)
{
	scene->shapes[i_shapes].type = 'c';
	set_point(1, &scene->shapes[i_shapes].coords,
		(float [2]){-FLT_MAX, FLT_MAX}, f);
	set_point(2, &scene->shapes[i_shapes].rotate, (float [2]){-1, 1}, f);
	if (ft_strchr(f.tmp[3], ',') || ft_strchr(f.tmp[4], ','))
		error_msg("Wrong cylinder diameter or height", NULL, f);
	scene->shapes[i_shapes].specs[0] = ft_atof(f.tmp, 3, f);
	scene->shapes[i_shapes].specs[1] = ft_atof(f.tmp, 4, f);
	if (scene->shapes[i_shapes].specs[0] <= 0
		|| scene->shapes[i_shapes].specs[1] <= 0)
		error_msg("Wrong cylinder diameter or height", NULL, f);
	set_color(5, &scene->shapes[i_shapes].color, "cylinder", f);
}

/*
** This function used to record information from the plan.
*/

static void	add_pl(t_free f, t_scene *scene, int i_shapes)
{
	scene->shapes[i_shapes].type = 'p';
	set_point(1, &scene->shapes[i_shapes].coords,
		(float [2]){-FLT_MAX, FLT_MAX}, f);
	set_point(2, &scene->shapes[i_shapes].rotate, (float [2]){-1, 1}, f);
	set_color(3, &scene->shapes[i_shapes].color, "plan", f);
}

/*
** The purpose of this function is to record information from the sphere.
*/

static void	add_sp(t_free f, t_scene *scene, int i_shapes)
{
	scene->shapes[i_shapes].type = 's';
	set_point(1, &scene->shapes[i_shapes].coords,
		(float [2]){-FLT_MAX, FLT_MAX}, f);
	if (ft_strchr(f.tmp[2], ','))
		error_msg("Wrong sphere diameter", NULL, f);
	scene->shapes[i_shapes].specs[0] = ft_atof(f.tmp, 2, f);
	if (scene->shapes[i_shapes].specs[0] <= 0)
		error_msg("Wrong sphere diameter", NULL, f);
	set_color(3, &scene->shapes[i_shapes].color, "sphere", f);
}

/*
** This function is used to add all shapes.
*/

int	add_shape(t_free f, t_scene *scene, int i_shapes)
{
	if (ft_strcmp(f.tmp[0], "sp") == 0 && ft_strlen(f.tmp[0]) == 2
		&& str_tab_len(f.tmp) == 4)
		add_sp(f, scene, i_shapes);
	else if (ft_strcmp(f.tmp[0], "pl") == 0 && ft_strlen(f.tmp[0]) == 2
		&& str_tab_len(f.tmp) == 4)
		add_pl(f, scene, i_shapes);
	else if (ft_strcmp(f.tmp[0], "cy") == 0 && ft_strlen(f.tmp[0]) == 2
		&& str_tab_len(f.tmp) == 6)
		add_cy(f, scene, i_shapes);
	else
		error_msg("in shape ", f.tmp[0], f);
	i_shapes++;
	return (i_shapes);
}

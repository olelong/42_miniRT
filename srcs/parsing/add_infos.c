/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_infos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olelong <olelong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 21:54:52 by olelong           #+#    #+#             */
/*   Updated: 2022/04/23 10:02:17 by olelong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

/*
** The purpose of this function is to record information from the camera.
*/

void	add_cam(t_free f, t_scene *scene)
{
	if (ft_strcmp(f.tmp[0], "C") == 0 && scene->cam.fov == -1
		&& ft_strlen(f.tmp[0]) == 1 && str_tab_len(f.tmp) == 4)
	{
		set_point(1, &scene->cam.coords, (float [2]){-FLT_MAX, FLT_MAX}, f);
		set_point(2, &scene->cam.rotate, (float [2]){-1.0, 1.0}, f);
		if (!(ft_atof(f.tmp, 3, f) >= 0 && ft_atof(f.tmp, 3, f) <= 180))
			error_msg("Camera's FOV Out of Range", NULL, f);
		if (ft_strchr(f.tmp[3], ','))
			error_msg("Wrong camera FOV", NULL, f);
		scene->cam.fov = ft_atof(f.tmp, 3, f);
	}
	else
		error_msg("Wrong infos in Cam", NULL, f);
}

/*
** This function used to record information from ambient light and light.
*/

void	add_light(t_free f, t_scene *scene)
{
	if (ft_strcmp(f.tmp[0], "L") == 0 && scene->light.brightness == -1
		&& ft_strlen(f.tmp[0]) == 1 && str_tab_len(f.tmp) == 4)
	{
		set_point(1, &scene->light.coords, (float [2]){-FLT_MAX, FLT_MAX}, f);
		set_brightness(2, &scene->light.brightness, "light", f);
		set_color(3, &scene->light.color, "light", f);
	}
	else if (ft_strcmp(f.tmp[0], "A") == 0 && scene->ambiant.brightness == -1
		&& ft_strlen(f.tmp[0]) == 1 && str_tab_len(f.tmp) == 3)
	{
		set_brightness(1, &scene->ambiant.brightness, "ambient light", f);
		if (scene->ambiant.brightness == 0)
			error_msg("Ambiant light cannot be zero", NULL, f);
		set_color(2, &scene->ambiant.color, "ambient light", f);
	}
	else
		error_msg("Wrong infos in ", *f.tmp, f);
}

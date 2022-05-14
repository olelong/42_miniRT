/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olelong <olelong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 19:59:00 by olelong           #+#    #+#             */
/*   Updated: 2022/04/14 03:19:39 by olelong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/strategy.h"

static t_ray_infos	intersect(t_scene *scene, int x, int y, t_shape *shape)
{
	const t_point	ray_origin = scene->cam.coords;
	t_point			ray_dir;

	ray_dir = (t_point){.x = x - WWIDTH / 2, .y = y - WHEIGHT / 2,
		.z = -WWIDTH / (2 * tan(scene->cam.fov * PI / 180.f / 2))};
	normalize(&ray_dir);
	rotate_vector(&ray_dir, scene->cam.rotate, 0);
	if (shape->type == 's')
		return (sp_equation(ray_origin, ray_dir, shape, scene));
	else if (shape->type == 'p')
		return (pl_equation(ray_origin, ray_dir, shape, scene));
	else if (shape->type == 'c')
		return (cy_equation(ray_origin, ray_dir, shape, scene));
	return ((t_ray_infos){.intensity = -1});
}

static t_ray_infos	get_nearest(t_scene *scene, int x, int y)
{
	t_ray_infos	nearest;
	t_ray_infos	tmp;
	int			i;

	i = 0;
	nearest.intensity = -1;
	nearest.dist_shape = FLT_MAX;
	while (i < scene->nb_shapes)
	{
		scene->id_ignore_shape = i;
		tmp = intersect(scene, x, y, &scene->shapes[i]);
		if (tmp.intensity != -1 && tmp.dist_shape < nearest.dist_shape)
		{
			nearest = tmp;
			nearest.id_shape = i;
		}
		i++;
	}
	return (nearest);
}

void	draw_nearest(t_scene *scene, int x, int y, void *img)
{
	t_ray_infos	nearest;
	t_point		c;
	t_point		tmp;

	nearest = get_nearest(scene, x, y);
	if (nearest.intensity != -1)
	{
		c.x = scene->ambiant.brightness * fmin(scene->ambiant.color.x,
				scene->shapes[nearest.id_shape].color.x);
		c.y = scene->ambiant.brightness * fmin(scene->ambiant.color.y,
				scene->shapes[nearest.id_shape].color.y);
		c.z = scene->ambiant.brightness * fmin(scene->ambiant.color.z,
				scene->shapes[nearest.id_shape].color.z);
		if (nearest.intensity != -2)
		{
			tmp.x = nearest.intensity * fmin(scene->light.color.x,
					scene->shapes[nearest.id_shape].color.x) / 255.f;
			tmp.y = nearest.intensity * fmin(scene->light.color.y,
					scene->shapes[nearest.id_shape].color.y) / 255.f;
			tmp.z = nearest.intensity * fmin(scene->light.color.z,
					scene->shapes[nearest.id_shape].color.z) / 255.f;
			c = (t_point){fmax(tmp.x, c.x), fmax(tmp.y, c.y), fmax(tmp.z, c.z)};
		}
		mlx_put_pixel_img(img, x, WHEIGHT - y - 1, c);
	}
}

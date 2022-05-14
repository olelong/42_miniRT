/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olelong <olelong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 00:41:28 by olelong           #+#    #+#             */
/*   Updated: 2022/04/06 07:00:02 by olelong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/geometry.h"

static int	is_shadow(t_point ray_origin, t_point ray_dir, t_scene *scene,
	float distance_light)
{
	t_ray_infos	r_infos;
	int			i;

	i = 0;
	while (i < scene->nb_shapes)
	{
		if (i == scene->id_ignore_shape)
		{
			i++;
			continue ;
		}
		if (scene->shapes[i].type == 's')
			r_infos = sp_equation(ray_origin, ray_dir, &scene->shapes[i], NULL);
		else if (scene->shapes[i].type == 'p')
			r_infos = pl_equation(ray_origin, ray_dir, &scene->shapes[i], NULL);
		else if (scene->shapes[i].type == 'c')
			r_infos = cy_equation(ray_origin, ray_dir, &scene->shapes[i], NULL);
		if (r_infos.dist_shape > 0 && r_infos.dist_shape < distance_light
			&& r_infos.intensity >= 0)
			return (1);
		i++;
	}
	return (0);
}

static t_point	get_normal(t_shape *shape, t_point x1_3d)
{
	t_point	origin_x1_3d;
	t_point	proj;
	t_point	normal_a;

	if (shape->type == 's')
		return (minus(x1_3d, shape->coords));
	else if (shape->type == 'p')
		return (shape->normal);
	else if (shape->type == 'c')
	{
		origin_x1_3d = minus(x1_3d, shape->coords);
		proj = mult(dot(origin_x1_3d, shape->normal)
				/ pow(norm(shape->normal), 2), shape->normal);
		normal_a = plus(shape->coords, proj);
		return (minus(x1_3d, normal_a));
	}
	return ((t_point){});
}

t_ray_infos	get_intensity(float x1, t_point ray_dir,
	t_shape *shape, t_scene *scene)
{
	t_point		x1_3d;
	t_point		normal;
	t_point		light;
	float		distance;
	t_ray_infos	res;

	if (x1 < 0)
		return ((t_ray_infos){.intensity = -1});
	ray_dir.x *= x1;
	ray_dir.y *= x1;
	ray_dir.z *= x1;
	x1_3d = plus(scene->cam.coords, ray_dir);
	normal = get_normal(shape, x1_3d);
	normalize(&normal);
	light = minus(scene->light.coords, x1_3d);
	distance = norm(light);
	normalize(&light);
	res.intensity = 0.5f / PI * scene->light.brightness
		* fmaxf(0, dot(normal, light)) / pow(distance, 2);
	res.intensity = fminf(255.f, fmaxf(0.f, res.intensity));
	if (is_shadow(x1_3d, light, scene, distance))
		res.intensity = -2;
	res.dist_shape = x1;
	return (res);
}

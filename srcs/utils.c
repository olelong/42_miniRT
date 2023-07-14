/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olelong <olelong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 09:04:43 by olelong           #+#    #+#             */
/*   Updated: 2022/04/24 17:19:25 by whazami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

int	free_all(t_scene *scene)
{
	mlx_destroy_image(scene->mlx, scene->img);
	mlx_destroy_window(scene->mlx, scene->win);
	//mlx_destroy_display(scene->mlx);
	free(scene->mlx);
	free(scene->shapes);
	exit(0);
}

int	key_hook(int keycode, t_scene *scene)
{
	if (keycode == ESC)
		free_all(scene);
	return (0);
}

void	mlx_put_pixel_img(void *img, int x, int y, t_point color)
{
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	char	*dst;

	addr = mlx_get_data_addr(img, &bits_per_pixel, &line_length, &endian);
	dst = addr + (y * line_length + x * (bits_per_pixel / 8));
	*(unsigned int *)dst = (int)color.x * pow(16, 4) + (int)color.y * pow(16, 2)
		+ (int)color.z;
}

t_ray_infos	cut_pl_for_cy(t_ray_infos r[2], t_point x1_3d[2], t_shape e[2],
	t_shape *cy)
{
	if (r[0].dist_shape < r[1].dist_shape && r[0].dist_shape >= 0
		&& norm(minus(x1_3d[0], e[0].coords)) <= cy->specs[0] / 2.f)
		return (r[0]);
	else if (r[1].dist_shape >= 0
		&& norm(minus(x1_3d[1], e[1].coords)) <= cy->specs[0] / 2.f)
		return (r[1]);
	return ((t_ray_infos){.intensity = -1});
}

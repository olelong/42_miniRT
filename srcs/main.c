/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olelong <olelong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:33:59 by whazami           #+#    #+#             */
/*   Updated: 2022/04/24 16:42:40 by whazami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"
#include "../includes/strategy.h"
#include "../includes/parsing.h"

/*
** This function initiates the elements of the scene structure.
*/

static void	init(t_scene *scene, char *filename)
{
	scene->ambiant.brightness = -1;
	scene->cam.fov = -1;
	scene->light.brightness = -1;
	scene->nb_shapes = count_nb_shapes(filename);
	scene->shapes = (t_shape *)ft_calloc(scene->nb_shapes, sizeof(t_shape));
}

static void	init_scene(t_scene *scene)
{
	scene->light.brightness *= 1000000;
	scene->ambiant.brightness /= 3.f;
	scene->mlx = mlx_init();
	scene->win = mlx_new_window(scene->mlx, WWIDTH, WHEIGHT, "miniRT!");
	scene->img = mlx_new_image(scene->mlx, WWIDTH, WHEIGHT);
}

/*
** fill image 
*/

static void	update(t_scene *scene)
{
	int	x;
	int	y;

	x = 0;
	while (x < WWIDTH)
	{
		y = 0;
		while (y < WHEIGHT)
		{
			draw_nearest(scene, x, y, scene->img);
			y++;
		}
		x++;
	}
}

int	main(int argc, char **argv)
{
	t_scene	scene;
	int		fd;

	scene.shapes = NULL;
	fd = check_file(argv[1], argc);
	init(&scene, argv[1]);
	parsing(fd, &scene);
	init_scene(&scene);
	update(&scene);
	mlx_put_image_to_window(scene.mlx, scene.win, scene.img, 0, 0);
	mlx_key_hook(scene.win, key_hook, &scene);
	mlx_hook(scene.win, 17, 0L, free_all, &scene);
	mlx_loop(scene.mlx);
	return (0);
}

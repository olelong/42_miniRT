/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olelong <olelong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 09:01:51 by olelong           #+#    #+#             */
/*   Updated: 2022/04/24 17:10:53 by whazami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../lib/mlx/mlx.h"
# include "geometry.h"
# include <math.h>

int			free_all(t_scene *scene);
int			key_hook(int keycode, t_scene *scene);
void		mlx_put_pixel_img(void *img, int x, int y, t_point color);

#endif // UTILS_H

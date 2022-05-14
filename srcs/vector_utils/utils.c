/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olelong <olelong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 22:39:14 by olelong           #+#    #+#             */
/*   Updated: 2022/04/06 06:49:03 by olelong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/geometry.h"

float	norm(t_point v)
{
	return (sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)));
}

void	normalize(t_point *v)
{
	float	norme;

	norme = norm(*v);
	v->x /= norme;
	v->y /= norme;
	v->z /= norme;
}

void	rotate_vector(t_point *vector, t_point rotate, int init)
{
	t_matrix	rox;
	t_matrix	roy;
	t_matrix	roz;
	float		angles[3];

	if (init)
		*vector = (t_point){.x = 0, .y = 1, .z = 0};
	angles[0] = rotate.x * PI;
	angles[1] = rotate.y * PI;
	angles[2] = rotate.z * PI;
	rox = (t_matrix){(t_point){1, 0, 0}, (t_point){0, cos(angles[0]),
		sin(angles[0])}, (t_point){0, -sin(angles[0]), cos(angles[0])}};
	roy = (t_matrix){(t_point){cos(angles[1]), 0, -sin(angles[1])},
		(t_point){0, 1, 0}, (t_point){sin(angles[1]), 0, cos(angles[1])}};
	roz = (t_matrix){(t_point){cos(angles[2]), sin(angles[2]), 0},
		(t_point){-sin(angles[2]), cos(angles[2]), 0}, (t_point){0, 0, 1}};
	*vector = dot_matrix(*vector, rox);
	*vector = dot_matrix(*vector, roy);
	*vector = dot_matrix(*vector, roz);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equation_shapes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olelong <olelong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 22:22:55 by olelong           #+#    #+#             */
/*   Updated: 2022/04/24 17:19:45 by whazami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/geometry.h"

t_ray_infos	cut_pl_for_cy(t_ray_infos r[2], t_point x1_3d[2], t_shape e[2],
				t_shape *cy);

t_ray_infos	sp_equation(t_point ray_origin, t_point ray_dir,
	t_shape *sphere, t_scene *scene)
{
	t_ray_infos	res;
	t_point		diff_vect;
	t_point		coeffs;
	float		delta;
	t_point		solutions;

	res.intensity = -1;
	diff_vect = minus(ray_origin, sphere->coords);
	coeffs.x = 1;
	coeffs.y = 2 * dot(ray_dir, diff_vect);
	coeffs.z = pow(norm(diff_vect), 2) - pow(sphere->specs[0] / 2.f, 2);
	delta = pow(coeffs.y, 2) - 4 * coeffs.x * coeffs.z;
	if (delta < 0)
		return (res);
	solutions.y = (-coeffs.y + sqrt(delta)) / (2 * coeffs.x);
	if (solutions.y > 0)
	{
		solutions.x = (-coeffs.y - sqrt(delta)) / (2 * coeffs.x);
		if (scene)
			return (get_intensity(solutions.x, ray_dir, sphere, scene));
		else
			return ((t_ray_infos){.dist_shape = solutions.x});
	}
	return (res);
}

t_ray_infos	pl_equation(t_point ray_origin, t_point ray_dir,
	t_shape *plan, t_scene *scene)
{
	float	solution;
	float	denom;

	rotate_vector(&plan->normal, plan->rotate, 1);
	if (plan->normal.z < 0 || (plan->normal.z == 0
			&& ((plan->coords.x < ray_origin.x && plan->normal.x < 0)
				|| (plan->coords.x > ray_origin.x && plan->normal.x > 0)
				|| (plan->coords.y < ray_origin.y && plan->normal.y < 0)
				|| (plan->coords.y > ray_origin.y && plan->normal.y > 0))))
	{
		plan->normal.x *= -1;
		plan->normal.y *= -1;
		plan->normal.z *= -1;
	}
	solution = -1;
	denom = dot(plan->normal, ray_dir);
	if (denom != 0)
		solution = dot(minus(plan->coords, ray_origin), plan->normal) / denom;
	if (scene)
		return (get_intensity(solution, ray_dir, plan, scene));
	else
		return ((t_ray_infos){.dist_shape = solution});
}

void	fill_cy_coeffs(t_point *coeffs, t_shape *cylindre, t_point ray_origin,
	t_point ray_dir)
{
	t_point		ab;
	t_point		ao;
	t_matrix	ca;
	t_point		ao_x_ab;
	t_point		v_x_ab;

	ab = minus(plus(cylindre->coords, cylindre->normal), cylindre->coords);
	ao = minus(ray_origin, cylindre->coords);
	ca = (t_matrix){(t_point){0, ab.z, -ab.y}, (t_point){-ab.z, 0, ab.x},
		(t_point){ab.y, -ab.x, 0}};
	ao_x_ab = dot_matrix(ao, ca);
	v_x_ab = dot_matrix(ray_dir, ca);
	coeffs->x = dot(v_x_ab, v_x_ab);
	coeffs->y = 2 * dot(v_x_ab, ao_x_ab);
	coeffs->z = dot(ao_x_ab, ao_x_ab) - (pow(cylindre->specs[0] / 2.f, 2)
			* dot(ab, ab));
}

/* ray[0] -> ray_origin, ray[1] -> ray_dir
 * r -> rays_infos
 * e -> edges
 * Cette fonction rajoute les bords ronds au cylindre
 * Ces bords sont des plans coupes en cercle
 * Tout d'abord on coupe le cylindre (parce qu'il est infini par defaut)
 * Ensuite, on cree les deux edges, puis on verifie si x1_3d est dans
 * l'un des deux, si oui on renvoie les ray_infos
 */

t_ray_infos	manage_edges(t_shape *cy, t_point x1_3d_cy, t_point ray[2],
	t_scene *scene)
{
	t_shape		e[2];
	t_ray_infos	r[2];
	t_point		x1_3d[2];
	int			i;

	if (norm(minus(x1_3d_cy, plus(cy->coords, mult(cy->specs[1]
						/ 2.f, cy->normal)))) > sqrt(pow(cy->specs[1] / 2.f, 2)
			+ pow(cy->specs[0] / 2.f, 2)))
	{
		i = -1;
		while (++i < 2)
		{
			e[i].coords = plus(cy->coords, mult(!i * cy->specs[1], cy->normal));
			e[i].rotate = cy->rotate;
			e[i].type = 'p';
			r[i] = pl_equation(ray[0], ray[1], &e[i], scene);
			x1_3d[i] = plus(ray[0], mult(r[i].dist_shape, ray[1]));
		}
		return (cut_pl_for_cy(r, x1_3d, e, cy));
	}
	return ((t_ray_infos){.intensity = -3});
}

t_ray_infos	cy_equation(t_point ray_origin, t_point ray_dir,
	t_shape *cylinder, t_scene *scene)
{
	t_ray_infos	res;
	t_point		coeffs;
	float		delta;
	t_point		solutions;
	t_point		x1_3d;

	rotate_vector(&cylinder->normal, cylinder->rotate, 1);
	fill_cy_coeffs(&coeffs, cylinder, ray_origin, ray_dir);
	delta = pow(coeffs.y, 2) - 4 * coeffs.x * coeffs.z;
	if (delta < 0)
		return ((t_ray_infos){.intensity = -1});
	solutions.y = (-coeffs.y + sqrt(delta)) / (2 * coeffs.x);
	if (solutions.y > 0)
	{
		solutions.x = (-coeffs.y - sqrt(delta)) / (2 * coeffs.x);
		x1_3d = plus(ray_origin, mult(solutions.x, ray_dir));
		res = manage_edges(cylinder, x1_3d, (t_point[2]){ray_origin, ray_dir},
				scene);
		if (res.intensity != -3)
			return (res);
		if (scene)
			return (get_intensity(solutions.x, ray_dir, cylinder, scene));
		return ((t_ray_infos){.dist_shape = solutions.x});
	}
	return ((t_ray_infos){.intensity = -1});
}

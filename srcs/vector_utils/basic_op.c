/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olelong <olelong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 22:26:09 by olelong           #+#    #+#             */
/*   Updated: 2022/04/06 02:50:26 by olelong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/geometry.h"

t_point	minus(t_point v1, t_point v2)
{
	t_point	res;

	res.x = v1.x - v2.x;
	res.y = v1.y - v2.y;
	res.z = v1.z - v2.z;
	return (res);
}

t_point	plus(t_point v1, t_point v2)
{
	t_point	res;

	res.x = v1.x + v2.x;
	res.y = v1.y + v2.y;
	res.z = v1.z + v2.z;
	return (res);
}

t_point	mult(float f, t_point v)
{
	v.x *= f;
	v.y *= f;
	v.z *= f;
	return (v);
}

float	dot(t_point v1, t_point v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_point	dot_matrix(t_point v, t_matrix m)
{
	t_point	ret;

	ret.x = v.x * m.x.x + v.y * m.y.x + v.z * m.z.x;
	ret.y = v.x * m.x.y + v.y * m.y.y + v.z * m.z.y;
	ret.z = v.x * m.x.z + v.y * m.y.z + v.z * m.z.z;
	return (ret);
}

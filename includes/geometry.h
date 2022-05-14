/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olelong <olelong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 00:04:13 by whazami           #+#    #+#             */
/*   Updated: 2022/04/24 16:25:52 by whazami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEOMETRY_H
# define GEOMETRY_H

# include "../lib/libft/libft.h"
# include "../lib/mlx/mlx.h"
# include <math.h>
# include <float.h>

# define WWIDTH  1200
# define WHEIGHT 675

//# define ESC 53 //Mac
# define ESC 65307

# define PI 3.1415926535897932f

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
}	t_point;

typedef struct s_matrix
{
	t_point	x;
	t_point	y;
	t_point	z;
}	t_matrix;

typedef struct s_ray_infos
{
	float	intensity;
	float	dist_shape;
	int		id_shape;
}	t_ray_infos;

typedef struct s_ambiant
{
	float	brightness;
	t_point	color;
}	t_ambiant;

typedef struct s_cam
{
	t_point	coords;
	t_point	rotate;
	int		fov;
}	t_cam;

typedef struct s_light
{
	t_point	coords;
	float	brightness;
	t_point	color;
}	t_light;

/* specs est le diametre et la hauteur pour le cylindre
 * et diametre pour la sphere */
typedef struct s_shape
{
	char	type;
	t_point	coords;
	t_point	rotate;
	float	specs[2];
	t_point	color;
	t_point	normal;
}	t_shape;

typedef struct s_scene
{
	t_ambiant	ambiant;
	t_cam		cam;
	t_light		light;
	t_shape		*shapes;
	int			nb_shapes;
	void		*mlx;
	void		*win;
	void		*img;
	int			id_ignore_shape;
}	t_scene;

// vector_utils/basic_op.c
t_point		minus(t_point v1, t_point v2);
t_point		plus(t_point v1, t_point v2);
t_point		mult(float f, t_point v);
float		dot(t_point v1, t_point v2);
t_point		dot_matrix(t_point v, t_matrix m);

// vector_utils/utils.c
float		norm(t_point v);
void		normalize(t_point *v);
void		rotate_vector(t_point *vector, t_point rotate, int init);

// equation_shapes.c
t_ray_infos	sp_equation(t_point ray_origin, t_point ray_dir,
				t_shape *sphere, t_scene *scene);
t_ray_infos	pl_equation(t_point ray_origin, t_point ray_dir,
				t_shape *plan, t_scene *scene);
t_ray_infos	cy_equation(t_point ray_origin, t_point ray_dir,
				t_shape *cylindre, t_scene *scene);

// geometry.c
t_ray_infos	get_intensity(float x1, t_point ray_dir,
				t_shape *shape, t_scene *scene);

#endif // GEOMETRY_H

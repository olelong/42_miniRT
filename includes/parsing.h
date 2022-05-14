/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olelong <olelong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 19:52:17 by olelong           #+#    #+#             */
/*   Updated: 2022/04/24 17:15:36 by whazami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "geometry.h"
# include "../lib/libft/libft.h"
# include <math.h>
# include <stdio.h>
# include <float.h>

typedef struct s_free
{
	t_shape	*shapes;
	char	*line;
	char	**tmp;
}	t_free;

/*
** ft_atof.c
*/
double	ft_atof(char **tmp, int i, t_free f);

/*
** parsing_utils.c
*/
void	free_tab(char **tab);
void	error_msg(char *s1, char *s2, t_free f);
int		str_tab_len(char **strs);
int		in_range(char **tmp, float range[2], char *message, t_free f);
void	add(t_point *point, char **tmp, t_free f);

/*
** set_infos.c
*/
void	set_brightness(int i, float *brightness, char *shape_name, t_free f);
void	set_color(int i, t_point *color, char *shape_name, t_free f);
void	set_point(int i, t_point *vec_or_coord, float range[2], t_free f);
void	check_end(int i_shapes, t_scene *scene, t_free f);
void	check_comma(char *str, char c, char *shape_name, t_free f);

/*
** add_shape.c
*/
int		add_shape(t_free f, t_scene *scene, int i_shapes);

/*
** add.c
*/
void	add_cam(t_free f, t_scene *scene);
void	add_light(t_free f, t_scene *scene);

/*
** count_nb_shape.c
*/

int		brief(char **line, int *ret, char **tmp, int fd_end[2]);
int		count_nb_shapes(char *filename);

/*
** parsing.c
*/
int		check_file(char *filename, int argc);
void	parsing(int fd, t_scene *scene);

#endif

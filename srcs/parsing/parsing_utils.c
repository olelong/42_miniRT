/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olelong <olelong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 17:37:11 by olelong           #+#    #+#             */
/*   Updated: 2022/04/23 10:06:25 by olelong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

/*
** Useful functions to free a tab.
*/

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
			free(tab[i++]);
		free(tab);
		tab = NULL;
	}
}

/*
** Useful functions to put an error message and quit the program.
*/

void	error_msg(char *s1, char *s2, t_free f)
{
	write(2, "Error\n", 6);
	if (s1)
		write(2, s1, ft_strlen(s1));
	if (s2)
		write(2, s2, ft_strlen(s2));
	write(2, "\n", 1);
	if (f.shapes)
		free(f.shapes);
	if (f.tmp)
		free_tab(f.tmp);
	if (f.line)
		free(f.line);
	exit(2);
}

/*
** Useful functions to return the size of a tab.
*/

int	str_tab_len(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		i++;
	return (i);
}

/*
** Functions to check if un number is in range or not.
*/

int	in_range(char **tmp, float range[2], char *message, t_free f)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		if (ft_atof(tmp, i, f) >= range[0] && ft_atof(tmp, i, f) <= range[1])
			i++;
		else
		{
			free_tab(tmp);
			error_msg(message, NULL, f);
			return (-1);
		}
	}
	return (1);
}

/*
** Useful functions to add color/vector/coords in struct.
*/

void	add(t_point *point, char **tmp, t_free f)
{
	if (str_tab_len(tmp) != 3)
	{
		if (tmp)
			free_tab(tmp);
		error_msg("Bad number of argument", NULL, f);
	}
	point->x = ft_atof(tmp, 0, f);
	point->y = ft_atof(tmp, 1, f);
	point->z = ft_atof(tmp, 2, f);
	if (tmp)
		free_tab(tmp);
}

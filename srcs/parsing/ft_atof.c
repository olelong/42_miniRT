/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olelong <olelong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 19:52:06 by olelong           #+#    #+#             */
/*   Updated: 2022/04/28 17:27:54 by olelong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

/*
** Function ft_atof to convert a string into float.
*/

static int	is_double(char *str)
{
	int	i;
	int	point;

	i = 0;
	point = 0;
	if (str[0] == '.')
		return (0);
	if (ft_strlen(str) > 1 && str[0] == '-' && !ft_isdigit(str[1]))
		return (0);
	while (str[i])
	{
		if (str[i] == '.')
			point++;
		if ((str[i] != '.' && !ft_isdigit(str[i]) && str[i] != '-'))
			return (0);
		i++;
		if (str[i] == '-')
			return (0);
	}
	if (point != 1 || str[i - 1] == '.')
		return (0);
	return (1);
}

static int	is_nb(char *str)
{
	int	i;

	i = 0;
	if (ft_strlen(str) == 1 && str[0] == '-')
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '-')
			return (0);
		i++;
		if (str[i] == '-')
			return (0);
	}
	return (1);
}

double	ft_atof(char **tmp, int i, t_free f)
{
	int		entier;
	int		decimal;
	double	res;

	res = 0.0;
	if (is_double(tmp[i]))
	{
		f.tmp = ft_split(tmp[i], '.');
		entier = ft_atoi(f.tmp[0]);
		decimal = ft_atoi(f.tmp[1]);
		if (entier < 0)
			res = entier - decimal / pow(10, (double)ft_strlen(f.tmp[1]));
		else
			res = entier + decimal / pow(10, (double)ft_strlen(f.tmp[1]));
		if (entier == 0 && tmp[i][0] == '-')
			res = -res;
		free_tab(f.tmp);
	}
	else if (is_nb(tmp[i]))
		res = ft_atoi(tmp[i]);
	else
	{
		if (tmp != f.tmp)
			free_tab(tmp);
		error_msg("Invalid number", NULL, f);
	}
	return (res);
}

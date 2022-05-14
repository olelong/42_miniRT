/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whazami <whazami@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 20:25:59 by whazami           #+#    #+#             */
/*   Updated: 2021/06/08 20:26:23 by whazami          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup_gnl(const char *s, size_t size)
{
	char	*strr;
	size_t	i;

	strr = (char *)malloc(size + 1);
	if (strr == NULL)
		return (NULL);
	i = 0;
	while (s[i] && i <= size)
	{
		strr[i] = s[i];
		i++;
	}
	while (i <= size)
	{
		strr[i] = '\0';
		i++;
	}
	return (strr);
}

size_t	ft_strlen_gnl(const char *s, char c)
{
	int	cpt;

	cpt = 0;
	while (s[cpt] != c && s[cpt])
		cpt++;
	return (cpt);
}

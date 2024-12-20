/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whazami <whazami@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 16:16:27 by whazami           #+#    #+#             */
/*   Updated: 2022/03/15 18:28:39 by olelong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_freeall(char **s)
{
	unsigned int	i;

	i = 0;
	while (s[i] != NULL)
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (NULL);
}

static	size_t	ft_wordcount(const char *s, char d)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != d)
		{
			count ++;
			while (s[i] && s[i] != d)
				i++;
		}
		else
			i++;
	}
	return (count);
}

static char	*ft_worddup(const char *s, char d)
{
	size_t	len;
	char	*ptr;

	len = 0;
	while (s[len] && s[len] != d)
		len++;
	ptr = ft_calloc(len + 1, sizeof(char));
	if (!ptr)
		return (NULL);
	ft_strlcpy (ptr, s, len + 1);
	return (ptr);
}

static char	**ft_inside_split(const char *s, char d, size_t len)
{
	char	**ptr;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	ptr = (char **)ft_calloc (len + 1, sizeof (char *));
	if (!ptr)
		return (NULL);
	while (i < len && s[j])
	{
		if (s[j] != d)
		{
			ptr[i] = ft_worddup(&s[j], d);
			if (!ptr[i++])
				return (ft_freeall(ptr));
			while (s[j] && s[j] != d)
				j++;
		}
		else
			j++;
	}
	return (ptr);
}

char	**ft_split(const char *s, char d)
{
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_wordcount(s, d);
	return (ft_inside_split(s, d, len));
}

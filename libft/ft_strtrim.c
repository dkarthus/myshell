/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarthus <dkarthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 17:29:15 by dkarthus          #+#    #+#             */
/*   Updated: 2020/12/02 20:03:43 by dkarthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	j;

	if (s1 == NULL || set == NULL)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	if (!(*s1))
		return (ft_strdup(s1));
	j = ft_strlen(s1);
	while (ft_strchr(set, s1[j - 1]))
		j--;
	return (ft_substr(s1, 0, j));
}

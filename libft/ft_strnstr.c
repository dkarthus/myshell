/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarthus <dkarthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 13:41:14 by dkarthus          #+#    #+#             */
/*   Updated: 2020/12/02 20:03:43 by dkarthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_probe(const char *big, const char *small)
{
	while (*big++ == *small++)
	{
		if (!(*small))
			return (1);
	}
	return (0);
}

char	*ft_strnstr(const char *hstck, const char *ndl, size_t len)
{
	size_t		j;

	if (ft_strlen(hstck) < ft_strlen(ndl))
		return (NULL);
	if (!(*ndl))
		return ((char *)hstck);
	j = 0;
	while ((j + ft_strlen(ndl) <= len) && hstck[j])
	{
		if (ft_probe((hstck + j), ndl))
			return ((char *)hstck + j);
		j++;
	}
	return (NULL);
}

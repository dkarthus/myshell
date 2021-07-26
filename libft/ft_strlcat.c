/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarthus <dkarthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 12:03:33 by dkarthus          #+#    #+#             */
/*   Updated: 2020/12/02 20:03:43 by dkarthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	j;
	size_t	i;
	size_t	dstlen;

	j = 0;
	dstlen = ft_strlen(dst);
	i = dstlen;
	if (!(*src))
		return (i);
	if (size < dstlen + 1)
		return (size + ft_strlen(src));
	if (size > dstlen + 1)
	{
		while (i < size - 1)
		{
			dst[i++] = src[j++];
			if (src[j] == '\0')
			{
				dst[i] = '\0';
				return (i);
			}
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src) + dstlen);
}

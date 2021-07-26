/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarthus <dkarthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 12:56:23 by dkarthus          #+#    #+#             */
/*   Updated: 2021/01/08 19:01:34 by dkarthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*ptr;
	const unsigned char	*ptr2;

	ptr = dst;
	ptr2 = src;
	if (len == 0 || dst == src)
		return (dst);
	if ((unsigned char *)src > (unsigned char *)dst)
		return (ft_memcpy(dst, src, len));
	if ((unsigned char *)src < (unsigned char *)dst)
	{
		while (len-- != 0)
			ptr[len] = ptr2[len];
	}
	return (dst);
}

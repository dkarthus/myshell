/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarthus <dkarthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 12:06:03 by dkarthus          #+#    #+#             */
/*   Updated: 2020/12/02 20:03:43 by dkarthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		uc;
	unsigned char		*ptr;
	const unsigned char	*ptr2;

	uc = c;
	ptr = dst;
	ptr2 = src;
	if (dst == src)
		return (dst);
	while (n != 0)
	{
		*ptr++ = *ptr2++;
		if (*ptr == uc)
			return (ptr);
		n--;
	}
	return (NULL);
}

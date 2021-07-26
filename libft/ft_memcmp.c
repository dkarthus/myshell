/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarthus <dkarthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 14:31:25 by dkarthus          #+#    #+#             */
/*   Updated: 2020/12/02 20:03:43 by dkarthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*ds1;
	const unsigned char	*ds2;

	ds1 = s1;
	ds2 = s2;
	while (n-- != 0)
	{
		if (*ds1 > *ds2)
			return ((int)(*ds1 - *ds2));
		if (*ds1 < *ds2)
			return (-(int)(*ds2 - *ds1));
		ds1++;
		ds2++;
	}
	return (0);
}

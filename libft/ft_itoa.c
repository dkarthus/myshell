/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarthus <dkarthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 21:09:58 by dkarthus          #+#    #+#             */
/*   Updated: 2020/12/02 20:03:43 by dkarthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	ft_norm(int n, int *sign)
{
	*sign = 1;
	if (n < 0)
	{
		*sign = -1;
		return (-(long)n);
	}
	return ((long)n);
}

char	*ft_itoa(int n)
{
	long	tmp;
	char	buf[12];
	int		k;
	int		sign;

	k = 10;
	sign = 1;
	ft_bzero(buf, 12);
	tmp = ft_norm(n, &sign);
	while (k >= 0)
	{
		if (tmp < 10)
		{
			buf[k] = tmp + '0';
			break ;
		}
		buf[k--] = tmp % 10 + '0';
		tmp = tmp / 10;
	}
	if (sign < 0)
		buf[--k] = '-';
	return (ft_strdup(buf + k));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarthus <dkarthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 15:08:26 by dkarthus          #+#    #+#             */
/*   Updated: 2020/12/02 20:03:43 by dkarthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_num_lng(long long i, int base)
{
	int	len;

	len = 0;
	if (i < 0)
		len++;
	while (i)
	{
		i = i / (long long)base;
		len++;
	}
	if (len == 0)
		return (1);
	else
		return (len);
}

char	*ft_itoa_base(long long num, int base)
{
	const char			*ref = "0123456789abcdef";
	char				*dst;
	int					len;
	unsigned long long	tmp;

	tmp = num;
	len = ft_num_lng(num, base);
	dst = ft_calloc((len + 1), 1);
	if (!dst)
		return (NULL);
	if (num == 0)
		return (ft_strdup("0"));
	len--;
	while (len >= 0)
	{
		dst[len] = ref[tmp % (long long)base];
		tmp = tmp / (long long)base;
		len--;
	}
	return (dst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarthus <dkarthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 18:18:34 by dkarthus          #+#    #+#             */
/*   Updated: 2020/12/02 20:03:42 by dkarthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\n' || c == '\t' || c == '\v' || c == '\f' || c
		== '\r');
}

long	ft_atoi(const char *str)
{
	long	sign;
	long	value;

	sign = 1;
	value = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		if (*(str + 1) == '-' || *(str + 1) == '+')
			return ((int)sign * 0);
		str++;
	}
	while (ft_isdigit(*str))
	{
		value = (long)(value * 10 + (*str - '0'));
		str++;
	}
	return (value * sign);
}

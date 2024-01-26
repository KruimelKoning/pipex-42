/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbartels <lbartels@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/04 17:46:47 by lbartels      #+#    #+#                 */
/*   Updated: 2023/10/26 19:55:21 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(char const *nptr)
{
	int	len;

	len = 0;
	while (*nptr == '0')
		nptr++;
	while (nptr[len] >= '0' && nptr[len] <= '9')
	{
		len++;
	}
	return (len);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	num;
	int	min;

	i = 0;
	num = 0;
	min = 0;
	while ((nptr[i] == 32) || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			min = 1;
		i++;
	}
	if (ft_len(nptr + i) >= 20)
		return (-1);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		num = num * 10 + (nptr[i] - 48);
		i++;
	}
	if (min == 1)
		num = -num;
	return (num);
}

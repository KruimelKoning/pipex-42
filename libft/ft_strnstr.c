/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbartels <lbartels@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 17:11:41 by lbartels      #+#    #+#                 */
/*   Updated: 2023/10/26 19:52:40 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	if (little[0] == '\0')
		return ((char *)big);
	while (*big != '\0' && len > 0)
	{
		i = 0;
		while (big[i] == little[i] && big[i] != '\0'
			&& little[i] != '\0' && len > 0)
		{
			i++;
			len--;
		}
		if (little[i] == '\0')
			return ((char *)big);
		else
			len = len + i;
		big++;
		len--;
	}
	return (0);
}

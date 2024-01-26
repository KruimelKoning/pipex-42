/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbartels <lbartels@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 15:59:21 by lbartels      #+#    #+#                 */
/*   Updated: 2023/10/26 19:52:16 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (((unsigned char *)s)[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (((unsigned char *)s)[i] == (char)c)
		return ((char *)&s[i]);
	return (0);
}

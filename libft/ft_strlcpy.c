/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbartels <lbartels@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 17:48:44 by lbartels      #+#    #+#                 */
/*   Updated: 2023/10/26 19:53:16 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (src[i] == '\0' && size == 0)
		return (i);
	while (src[i] != '\0' && size > (i + 1))
	{
		dest[i] = src[i];
		i++;
	}
	if (src[i] == '\0' || size != 0)
		dest[i] = '\0';
	while (src[i] != '\0')
		i++;
	return (i);
}

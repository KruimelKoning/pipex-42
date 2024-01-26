/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbartels <lbartels@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/13 16:55:11 by lbartels      #+#    #+#                 */
/*   Updated: 2023/12/14 15:45:59 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

int	check_new_line(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*gnl_strjoin(char *str, char const *buffer)
{
	char	*new_str;
	size_t	i;
	size_t	j;

	if (!str)
	{
		str = (char *)malloc(1 * sizeof(char));
		str[0] = '\0';
	}
	new_str = (char *)malloc(sizeof(char)
			* (ft_strlen(str) + ft_strlen(buffer) + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
		new_str[j++] = str[i++];
	i = 0;
	while (buffer[i])
		new_str[j++] = buffer[i++];
	new_str[j] = '\0';
	free(str);
	return (new_str);
}

char	*set_next_line(char *str)
{
	int		i;
	char	*next_line;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	next_line = (char *)malloc((i + 1) * sizeof(char));
	if (!next_line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		next_line[i] = str[i];
		i++;
	}
	if (str[i])
		next_line[i++] = '\n';
	next_line[i] = '\0';
	return (next_line);
}

char	*new_str(char *str)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	new_str = (char *)malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!new_str)
		return (NULL);
	i++;
	j = 0;
	while (str[i])
		new_str[j++] = str[i++];
	new_str[j] = '\0';
	free(str);
	return (new_str);
}

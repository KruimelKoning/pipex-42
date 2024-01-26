/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbartels <lbartels@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/10 15:02:51 by lbartels      #+#    #+#                 */
/*   Updated: 2023/10/10 15:02:51 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_checkchar(char const *s, char c)
{
	size_t	count;

	if (!*s)
		return (0);
	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count++;
		while (*s != c && *s)
			s++;
	}
	return (count);
}

static size_t	ft_len(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (s[count] != c && s[count] != '\0')
		count++;
	return (count);
}

static void	ft_free_array(char **array, int i)
{
	while (i > 0)
	{
		free(array[i - 1]);
		i--;
	}
	free(array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		i;

	if (!s)
		return (NULL);
	array = (char **)ft_calloc((ft_checkchar(s, c) + 1), sizeof(char *));
	if (!array)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			array[i] = ft_substr(s, 0, ft_len(s, c));
			if (!array[i])
			{
				ft_free_array(array, i);
				return (NULL);
			}
			s += ft_len(s, c) - 1;
			i++;
		}
		s++;
	}
	return (array);
}

// static int	ft_checkchar(char const *s, char c)
// {
// 	int		count;
// 	int		i;
// 	char	*str;
// 	char	set[2];

// 	count = 0;
// 	i = 0;
// 	set[0] = c;
// 	set[1] = '\0';
// 	str = ft_strtrim(s, set);
// 	if (!str)
// 		return (-1);
// 	if (str[i])
// 		count = 1;
// 	while (str[i])
// 	{
// 		if (str[i] == c && str[i + 1] != c)
// 			count++;
// 		i++;
// 	}
// 	free(str);
// 	return (count);
// }
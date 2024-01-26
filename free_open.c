/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_open.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbartels <lbartels@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/24 16:49:14 by lbartels      #+#    #+#                 */
/*   Updated: 2024/01/24 16:49:43 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	open_file(char *file, char flag)
{
	int	fd;

	if (flag == 'i')
		fd = open(file, O_RDONLY);
	if (flag == 'o')
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (flag == 'h')
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
	{
		ft_putstr_fd(RED, 2);
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

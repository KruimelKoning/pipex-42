/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbartels <lbartels@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/06 16:43:52 by lbartels      #+#    #+#                 */
/*   Updated: 2023/12/08 17:34:58 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define RED "\x1b[31m"
# define YELLOW "\x1b[33m"
# define GREEN "\x1b[32m"
# define BLUE "\x1b[34m"
# define BLACK "\x1b[30m"

# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "libft/libft.h"

char	*get_path(char *cmd, char **env);
void	execute(char *cmd, char **env);
void	child_process(int *fd, char **argv, char **env);
void	parent_process(int *fd, char **argv, char **env);

#endif
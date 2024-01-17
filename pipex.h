/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbartels <lbartels@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/06 16:43:52 by lbartels      #+#    #+#                 */
/*   Updated: 2024/01/08 15:31:29 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define WHITE "\033[0;37m"

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

// BONUS
int		open_file(char *file, char flag);
void	ft_exit(int error);
void	ft_pipe(char *argv, char **env);

#endif
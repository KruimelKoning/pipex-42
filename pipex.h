/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbartels <lbartels@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/06 16:43:52 by lbartels      #+#    #+#                 */
/*   Updated: 2024/01/24 16:36:01 by lbartels      ########   odam.nl         */
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
# include <sys/types.h>
# include "libft/libft.h"

// struct :(
typedef struct process_id
{
	pid_t	p_id;
	pid_t	p_id2;
}	t_process_id;

typedef struct bonus_vars
{
	int		i;
	int		file_in;
	int		file_out;
	int		status;
	pid_t	p_id;
}	t_bonus_vars;

char	*get_path(char *cmd, char **env);
void	execute(char *cmd, char **env);
void	child_process(int *fd, char **argv, char **env);
void	parent_process(int *fd, char **argv, char **env);
void	ft_free_tab(char **tab);

// BONUS
int		open_file(char *file, char flag);
void	ft_exit(int error);
void	ft_pipe(char *argv, char **env);

#endif
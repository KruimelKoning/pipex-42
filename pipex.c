/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbartels <lbartels@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/08 17:23:47 by lbartels      #+#    #+#                 */
/*   Updated: 2024/01/24 16:35:45 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(int *fd, char **argv, char **env)
{
	int	file_in;

	close(fd[0]);
	file_in = open(argv[1], O_RDONLY);
	if (file_in == -1)
	{
		ft_putstr_fd(RED, 2);
		perror("Error opening file");
		ft_putstr_fd(WHITE, 2);
		exit(EXIT_FAILURE);
	}
	dup2(file_in, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(file_in);
	close(fd[1]);
	execute(argv[2], env);
}

void	parent_process(int *fd, char **argv, char **env)
{
	int	file_out;

	close(fd[1]);
	file_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file_out == -1)
	{
		ft_putstr_fd(RED, 2);
		perror("Error opening file");
		ft_putstr_fd(WHITE, 2);
		exit(EXIT_FAILURE);
	}
	dup2(file_out, STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	close(file_out);
	close(fd[0]);
	execute(argv[3], env);
}

int	main(int argc, char **argv, char **env)
{
	int				fd[2];
	int				status;
	t_process_id	process;

	if (argc != 5)
		ft_exit(1);
	pipe(fd);
	process.p_id = fork();
	if (!process.p_id)
		child_process(fd, argv, env);
	else
	{
		process.p_id2 = fork();
		if (!process.p_id2)
			parent_process(fd, argv, env);
		else
		{
			close(fd[0]);
			close(fd[1]);
			waitpid(process.p_id, NULL, 0);
			waitpid(process.p_id2, &status, 0);
			exit(WEXITSTATUS(status));
		}
	}
	return (0);
}

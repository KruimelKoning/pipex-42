/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbartels <lbartels@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/08 17:23:47 by lbartels      #+#    #+#                 */
/*   Updated: 2023/12/08 18:18:30 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(int *fd, char **argv, char **env)
{
	int file_in;

	close(fd[0]);
	file_in = open(argv[1], O_RDONLY);
	if (file_in == -1)
	{
		ft_putstr_fd(RED, 2);
		perror("Error opening file");
		exit(1);
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
		return ;
	}
	dup2(file_out, STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	close(file_out);
	close(fd[0]);
	execute(argv[3], env);
}

int main(int argc, char **argv, char **env)
{
	int	fd[2];
	pid_t p_id;

	if (argc == 5)
	{
		pipe(fd);
		p_id = fork();
		if (p_id == 0)
			child_process(fd, argv, env);
		waitpid(p_id, NULL, 0);
		parent_process(fd, argv, env);
	}
	else
	{
		ft_putstr_fd(YELLOW, 2);
		if (argc > 5)
			perror("Too many arguments");
		if (argc < 5)
			perror("Too few arguments");
		exit(1);
	}
	return (0);
}

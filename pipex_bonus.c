/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_bonus.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbartels <lbartels@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/11 15:10:20 by lbartels      #+#    #+#                 */
/*   Updated: 2024/01/16 13:31:24 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

static void	get_here_doc(int *fd, char *argv)
{
	char	*buffer;

	close(fd[0]);
	while (1)
	{
		ft_putstr_fd("pipe heredoc: ", 1);
		buffer = get_next_line(0);
		if (ft_strnstr(buffer, argv, ft_strlen(argv)))
		{
			free(buffer);
			exit(0);
		}
		ft_putstr_fd(buffer, fd[1]);
		free(buffer);
	}
}

void	here_doc(char **argv)
{
	int		fd[2];
	pid_t	p_id;

	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
	p_id = fork();
	if (p_id == -1)
		exit(EXIT_FAILURE);
	if (!p_id)
	{
		get_here_doc(fd, argv[2]);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		wait(NULL);
	}
}

void	ft_pipe(char *argv, char **env)
{
	int		fd[2];
	pid_t	p_id;

	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
	p_id = fork();
	if (p_id == -1)
		exit(EXIT_FAILURE);
	if (!p_id)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execute(argv, env);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
}

int	main(int argc, char **argv, char **env)
{
	int	i;
	int	file_in;
	int	file_out;
	pid_t	p_id;
	int	status;

	if (argc < 5 || (!ft_strncmp(argv[1], "here_doc", 8) && argc < 6))
		ft_exit(1);
	if (!ft_strncmp(argv[1], "here_doc", 8))
	{
		here_doc(argv);
		file_out = open_file(argv[argc - 1], 'h');
		i = 3;
	}
	else
	{
		file_in = open_file(argv[1], 'i');
		file_out = open_file(argv[argc - 1], 'o');
		dup2(file_in, STDIN_FILENO);
		close(file_in);
		i = 2;
	}
	p_id = fork();
	if (!p_id)
	{
		while (i < argc - 2)
			ft_pipe(argv[i++], env);
		dup2(file_out, STDOUT_FILENO);
		execute(argv[argc - 2], env);
	}
	else
	{
		waitpid(p_id, &status, 0);
		exit(WEXITSTATUS(status));
	}
	return (0);
}

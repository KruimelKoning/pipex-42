/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_bonus.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbartels <lbartels@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/11 15:10:20 by lbartels      #+#    #+#                 */
/*   Updated: 2024/01/24 16:33:21 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	fill_vars(t_bonus_vars *vars, int argc, char **argv)
{
	vars->file_out = open_file(argv[argc - 1], 'o');
	vars->file_in = open_file(argv[1], 'i');
	dup2(vars->file_in, STDIN_FILENO);
	close(vars->file_in);
	vars->i = 2;
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

void	here_doc(char **argv, int argc, t_bonus_vars *vars)
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
	vars->file_out = open_file(argv[argc - 1], 'h');
	vars->i = 3;
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
		exit(EXIT_SUCCESS);
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
	t_bonus_vars	vars;

	if (argc < 5 || (!ft_strncmp(argv[1], "here_doc", 8) && argc < 6))
		ft_exit(1);
	if (!ft_strncmp(argv[1], "here_doc", 8))
		here_doc(argv, argc, &vars);
	else
		fill_vars(&vars, argc, argv);
	vars.p_id = fork();
	if (!vars.p_id)
	{
		while (vars.i < argc - 2)
			ft_pipe(argv[vars.i++], env);
		dup2(vars.file_out, STDOUT_FILENO);
		execute(argv[argc - 2], env);
		exit(EXIT_SUCCESS);
	}
	close(vars.file_in);
	close(vars.file_out);
	waitpid(vars.p_id, &vars.status, 0);
	exit(WEXITSTATUS(vars.status));
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbartels <lbartels@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/08 17:24:37 by lbartels      #+#    #+#                 */
/*   Updated: 2024/01/16 11:24:49 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_exit(int error)
{
	if (error == 1 || error == 2)
	{
		ft_putstr_fd(RED, 2);
		ft_putstr_fd("ERROR: ", 2);
		ft_putstr_fd(GREEN, 2);
		if (error == 1)
			ft_putstr_fd("Too few arguments\n", 2);
		else
			ft_putstr_fd("Too many arguments\n", 2);
		ft_putstr_fd(WHITE, 2);
		exit(EXIT_FAILURE);
	}
	if (error == 3)
	{
		ft_putstr_fd(RED, 2);
		ft_putstr_fd("ERROR: empty argument\tpermission denied\n", 2);
		ft_putstr_fd(WHITE, 2);
		exit(126);
	}
}

static void	ft_free_tab(char **tab)
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

static char	*ft_getenv(char *name, char **env)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		temp = ft_substr(env[i], 0, j);
		if (!ft_strncmp(temp, name, ft_strlen(name)))
		{
			free(temp);
			return (env[i] + j + 1);
		}
		free(temp);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	**full_path;
	char	*path;
	char	*ret;

	if (!strncmp(cmd, "/bin/", 5))
		cmd += 5;
	full_path = ft_split(ft_getenv("PATH", env), ':');
	i = 0;
	while (full_path[i])
	{
		path = ft_strjoin(full_path[i], "/");
		ret = ft_strjoin(path, cmd);
		free(path);
		if (access(ret, F_OK | X_OK) == 0)
		{
			ft_free_tab(full_path);
			return (ret);
		}
		free(ret);
		i++;
	}
	ft_free_tab(full_path);
	return (NULL);
}

void	execute(char *cmd, char **env)
{
	char	**split_cmd;
	char	*path;

	if (!cmd[0])
		ft_exit(3);
	split_cmd = ft_split(cmd, ' ');
	path = get_path(split_cmd[0], env);
	if (!path)
	{
		ft_free_tab(split_cmd);
		ft_putstr_fd(RED, 2);
		perror("ERROR: command not found");
		ft_putstr_fd(WHITE, 2);
		exit (127);
	}
	if (execve(path, split_cmd, env) == -1)
	{
		free (path);
		ft_free_tab(split_cmd);
		ft_putstr_fd(RED, 2);
		perror("ERROR: could not execute this command");
		exit (EXIT_FAILURE);
	}
	free (path);
	ft_free_tab(split_cmd);
}

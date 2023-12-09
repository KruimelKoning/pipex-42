/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lbartels <lbartels@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/08 17:24:37 by lbartels      #+#    #+#                 */
/*   Updated: 2023/12/08 18:18:15 by lbartels      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_free_tab(char **tab)
{
	size_t	i;

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
	int	i;
	int	j;
	char *temp;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		temp = ft_substr(env[i], 0, j);
		if (!ft_strncmp(temp, name, 10))
		{
			free(temp);
			return (env[i] + j + 1);
		}
		free(temp);
		i++;
	}
	return (NULL);
}

char *get_path(char *cmd, char **env)
{
	int i;
	char **full_path;
	char *path;
	char *ret;

	full_path = ft_split(ft_getenv("PATH", env), ':');
	i = 0;
	while (full_path[i])
	{
		path = ft_strjoin(full_path[i], "/");
		ret = ft_strjoin(path, cmd);
		free(path);
		if (access(ret, F_OK | X_OK) == 0)
		{
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
	char **split_cmd;
	char *path;

	split_cmd = ft_split(cmd, ' ');
	path = get_path(split_cmd[0], env);
	if (!path)
	{
		ft_free_tab(split_cmd);
		perror("ERROR");
		exit (1);
	}
	if (execve(path, split_cmd, env) == -1)
	{
		perror("error");
		exit (1);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgoremyk <dgoremyk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 20:40:37 by dgoremyk          #+#    #+#             */
/*   Updated: 2022/12/02 18:38:18 by dgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*free_strjoin(char *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*dst;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	dst = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!dst)
		return (NULL);
	while (s1[i])
	{
		dst[i] = s1[i];
		i++;
	}
	free(s1);
	while (s2[j])
	{		
		dst[i] = s2[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (dst);
}

char	**path_splitter(t_node *data, char **av, char **envp)
{
	char	**path_splitted;
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		error_exit(data, "envp not valid", av);
	path_splitted = ft_split(envp[i] + 5, ':');
	i = 0;
	while (path_splitted[i])
	{
		path_splitted[i] = free_strjoin(path_splitted[i], "/");
		i++;
	}
	return (path_splitted);
}

char	**cmd_splitter(char *cmd)
{
	char	**cmd_splitted;

	if (!cmd)
		return (NULL);
	cmd_splitted = ft_split(cmd, ' ');
	return (cmd_splitted);
}

char	*get_valid_path(char **splitted_path, char *cmd)
{
	int		i;
	char	*valid_path;

	i = 0;
	while (splitted_path[i])
	{
		valid_path = ft_strjoin(splitted_path[i], cmd);
		if (access(valid_path, X_OK) == 0)
		{
			return (valid_path);
		}
		free(valid_path);
		i++;
	}
	return (NULL);
}

void	add_data(t_node *data, char **av, char **envp)
{
	data->cmd1 = cmd_splitter(av[2]);
	data->cmd2 = cmd_splitter(av[3]);
	data->path_splitted = path_splitter(data, av, envp);
	if (access(av[2], X_OK) == 0)
		data->valid_path1 = data->cmd1[0];
	else
		data->valid_path1 = get_valid_path(data->path_splitted, data->cmd1[0]);
	if (access(av[3], X_OK) == 0)
		data->valid_path2 = data->cmd2[0];
	else
		data->valid_path2 = get_valid_path(data->path_splitted, data->cmd2[0]);
}

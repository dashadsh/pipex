/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgoremyk <dgoremyk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 20:39:17 by dgoremyk          #+#    #+#             */
/*   Updated: 2022/12/02 16:23:37 by dgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_clear(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}

void	free_struct(t_node *data, char **av)
{
	if (data->path_splitted)
		ft_clear(data->path_splitted);
	if (data->cmd1)
		ft_clear(data->cmd1);
	if (data->cmd2)
		ft_clear(data->cmd2);
	if ((access(av[2], X_OK) != 0) && (data->valid_path1))
		free(data->valid_path1);
	if ((access(av[3], X_OK) != 0) && (data->valid_path2))
		free(data->valid_path2);
	free(data);
}

void	perror_exit(t_node *data, char **av)
{
	perror("");
	free_struct(data, av);
	exit(EXIT_FAILURE);
}

void	error_exit(t_node *data, char *msg, char **av)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
	free_struct(data, av);
	exit(EXIT_FAILURE);
}

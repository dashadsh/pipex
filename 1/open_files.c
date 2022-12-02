/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgoremyk <dgoremyk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 14:32:59 by dgoremyk          #+#    #+#             */
/*   Updated: 2022/12/02 16:35:12 by dgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_files(t_node *data, char **av)
{
	data->infile = open(av[1], O_RDONLY);
	data->outfile = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (data->infile == -1 || data->outfile == -1)
		perror_exit(data, av);
}

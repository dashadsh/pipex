/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgoremyk <dgoremyk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 21:15:05 by dgoremyk          #+#    #+#             */
/*   Updated: 2022/12/02 18:36:58 by dgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	empty_cmd_checker(t_node *data, char **av)
{
	if (av[2][0] == '\0' && av[3][0] == '\0')
	{
		write(STDERR_FILENO, "permission denied: \n", 20);
		write(STDERR_FILENO, "permission denied: \n", 20);
		free_struct(data, av);
		exit(EXIT_FAILURE);
	}
	else if (av[2][0] == '\0' || av[3][0] == '\0')
	{
		write(STDERR_FILENO, "permission denied: \n", 20);
		free_struct(data, av);
		exit(EXIT_FAILURE);
	}
}

void	both_cmd_not_found(t_node *data, char **av)
{		
	write(STDERR_FILENO, "command not found: ", 19);
	write(STDERR_FILENO, data->cmd1[0], ft_strlen(data->cmd1[0]));
	write(STDERR_FILENO, "\n", 1);
	write(STDERR_FILENO, "command not found: ", 19);
	write(STDERR_FILENO, data->cmd2[0], ft_strlen(data->cmd2[0]));
	write(STDERR_FILENO, "\n", 1);
	close(data->infile);
	close(data->outfile);
	free_struct(data, av);
	exit(EXIT_FAILURE);
}

void	empty_valid_path_checker(t_node *data, char **av)
{
	//printf("%s %s", data->valid_path1, data->valid_path2);
	if ((data->valid_path1 == NULL) && (data->valid_path2 == NULL))
		both_cmd_not_found(data, av);
	else if (data->valid_path1 == NULL)
	{
		write(STDERR_FILENO, "command not found: ", 19);
		write(STDERR_FILENO, data->cmd1[0], ft_strlen(data->cmd1[0]));
		write(STDERR_FILENO, "\n", 1);
		close(data->infile);
		close(data->outfile);
		free_struct(data, av);
		exit(EXIT_FAILURE);
	}
	else if (data->valid_path2 == NULL)
	{
		write(STDERR_FILENO, "command not found: ", 19);
		write(STDERR_FILENO, data->cmd2[0], ft_strlen(data->cmd2[0]));
		write(STDERR_FILENO, "\n", 1);
		close(data->infile);
		close(data->outfile);
		free_struct(data, av);
		exit(EXIT_FAILURE);
	}
}

void	wrong_cmd_checker(t_node *data, char **av)
{
	empty_valid_path_checker(data, av);
	if (access(data->valid_path1, X_OK) != 0
		&& access(data->valid_path2, X_OK) != 0)
		both_cmd_not_found(data, av);
	else if (access(data->valid_path1, X_OK) != 0)
	{
		write(STDERR_FILENO, "command not found: ", 19);
		write(STDERR_FILENO, data->cmd1[0], ft_strlen(data->cmd1[0]));
		write(STDERR_FILENO, "\n", 1);
		close(data->infile);
		close(data->outfile);
		free_struct(data, av);
		exit(EXIT_FAILURE);
	}
	else if (access(data->valid_path1, X_OK) != 0)
	{
		write(STDERR_FILENO, "command not found: ", 19);
		write(STDERR_FILENO, data->cmd2[0], ft_strlen(data->cmd2[0]));
		write(STDERR_FILENO, "\n", 1);
		close(data->infile);
		close(data->outfile);
		free_struct(data, av);
		exit(EXIT_FAILURE);
	}
}

void	early_error_check(t_node *data, int ac, char **av, char **envp)
{
	if (ac != 5)
		error_exit(data, "invalid input\n", av);
	if (!envp)
		error_exit(data, "envp error\n", av);
	empty_cmd_checker(data, av);
}

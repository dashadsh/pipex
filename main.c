/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgoremyk <dgoremyk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 20:35:16 by dgoremyk          #+#    #+#             */
/*   Updated: 2022/12/05 14:36:16 by dgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	empty_init(t_node *data)
{
	data->infile = -1;
	data->outfile = -1;
	data->path_splitted = NULL;
	data->cmd1 = NULL;
	data->cmd2 = NULL;
	data->valid_path1 = NULL;
	data->valid_path2 = NULL;
	data->pipe_fd[0] = -1;
	data->pipe_fd[1] = -1;
	data->pid1 = -1;
	data->pid2 = -1;
}

void	process_1(t_node *data, char **envp)
{
	close(data->outfile);
	close(data->pipe_fd[0]);
	dup2(data->infile, STDIN_FILENO);
	dup2(data->pipe_fd[1], STDOUT_FILENO);
	if (execve(data->valid_path1, data->cmd1, envp) == -1)
	{
		close(data->infile);
		close(data->pipe_fd[1]);
		perror("execve error on process 1: ");
		exit(EXIT_FAILURE);
	}
}

void	process_2(t_node *data, char **envp)
{
	close(data->infile);
	close(data->pipe_fd[1]);
	dup2(data->pipe_fd[0], STDIN_FILENO);
	dup2(data->outfile, STDOUT_FILENO);
	if (execve(data->valid_path2, data->cmd2, envp) == -1)
	{
		close(data->outfile);
		close(data->pipe_fd[0]);
		perror("execve error on process 2: ");
		exit(EXIT_FAILURE);
	}
}

void	pipex(t_node *data, char **envp)
{
	pipe(data->pipe_fd);
	if (pipe(data->pipe_fd) == -1)
		perror_exit(data);
	data->pid1 = fork();
	if (data->pid1 == -1)
		perror_exit(data);
	else if (data->pid1 == 0)
		process_1(data, envp);
	else
	{
		data->pid2 = fork();
		if (data->pid2 == -1)
			perror_exit(data);
		else if (data->pid2 == 0)
			process_2(data, envp);
		else
		{
			waitpid(-1, NULL, 0);
			close(data->pipe_fd[0]);
			close(data->pipe_fd[1]);
			close(data->infile);
			close(data->outfile);
			free_struct(data);
		}
	}
}

int	main(int ac, char **av, char **envp)
{
	t_node	*data;

	data = ft_calloc(sizeof(t_node), 1);
	if (!data)
		return (1);
	empty_init(data);
	early_error_check(data, ac, av, envp);
	open_files(data, av);
	add_data(data, av, envp);
	wrong_cmd_checker(data);
	pipex (data, envp);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgoremyk <dgoremyk@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 19:00:43 by dgoremyk          #+#    #+#             */
/*   Updated: 2022/12/02 16:34:44 by dgoremyk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/wait.h>

# include <stdlib.h>
/* EXIT_SUCCESS, EXIT_FAILURE */

# include <unistd.h>
/* STDERR_FILENO, STDOUT_FILENO */

# include <stdio.h>

# include <fcntl.h>

# include "libft/libft.h"

typedef struct s_node
{
	int		infile;
	int		outfile;
	char	**path_splitted;
	char	**cmd1;
	char	**cmd2;
	char	*valid_path1;
	char	*valid_path2;
	int		pipe_fd[2];
	int		pid1;
	int		pid2;
}				t_node;

void	empty_init(t_node *data);

void	ft_clear(char **str);
void	free_struct(t_node *data, char **av);

char	*free_strjoin(char *s1, char const *s2);

void	perror_exit(t_node *data, char **av);
void	error_exit(t_node *data, char *msg, char **av);

void	both_cmd_not_found(t_node *data, char **av);
void	empty_valid_path_checker(t_node *data, char **av);
void	wrong_cmd_checker(t_node *data, char **av);
void	empty_cmd_checker(t_node *data, char **av);
void	early_error_check(t_node *data, int ac, char **av, char **envp);

void	open_files(t_node *data, char **av);

char	**path_splitter(t_node *data, char **av, char **envp);
char	**cmd_splitter(char *cmd);
char	*get_valid_path(char **splitted_path, char *cmd);

void	add_data(t_node *data, char **av, char **envp);

void	process_1(t_node *data, char **envp);
void	process_2(t_node *data, char **envp);
void	pipex(t_node *data, char **av, char **envp);
int		main(int ac, char **av, char **envp);

#endif
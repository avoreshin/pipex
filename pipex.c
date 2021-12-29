/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlamonic <jlamonic@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 23:06:53 by jlamonic          #+#    #+#             */
/*   Updated: 2021/12/29 22:09:04 by jlamonic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_double_array(char **str)
{
	while(*str)
	{
		free(*str);
		str++;
	}
	free(str);
	str = NULL;
}

void	ft_free (t_struct *data)
{
	free(data->path);
	ft_free_double_array(data->cmd_arg);
	data->path = NULL;
	data->cmd_arg = NULL;
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void ft_part_path(char **env, t_struct *data, char *cmd_arg)
{

}

void ft_parsing_str(char *argv)
{

}

void	ft_parent_process(t_struct *data, char **argv, char **env, pid_t *pid)
{
	waitpid(*pid, &data->pid_status, WNOHANG);
	data->fd_outfile = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (data->fd_outfile < 0)
	{
		write(2, "outfile doesn't exist\n",22);
		exit(EXIT_FAILURE);
	}
	close(data->fd_pipe[1]);
	dup2(data->fd_pipe[0], STDIN_FILENO);
	close(data->fd_pipe[0]);
	dup2(data->fd_outfile,STDOUT_FILENO);
	data->cmd_arg = ft_split(argv[3], ' ');
	data->path = ft_part_path(env, data, data->cmd_arg[0]);
	if (execve(data->path, data->cmd_arg, env) == -1)
	{
		write(2,"command not found: ", 19);
		write(2,data->cmd_arg[0],ft_strlen(data->cmd_arg[0]));
		ft_free(data);
		exit(EXIT_FAILURE);
	}
}

void	ft_child_process(t_struct *data, char **argv, char **env)
{
	data->fd_infile = open(argv[1], O_RDONLY);
	if (data->fd_infile < 0)
	{
		write(1,"infile doesn't exist\n",21 );
		exit(EXIT_FAILURE);
	}
	close(data->fd_pipe[0]);
	dup2(data->fd_pipe[1], STDOUT_FILENO);
	close[data->fd_pipe[1]];
	dup2(data->fd_infile, STDIN_FILENO);
	data->cmd_arg = ft_parsing_str(argv[2]);
	data->path = ft_part_path(env, data, data->cmd_arg[0]);
	
}

void	ft_fork_process(t_struct *data, char **argv, char **env);
{
	pid_t	pid;

	pid = fork();
	if(pid == -1)
	{
		write(1,"fork failed\n",12);
		exit(EXIT_FAILURE);
	}
	else if(pid == 0)
		ft_child_process(data, argv, env);
	else if(pid > 0)
		ft_parent_process(data, argv, env, &pid);
}

int	main(int argc char **argv char **env)
{
	t_struct	data;

	if(argc != 5)
	{
		write(2,"usage: ./pipex file1 cmd1 cmd2 file2\n", 38);
		exit(EXIT_FAILURE);
	}
	if (pipe(data.fd_pipe) == -1)
	{
		write(2,"pipe failed\n",13);
		exit(EXIT_FAILURE);
	}
	ft_fork_process(&data, argv, env);
	ft_free(&data);
	close(data.fd_outfile);
	close(data.fd_infile);
	return (EXIT_SUCCESS);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlamonic <jlamonic@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 23:06:53 by jlamonic          #+#    #+#             */
/*   Updated: 2022/01/04 01:39:40 by jlamonic         ###   ########.fr       */
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

void	ft_extract_pathline(char **env, t_struct *data)
{
	int i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			data->partline = env[i] + 5;
		i++;
	}
}

void ft_part_path(char **env, t_struct *data, char *cmd_arg)
{
	t_path	path;
	int 	i;

	i = 0;
	if(!ft_strncmp(cmd_arg,"/",1))
		return (cmd_arg);
	ft_extract_pathline(env, data);
	path.split = ft_split(data->partline, ':');
	while (path.split[i])
	{
		path.temp1 = ft_strjoin(path.split[i], "/");
		path.temp2 = ft_strjoin(path.temp1, cmd_arg);
		free(path.temp1);
		if (access(path.temp2, F_OK | X_OK) == 0)
		{
			ft_free_double_array(path.split);
			return (path.temp2);
		}
		free(path.temp2);
		i++;
	}
	ft_free_double_array(path.split);
	return (NULL);
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
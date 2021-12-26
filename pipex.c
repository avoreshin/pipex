/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlamonic <jlamonic@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 23:06:53 by jlamonic          #+#    #+#             */
/*   Updated: 2021/12/26 22:47:22 by jlamonic         ###   ########.fr       */
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
	ft_fork_process(argv, env);
	ft_free(&data);
	close(data.fd_outfile);
	close(data.fd_infile);
	return (EXIT_SUCCESS);
}
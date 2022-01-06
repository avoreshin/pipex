/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlamonic <jlamonic@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 23:33:40 by jlamonic          #+#    #+#             */
/*   Updated: 2022/01/06 23:34:46 by jlamonic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

void	ft_free_double_array(char **str)
{
	while (*str)
	{
		free(*str);
		str++;
	}
	str = NULL;
}

void	ft_free(t_struct *data)
{
	free(data->path);
	ft_free_double_array(data->cmd_arg);
	data->path = NULL;
	data->cmd_arg = NULL;
}

void	ft_extract_pathline(char **env, t_struct *data)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			data->partline = env[i] + 5;
		i++;
	}
}

char	*ft_part_path(char **env, t_struct *data, char *cmd_arg)
{
	t_path	path;
	int		i;

	i = 0;
	if (!ft_strncmp(cmd_arg, "/", 1))
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

void	ft_execve_child(t_struct *data, char **env)
{
	if (execve(data->path, data->cmd_arg, env) == -1)
	{
		write(2, "command not found: ", 19);
		write(2, data->cmd_arg[0], ft_strlen(data->cmd_arg[0]));
		ft_free(data);
		exit(EXIT_FAILURE);
	}
}

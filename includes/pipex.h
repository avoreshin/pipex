/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlamonic <jlamonic@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 23:43:14 by jlamonic          #+#    #+#             */
/*   Updated: 2022/01/06 23:46:59 by jlamonic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <string.h>

typedef struct s_struct
{
	int			fd_infile;
	int			fd_outfile;
	int			fd_pipe[2];
	int			pid_status;
	char		*path;
	char		**cmd_arg;
	char		*partline;
}	t_struct;

typedef struct s_path
{
	char		**split;
	char		*temp1;
	char		*temp2;
	int			i;
}	t_path;

char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_free_double_array(char **str);
void	ft_free(t_struct *data);
void	ft_extract_pathline(char **env, t_struct *data);
char	*ft_part_path(char **env, t_struct *data, char *cmd_arg);
void	ft_execve_child(t_struct *data, char **env);

#endif
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
	int 	fd_infile;
	int		fd_outfile;
	int 	fd_pipe[2];
	int 	pid_status;
	char 	*path;
	char 	**cmd_arg;

} t_struct;

# endif
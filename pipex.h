#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include "libft/get_next_line.h"
# include "libft/ft_printf.h"
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdarg.h>
# include <string.h>
enum {
	MALLOC_ERROR = 1,
	FD_ERROR,
	EXEC_ERROR,
	PIPE_ERROR,
	PATH_CMD,
	PATH_INFILE,
	RIGHT_INFILE,
	RIGHT_OUTFILE,
	PATH_ENV
};

# define IN 1
# define OUT 0
# define READ 0
# define WRITE 1

typedef struct s_pipex
{
	char	*infile;
	char	*outfile;
	int		arg_nbr;
	int		exit_status;
}				t_pipex;

/*****Settings*****/
int	*setting_here_doc(int *fd, char *delimiter, char *outfile);
int	*set_fd(int *fd, char *infile, char*outfile);
int	*set_fd_to_use(int *fd, int fd_in, int fd_out);


void	exit_handler(int n_exit);
int		open_file(char *file, int n);
char	*my_getenv(char *name, char **env);
char	*get_path(char *cmd, char **env);
void	exec(char *cmd, int fd[2], char **env);
void	ft_free_tab(char **tab);
void	ft_strerror(int error, char *file);
int	ft_error(int error);

#endif
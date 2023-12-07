/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartel <gemartel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:37:24 by gemartel          #+#    #+#             */
/*   Updated: 2023/12/07 16:37:24 by gemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
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

/*****Settings*****/
int		*setting_here_doc(int *fd, char *delimiter, char *outfile);
int		*set_fd(int *fd, char *infile, char*outfile);
int		*set_fd_to_use(int *fd, int fd_in, int fd_out);

char	*get_path(char *cmd, char **env);
void	ft_free_tab(char **tab);
void	ft_strerror(int error, char *file);
int		command_receiver(int nb_cmd, char **cmds,
			char **env, int *fd_in_and_out);
void	perror_msg(char *msg);

#endif
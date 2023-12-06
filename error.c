/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartel <gemartel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:19:30 by gemartel          #+#    #+#             */
/*   Updated: 2023/12/04 16:19:30 by gemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_write_error(char *error_msg, char *file, int exit_code)
{
	write(2, error_msg, ft_strlen(error_msg));
	write(2, file, ft_strlen(file));
	write(2, "\n", 1);
	exit(exit_code);
}

void	ft_strerror(int error, char *file)
{
	printf("ft_strerror\n");
	if (error == PATH_CMD)
		ft_write_error("Error: command not found: ", file, 127);
	else if (error == PATH_INFILE) 
		ft_write_error("Error: no such file or directory: ", file, 2);
	else if (error == RIGHT_INFILE)
		ft_write_error("Error: permission denied: ", file, 3);
	else if (error == RIGHT_OUTFILE)
		ft_write_error("Error: permission denied: ", file, 4);
	else if (error == PATH_ENV)
		ft_write_error("Error: path variable does not exist", "", 5);
}

int	ft_error(int error)
{
	printf("ft_error\n");
	if (error == MALLOC_ERROR || error == FD_ERROR || error == EXEC_ERROR || PIPE_ERROR)
	{
		perror("Error");
		exit(6);
	}
	return (0);
}
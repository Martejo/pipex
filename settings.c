/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartel <gemartel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 10:57:21 by gemartel          #+#    #+#             */
/*   Updated: 2023/12/06 10:57:21 by gemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	*set_fd(int *fd, char *infile, char*outfile)
{
	fd[IN] = open(infile, O_RDONLY);
	if (fd[IN] == -1)
		perror(infile);
	fd[OUT] = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd[OUT] == -1)
		perror(outfile);
	return (fd);
}

int	*setting_here_doc(int *fd, char *delimiter, char *outfile)
{
	char	*str;
	int	p[2];

	if (pipe(p) == -1)
	{
		perror("Pipe creation error: (pipe)\n");
		exit(EXIT_FAILURE);
	}
	str = get_next_line(0);
	if (!str)
		ft_error(MALLOC_ERROR);
	while (ft_strncmp(str, delimiter, ft_strlen(delimiter)) != 0 && str != NULL )
	{
		if (write(p[WRITE], str, ft_strlen(str)) == -1)
		{
			ft_printf("pipex: write error: %s\n", strerror(errno));
			free(str);
			exit(EXIT_FAILURE);
		}
		free(str);
		str = get_next_line(0);
	}
	close(p[WRITE]);
	fd[IN] = p[READ];
	fd[OUT] = open(outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd[OUT] == -1) // A verifier plus tard cette gestion d'erreur
		perror(outfile);
	return (fd);
}

int	*set_fd_to_use(int *fd, int fd_in, int fd_out)
{
	fd[3] = fd_in;
	fd[2] = fd_out;
	return (fd);
}
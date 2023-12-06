#include "pipex.h"

void	exec(char *cmd, int fd[2], char **env)
{
	char	**s_cmd;
	char	*path;

	if (fd[IN] == -1 || fd[OUT] == -1)
		exit(EXIT_FAILURE);
	dup2(fd[IN], STDIN_FILENO);
	close(fd[IN]);
	dup2(fd[OUT], STDOUT_FILENO);
	close(fd[OUT]);
	s_cmd = ft_split(cmd, ' '); // gerer les whitespaces + malloc
	path = get_path(s_cmd[0], env);
	if (!path)
	{
		printf("error path\n");
		ft_free_tab(s_cmd);
		ft_strerror(PATH_CMD, cmd);
		exit(EXIT_FAILURE);
	}
	if (execve(path, s_cmd, env) == -1)
	{
		printf("error execve\n");
		free(path);
		ft_free_tab(s_cmd);
		ft_printf("pipex: failed to execute a command: %s\n", cmd);
		exit(EXIT_FAILURE);
	}
}

void	parent_process(int *fd_to_use, int *p)
{
	close(fd_to_use[IN]);
	close(fd_to_use[OUT]);
	fd_to_use[IN] = p[READ];
}

int	wait_pids(int *pid, int len)
{
	int	i;
	int	status;

	i = 0;
	while (i < len)
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
	free(pid);
	return (status);
}

int	fork_exec(char *cmd, int *fds, char **env, int *pid_tab)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		perror("pid\n");
	if (pid == 0)
	{
		free(pid_tab);
		close(fds[READ]);
		exec(cmd, &fds[2], env);
	}
	return (pid);
}

int	command_receiver(int nb_cmd, char **cmds, char **env, int *fd_in_and_out)
{
	int	fds[4];
	int	*pid;
	int	i;

	i = -1;
	pid = (int *)malloc(sizeof(int) * nb_cmd);
	if (!pid)
		perror("malloc");
	printf("fd[IN] = %d fd[OUT] = %d\n", fd_in_and_out[IN], fd_in_and_out[OUT]);
	while (++i < nb_cmd)
	{
		
		if (pipe(fds) == -1)
			ft_error(PIPE_ERROR);
		printf("-------------\n");
		if (i == 0)
			set_fd_to_use(fds, fd_in_and_out[IN], fds[WRITE]);
		else if (i == nb_cmd - 1)
			set_fd_to_use(fds, fds[2 + IN], fd_in_and_out[OUT]);
		else
			set_fd_to_use(fds, fds[2 + IN], fds[2 + OUT]);
		printf("avant fork et parent fds[0] =%d fds[1] =%d |||| fds[2] =%d fds[3] = %d\n\n", fds[0], fds[1], fds[2], fds[3]);
		pid[i] = fork_exec(cmds[i], fds, env, pid);
		parent_process(&fds[2], fds);
		printf("apres fork et parent fds[0] =%d fds[1] =%d |||| fds[2] =%d fds[3] = %d\n\n", fds[0], fds[1], fds[2], fds[3]);
	}
	i = wait_pids(pid, nb_cmd);
	return (i);
}

/*int command_receiver(int nb_cmd, char **cmds, char **env, int *fd) 
{
    int pipe_fd[2];
	int *pid;
	int  i;
    int prev_read_fd; 
	int in_fd;
	int out_fd;
	prev_read_fd = fd[IN]; // Utiliser pour stocker l'extrémité de lecture du pipe précédent
	i = -1;
    pid = (int *)malloc(sizeof(int) * nb_cmd);
    if (!pid) 
		ft_error(MALLOC_ERROR);

	while (++i < nb_cmd)
	{
		 if (i < nb_cmd - 1) 
		 {
            if (pipe(pipe_fd) == -1) 
			ft_error(PIPE_ERROR);
		 }
    	else 
            pipe_fd[WRITE] = fd[OUT];
		if (i == 0) 
    		in_fd = fd[IN]; // Entrée pour la première commande
 		else 
    		in_fd = prev_read_fd; // Entrée pour les commandes suivantes
		if (i < nb_cmd - 1)
			out_fd = pipe_fd[WRITE]; // Sortie pour toutes sauf la dernière commande
		else 
			out_fd = fd[OUT]; // Sortie pour la dernière commande
		pid[i] = fork_exec(cmds[i], (int[]){in_fd, out_fd}, env, pid);
        if (i < nb_cmd - 1) 
		{
            if (i > 0)
				close(prev_read_fd); // Fermer l'extrémité de lecture du pipe précédent
            prev_read_fd = pipe_fd[READ]; // Mettre à jour pour la prochaine commande
            close(pipe_fd[WRITE]); // Toujours fermer l'extrémité d'écriture du pipe actuel
        }
	}
    int status = wait_pids(pid, nb_cmd);
    return status;
}*/


/*int command_receiver(int nb_cmd, char **cmds, char **env, int *fd) 
{
    int pipe_fd[2];
	int *pid;
	int  i; 
	int prev_read_fd;
	
	prev_read_fd = fd[IN];
    pid = (int *)malloc(sizeof(int) * nb_cmd);
    if (!pid) 
		ft_error(MALLOC_ERROR);

    for (i = 0; i < nb_cmd; i++) 
	{

        if (i < nb_cmd - 1)
		{
			if (pipe(pipe_fd) == -1)
				ft_error(PIPE_ERROR);
        } 
		else
			pipe_fd[WRITE] = fd[OUT]; // Pour la dernière commande
		if (i == 0)
			pipe_fd[READ] = fd[IN];
		else
			 pipe_fd[READ] = prev_read_fd;
		pid[i] = fork_exec(cmds[i], pipe_fd, env, pid);
		printf("Command: %s, Pipe read fd: %d, Pipe write fd: %d\n", cmds[i], pipe_fd[READ], pipe_fd[WRITE]);
        if (i < nb_cmd - 1) 
		{
			if (i > 0) 
				close(prev_read_fd); // Fermer l'extrémité de lecture du pipe précédent
			prev_read_fd = pipe_fd[READ];
			close(pipe_fd[WRITE]); // Toujours fermer l'extrémité d'écriture du pipe actuel
        }
    }
    int status = wait_pids(pid, nb_cmd);
    return status;
}*/


//pid[i] = fork_exec(cmds[i], (i == 0) ? (int[]){fd[IN], pipe_fd[WRITE]} : (int[]){prev_read_fd, pipe_fd[WRITE]}, env, pid);
/*int command_receiver(int nb_cmd, char **cmds, char **env, int *fd) {
    int pipe_fd[2], *pid, i, prev_read_fd = fd[IN];

    pid = (int *)malloc(sizeof(int) * nb_cmd);
    if (!pid) ft_error(MALLOC_ERROR);

    for (i = 0; i < nb_cmd; i++) {
        if (i < nb_cmd - 1) {
            if (pipe(pipe_fd) == -1) ft_error(PIPE_ERROR);
        } else {
            pipe_fd[WRITE] = fd[OUT];
        }

        if (i == 0) {
            pipe_fd[READ] = fd[IN];
        } else {
            pipe_fd[READ] = prev_read_fd;
        }

        pid[i] = fork_exec(cmds[i], pipe_fd, env, pid);

        if (i > 0) close(prev_read_fd);
        if (i < nb_cmd - 1) {
            close(pipe_fd[WRITE]);
            prev_read_fd = pipe_fd[READ];
        }
    }

    int status = wait_pids(pid, nb_cmd);
    return status;
}*/






int	check_args(int argc, char **argv, char **envp)
{
	if (envp == NULL)
	{
		ft_putstr_fd( "Error: Environment Path missing\n", 2);
		exit(EXIT_FAILURE);
	}
	if (argc < 5)
	{
		ft_putstr_fd("pipex: invalid number of arguments.\n", 2);
		exit(EXIT_FAILURE);
	}
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		if (argc < 6)
		{
			ft_putstr_fd("pipex: invalid number of arguments.\n", 2);
			exit(EXIT_FAILURE);
		}
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int	status;
	int	fd[2];

	if (check_args(argc, argv, envp) == 1)
	{
		setting_here_doc(fd, argv[2], argv[argc - 1]);
		status = command_receiver(argc - 4, &argv[3], envp, fd);
		return (status);
	}
	set_fd(fd, argv[1], argv[argc-1]);
	status = command_receiver(argc - 3, &argv[2], envp, fd);
	status = WEXITSTATUS(status);
	return (status);
}
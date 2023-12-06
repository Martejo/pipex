#include "pipex.h"

void	exit_handler(int n_exit)
{
	if (n_exit == 1)
		ft_putstr_fd("./pipex infile cmd cmd outfile\n", 2);
	exit(1);
}

/*int	open_file(char *file, int in_or_out)
{
	int	ret;
	if (in_or_out == 0)
	{
		if (access(file, F_OK) == -1)
		{
			printf("acces f_ok\n");
			ft_strerror(PATH_INFILE, file);
		}	
		else if (access(file, R_OK) == -1)
		{
			printf("access r_ok\n");
			ft_strerror(RIGHT_INFILE, file);
		}
		ret = open(file, O_RDONLY, 0777);
		if (ret == -1)
		{
			printf("open filein\n");
			ft_strerror(PATH_INFILE, file);
		}
	}
	if (in_or_out == 1)
	{
		ret = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (ret == -1)
			ft_error(FD_ERROR);
	}
	if (in_or_out == 2)
	{
		ret = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (ret == -1)
			ft_error(FD_ERROR);
	}
	return (ret);
}*/

void	ft_free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*my_getenv(char *name, char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j);
		if (!sub)
			ft_error(MALLOC_ERROR);
		if (ft_strcmp(sub, name) == 0)
		{
			free(sub);
			return (env[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;
	char	**s_cmd;

	i = -1;
	allpath = ft_split(my_getenv("PATH", env), ':');
	if (!allpath)
		return (NULL);
	s_cmd = ft_split(cmd, ' ');
	if (!s_cmd)
	{
		ft_free_tab(allpath);
		return (NULL);
	}
	while (allpath[++i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		if (!path_part)
		{
			ft_free_tab(allpath);
			ft_free_tab(s_cmd);
			return (NULL);
		}
		exec = ft_strjoin(path_part, s_cmd[0]);
		if (!exec)
		{
			free(path_part);
			ft_free_tab(allpath);
			ft_free_tab(s_cmd);
			return (NULL);
		}
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
		{
			ft_free_tab(s_cmd);
			ft_free_tab(allpath);
			return (exec);
		}
		free(exec);
	}
	if (ft_strchr(s_cmd[0], '/') && access(s_cmd[0], F_OK) == 0)
	{
		ft_free_tab(allpath);
		ft_free_tab(s_cmd);
		exec = ft_strdup(s_cmd[0]);
		return (exec);
	}
	ft_free_tab(allpath);
	ft_free_tab(s_cmd);
	return (NULL);
}
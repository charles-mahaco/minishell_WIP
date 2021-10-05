#include "minishell.h"

void	exec_cmd(char **cmd)
{
	pid_t	pid;
	int		status;

	// On fork
	pid = fork();
	if (pid == -1)
		perror("fork");
	// Si le fork a reussit, le processus pere attend l'enfant (process fork)
	else if (pid > 0)
	{
		// On block le processus parent jusqu'a ce que l'enfant termine puis
		// on kill le processus enfant
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	}
	else if (pid == 0)
	{
		// Le processus enfant execute la commande ou exit si execve echoue
		if (execve(cmd[0], cmd, NULL) == -1)
			perror("shell");
		exit(EXIT_FAILURE);
	}
}

void	get_absolute_path(char **cmd)
{
	char	*path;
	char	*bin;
	char	**path_split;
	int		i;

	i = -1;
	path = strdup(getenv("PATH"));
	if (path == NULL)
		path = strdup("/bin:/usr/local/bin:/usr/bin:/bin:/usr/local/sbin");
	if (cmd[0][0] != '/' && ft_strncmp(cmd[0], "./", 2) != 0)
	{
		path_split = my_str_to_wordtab(path, ':');
		free(path);
		path = NULL;
		while (path_split[++i])
		{
			bin = (char *)calloc(sizeof(char), (ft_strlen1(path_split[i])
						+ 1 + ft_strlen1(cmd[0]) + 1));
			if (bin == NULL)
				break ;
			strcat(bin, path_split[i]);
			strcat(bin, "/");
			strcat(bin, cmd[0]);
			if (access(bin, F_OK) == 0)
				break ;
			free(bin);
			bin = NULL;
		}
		free_array(path_split);
		free(cmd[0]);
		cmd[0] = bin;
	}
	else
	{
		free(path);
		path = NULL;
	}
}

void	dup_env(char **envp, t_env **first)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		add_tail(strdup(envp[i]), first);
		i++;
	}
}

char	*get_env_var(char *var, t_env *first)
{
	t_env	*tmp;
	size_t	len;

	len = ft_strlen1(var);
	tmp = first;
	while (tmp)
	{
		if (!ft_strncmp(var, tmp->var, len))
			return (tmp->var);
		tmp = tmp->next;
	}
	return (NULL);
}

int	main(int argc, char **argv, char **envp)
{
	char			*buffer;
	size_t			buf_size;
	char			**cmd_line;
	static t_env	*first = NULL;

	buf_size = 2048;
	dup_env(envp, &first);
	buffer = (char *)calloc(sizeof(char), buf_size);
	if (buffer == NULL)
	{
		perror("Malloc failure");
		return (EXIT_FAILURE);
	}
	write(1, "~mahaco~ $> ", 12);
	while (get_next_line(0, &buffer) > 0)
	{
		cmd_line = my_str_to_wordtab(buffer, ' ');
		if (cmd_line[0] == NULL)
			printf("command not found\n");
		else if (is_built_in(cmd_line[0]) == false)
		{
			get_absolute_path(cmd_line);
			exec_cmd(cmd_line);
		}
		else
			exec_built_in(cmd_line, first);
		write(1, "~mahaco~ $> ", 12);
		free_array(cmd_line);
	}
	printf("Bye \n");
	free_lst(&first);
	free(buffer);
}

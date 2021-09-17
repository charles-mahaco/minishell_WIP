#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <wait.h>
#include <string.h>
#include <stdbool.h>
#include <linux/limits.h>
#include "get_next_line.h"
#include "minishell.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int i;
	unsigned char *src1;
	unsigned char *src2;

	i = 0;
	src1 = (unsigned char *)s1;
	src2 = (unsigned char *)s2;
	while (src1[i] && src2[i] && i < n)
	{
		if (src1[i] != src2[i])
			return (src1[i] - src2[i]);
		i++;
	}
	if (i < n && ((src1[i] == '\0' && src2[i] != '\0') ||
				(src2[i] == '\0' && src1[i] != '\0')))
		return (src1[i] - src2[i]);
	return (0);
}

size_t	ft_strlen1(const char *s)
{
	unsigned int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void free_array(char **str)
{
	int i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
}

int    count_word(char *str, char separator)
{
  int  i;
  int  n;

  i = 0;
  n = 1;
  while (str[i] != '\0' && str[i] != '\n')
    {
      if (str[i] == separator && str[i + 1] != '\0')
        n++;
      i++;
    }
  return (n);
}

int    count_char(char *str, char separator)
{
  int  c;

  c = 0;
  while ((str[c] != separator) && (str[c] != '\0') && (str[c] != '\n'))
    c++;
  return (c);
}

char    **my_str_to_wordtab(char *str, char separator)
{
  char  **tab;
  int  i;
  int  b;
  int  a;

  b = 0;
  i = 0;
  a = 0;
  if (str == NULL)
  	return (NULL);
  tab = malloc(sizeof(*tab) * ((count_word(str, separator) + 1)));
  if (!tab)
  	return (NULL);
  while (str[i] != '\t' && str[i] != '\0')
    {
      if (str[i] == separator || str[i] == '\n')
        {
          while (str[i] == separator)
            i++;
          a++;
          b = 0;
        }
      tab[a] = malloc(sizeof(**tab) * ((count_char(str + i, separator) + 1)));
      while ((str[i] != separator)  && (str[i] != '\n') && (str[i] != '\0'))
        tab[a][b++] = str[i++];
      tab[a][b] = '\0';
    }
  tab[a + 1] = NULL;
  return (tab);
}

static void add_tail(char *var, t_env **first)
{
	t_env	*ptr = (*first);
	t_env	*new_node = NULL;

	new_node = (t_env *)calloc(sizeof(t_env), 1);
	if (new_node == NULL) {
		printf("Alloc failure\n");
		return ;
	}

	new_node->var = var;
	new_node->next = NULL;

	if (ptr == NULL) {
		(*first) = new_node;
	} else {
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = new_node;
	}
}

static void	exec_cmd(char **cmd)
{
	pid_t	pid = 0;
	int		status = 0;

	// On fork
	pid = fork();
	if (pid == -1)
		perror("fork");
	// Si le fork a reussit, le processus pere attend l'enfant (process fork)
	else if (pid > 0) {
		// On block le processus parent jusqu'a ce que l'enfant termine puis
		// on kill le processus enfant
		
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	} else if (pid == 0) {
		// Le processus enfant execute la commande ou exit si execve echoue
		if (execve(cmd[0], cmd, NULL) == -1)
			perror("shell");
		exit(EXIT_FAILURE);
	}
}

static void	get_absolute_path(char **cmd)
{
	char	*path = strdup(getenv("PATH"));
	char	*bin = NULL;
	char	**path_split = NULL;

	if (path == NULL)
		path = strdup("/bin:/usr/local/bin:/usr/bin:/bin:/usr/local/sbin");

	if (cmd[0][0] != '/' && strncmp(cmd[0], "./", 2) != 0) {
		path_split = my_str_to_wordtab(path, ':');
		free(path);
		path = NULL;
		
		for (int i = 0; path_split[i]; i++) {
			bin = (char *)calloc(sizeof(char), (strlen(path_split[i]) + 1 + strlen(cmd[0]) + 1));
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

	} else {
		free(path);
		path = NULL;
	}
}

static char	*get_env_var(char *var, t_env *first)
{
	t_env	*tmp = first;
	size_t	len = 0;

	len = strlen(var);

	while (tmp) {
		if (!ft_strncmp(var, tmp->var, len)) {
			return (tmp->var);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

static void pop_lst(char *var_name, char *var, t_env **first)
{
	t_env	*ptr = (*first);
	char *newvar;

	newvar = calloc(sizeof(char), (ft_strlen1(var_name) + ft_strlen1(var)) + 1);
	strcat(newvar, var_name);
	strcat(newvar, var);
	while (ptr->next)
	{
		if (!ft_strncmp(var_name, ptr->var, ft_strlen1(var_name)))
		{
			ptr->var = newvar;
			break ;
		}
		ptr = ptr->next;
	}
}

void built_in_cd(char *path, t_env *first)
{
	char cwd[PATH_MAX];

	if (chdir(path) != 0)
		perror("chdir()");
	pop_lst("OLDPWD=", strrchr(get_env_var("PWD=", first), '=') + 1, &first);
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		perror("getcwd()");
	pop_lst("PWD=", cwd, &first);
}

void	built_in_pwd(void)
{
	char cwd[PATH_MAX];
	
	if (getcwd(cwd, sizeof(cwd)) != NULL) {
	       printf("%s\n", cwd);
	} else {
		perror("getcwd()");
	}
}

void built_in_env(t_env *head) {
    t_env *current_node = head;

   	while ( current_node != NULL)
   	{
        printf("%s\n", current_node->var);
        current_node = current_node->next;
    }
}

void built_in_export(char *var, t_env *first)
{
	int i;
	char *var_name;

	i = 0;
	if (strrchr(var, '='))
	{
		while (var[i] != '=')
			i++;
		var_name = calloc(sizeof(char), i + 1);
		i = 0;
		while(var[i] != '=')
		{
			var_name[i] = var[i];
			i++;
		}
		var_name[i] = '=';
		if (get_env_var(var_name, first))
			pop_lst(var_name, strrchr(var, '=') + 1, &first);
		else
			add_tail(strdup(var), &first);
		free(var_name);
	}
}

void built_in_echo(char **var)
{
	int i;
	int l;

	i = (!ft_strncmp(var[1], "-n", ft_strlen1(var[0]))) ? 2 : 1;
	while (var[i])
	{
		l = 0;
		while (var[i][l])
		{
			if (var[i][l] != '"' && var[i][l] != 39)
				write(1, &var[i][l], 1);
			l++;
		}
		i++;
		if (var[i])
			write(1," ",1);
		else if (ft_strncmp(var[1], "-n", ft_strlen1(var[0])))
			write(1, "\n", 1);
	}
}

void	built_in_unset(char *var, t_env **first)
{
	t_env	*prev;
	t_env	*current;

	prev = NULL;
	current = *first;
	while (current != NULL) {	
		if (!ft_strncmp(var, current->var, ft_strlen1(var)))
		{
			if (prev == NULL)
				*first = current->next;
			else
				prev->next = current->next;
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

static bool is_built_in(char *cmd)
{
	if (!ft_strncmp(cmd, "cd", ft_strlen1(cmd)) || !ft_strncmp(cmd, "pwd", ft_strlen1(cmd))
		|| !ft_strncmp(cmd, "env", ft_strlen1(cmd)) || !ft_strncmp(cmd, "export", ft_strlen1(cmd))
		|| !ft_strncmp(cmd, "echo", ft_strlen1(cmd)) || !ft_strncmp(cmd, "unset", ft_strlen1(cmd)))
	{
		return (true);
	}
	else
		return (false);
}

static void exec_built_in(char **cmd, t_env *first)
{
	if (!ft_strncmp(cmd[0], "cd", ft_strlen1(cmd[0])))
		built_in_cd(cmd[1], first);
	else if (!ft_strncmp(cmd[0], "pwd", ft_strlen1(cmd[0])))
		built_in_pwd();
	else if (!ft_strncmp(cmd[0], "env", ft_strlen1(cmd[0])))
		built_in_env(first);
	else if (!ft_strncmp(cmd[0], "export", ft_strlen1(cmd[0])))
		built_in_export(cmd[1], first);
	else if (!ft_strncmp(cmd[0], "unset", ft_strlen1(cmd[0])))
		built_in_unset(cmd[1], &first);
	else if (!ft_strncmp(cmd[0], "echo", ft_strlen1(cmd[0])))
		built_in_echo(cmd);
}

static void dup_env(char **envp, t_env **first)
{
	int i;

	i = 0;
	while (envp[i])
	{
		add_tail(strdup(envp[i]), first);
		i++;
	}
}

static void	free_lst(t_env **first)
{
	t_env	*idx = (*first);
	t_env	*tmp = idx;

	while (idx != NULL) {
		tmp = idx;
		idx = idx->next;
		free(tmp->var);
		tmp->var = NULL;
		free(tmp);
		tmp = NULL;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*buffer = NULL;
	size_t	buf_size = 2048;
	char	**cmd_line;
	static t_env	*first = NULL;

	dup_env(envp, &first);
	//built_in_env(first);
	//built_in_unset("CLUTTER_IM_MODULE", &first);
	//built_in_env(first);
	buffer = (char *)calloc(sizeof(char), buf_size);
	if (buffer == NULL) {
		perror("Malloc failure");
		return (EXIT_FAILURE);
	}

	write(1, "~mahaco~ $> ", 12);

	while (get_next_line(0, &buffer) > 0) {
		
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

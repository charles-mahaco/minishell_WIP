/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 15:59:39 by charles           #+#    #+#             */
/*   Updated: 2021/10/05 15:59:42 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <string.h>
# include <stdbool.h>
# include <limits.h>
# include <time.h>
# include "get_next_line.h"
# include "ft_printf.h"

typedef struct s_env
{
	char			*var;
	struct s_env	*next;
}					t_env;

int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strrchr(const char *s, int c);
size_t	ft_strlen(const char *s);
void	free_array(char **str);
int		count_word(char *str, char separator);
int		count_char(char *str, char separator);
char	**my_str_to_wordtab(char *str, char separator);
void	add_tail(char *var, t_env **first);
void	free_lst(t_env **first);
void	pop_lst(char *var_name, char *var, t_env **first);

void	built_in_export(char *var, t_env *first);
void	built_in_echo(char **var);
void	built_in_unset(char *var, t_env **first);
bool	is_built_in(char *cmd);
void	exec_built_in(char **cmd, t_env *first);
void	built_in_cd(char *path, t_env *first);
void	built_in_pwd(void);
void	built_in_env(t_env *head);

char	*get_env_var(char *var, t_env *first);
void	dup_env(char **envp, t_env **first);
void	get_absolute_path(char **cmd);
void	exec_cmd(char **cmd);
char	*ft_strcat(char *dest, const char *src);
char	*ft_strdup(const char *s1);

#endif

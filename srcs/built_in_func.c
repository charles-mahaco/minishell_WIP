/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 15:59:55 by charles           #+#    #+#             */
/*   Updated: 2021/10/05 15:59:58 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	built_in_export(char *var, t_env *first)
{
	int		i;
	char	*var_name;

	i = 0;
	if (ft_strrchr(var, '='))
	{
		while (var[i] != '=')
			i++;
		var_name = ft_calloc(sizeof(char), i + 1);
		i = 0;
		while (var[i] != '=')
		{
			var_name[i] = var[i];
			i++;
		}
		var_name[i] = '=';
		if (get_env_var(var_name, first))
			pop_lst(var_name, ft_strrchr(var, '=') + 1, &first);
		else
			add_tail(ft_strdup(var), &first);
		free(var_name);
	}
}

void	built_in_echo(char **var)
{
	int	i;
	int	l;

	if (!ft_strncmp(var[1], "-n", ft_strlen(var[0])))
		i = 2;
	else
		i = 1;
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
			write(1, " ", 1);
		else if (ft_strncmp(var[1], "-n", ft_strlen(var[0])))
			write(1, "\n", 1);
	}
}

void	built_in_unset(char *var, t_env **first)
{
	t_env	*prev;
	t_env	*current;

	prev = NULL;
	current = *first;
	while (current != NULL)
	{
		if (!ft_strncmp(var, current->var, ft_strlen(var)))
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

bool	is_built_in(char *cmd)
{
	if (!ft_strncmp(cmd, "cd", ft_strlen(cmd))
		|| !ft_strncmp(cmd, "pwd", ft_strlen(cmd))
		|| !ft_strncmp(cmd, "env", ft_strlen(cmd))
		|| !ft_strncmp(cmd, "export", ft_strlen(cmd))
		|| !ft_strncmp(cmd, "echo", ft_strlen(cmd))
		|| !ft_strncmp(cmd, "unset", ft_strlen(cmd)))
		return (true);
	else
		return (false);
}

void	exec_built_in(char **cmd, t_env *first)
{
	if (!ft_strncmp(cmd[0], "cd", ft_strlen(cmd[0])))
		built_in_cd(cmd[1], first);
	else if (!ft_strncmp(cmd[0], "pwd", ft_strlen(cmd[0])))
		built_in_pwd();
	else if (!ft_strncmp(cmd[0], "env", ft_strlen(cmd[0])))
		built_in_env(first);
	else if (!ft_strncmp(cmd[0], "export", ft_strlen(cmd[0])))
		built_in_export(cmd[1], first);
	else if (!ft_strncmp(cmd[0], "unset", ft_strlen(cmd[0])))
		built_in_unset(cmd[1], &first);
	else if (!ft_strncmp(cmd[0], "echo", ft_strlen(cmd[0])))
		built_in_echo(cmd);
}

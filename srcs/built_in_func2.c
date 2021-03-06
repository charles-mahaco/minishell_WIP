/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_func2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 16:00:07 by charles           #+#    #+#             */
/*   Updated: 2021/10/05 16:00:09 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	built_in_cd(char *path, t_env *first)
{
	char	cwd[PATH_MAX];

	if (!path)
		path = ft_strrchr(get_env_var("HOME=", first), '=') + 1;
	if (chdir(path) != 0)
		perror("chdir()");
	pop_lst("OLDPWD=", ft_strrchr(get_env_var("PWD=", first), '=') + 1, &first);
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		perror("getcwd()");
	pop_lst("PWD=", cwd, &first);
}

void	built_in_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("getcwd()");
}

void	built_in_env(t_env *head)
{
	t_env	*current_node;

	current_node = head;
	while (current_node != NULL)
	{
		printf("%s\n", current_node->var);
		current_node = current_node->next;
	}
}

void	built_in_exit(char **cmd, t_data *data)
{
	free_array(cmd);
	free_lst(&data->env);
	free(data->prompt);
	exit(3);
}
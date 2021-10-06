/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 16:00:23 by charles           #+#    #+#             */
/*   Updated: 2021/10/05 16:00:24 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**my_str_to_wordtab(char *str, char separator)
{
	char	**tab;
	int		i;
	int		b;
	int		a;

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
		while ((str[i] != separator) && (str[i] != '\n') && (str[i] != '\0'))
			tab[a][b++] = str[i++];
		tab[a][b] = '\0';
	}
	tab[a + 1] = NULL;
	return (tab);
}

void	add_tail(char *var, t_env **first)
{
	t_env	*ptr;
	t_env	*new_node;

	ptr = (*first);
	new_node = (t_env *)ft_calloc(sizeof(t_env), 1);
	if (new_node == NULL)
	{
		printf("Alloc failure\n");
		return ;
	}
	new_node->var = var;
	new_node->next = NULL;
	if (ptr == NULL)
		(*first) = new_node;
	else
	{
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = new_node;
	}
}

void	free_lst(t_env **first)
{
	t_env	*idx;
	t_env	*tmp;

	idx = (*first);
	tmp = idx;
	while (idx != NULL)
	{
		tmp = idx;
		idx = idx->next;
		free(tmp->var);
		tmp->var = NULL;
		free(tmp);
		tmp = NULL;
	}
}

void	pop_lst(char *var_name, char *var, t_env **first)
{
	t_env	*ptr;
	char	*newvar;

	ptr = (*first);
	newvar = ft_calloc(sizeof(char), (ft_strlen(var_name) + ft_strlen(var)) + 1);
	ft_strcat(newvar, var_name);
	ft_strcat(newvar, var);
	while (ptr->next)
	{
		if (!ft_strncmp(var_name, ptr->var, ft_strlen(var_name)))
		{
			free(ptr->var);
			ptr->var = newvar;
			break ;
		}
		ptr = ptr->next;
	}
}

void	free_array(char **str)
{
	int	i;

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

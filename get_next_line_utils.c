/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 15:40:46 by sdunckel          #+#    #+#             */
/*   Updated: 2019/10/28 16:23:53 by sdunckel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *s, int gnl)
{
	size_t		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n' && gnl)
			return (i);
		i++;
	}
	return (i);
}

int		is_in_s(char c, char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	if (str[i] == c)
		return (i);
	return (-1);
}

char	*ft_strjoin_n_free(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(str = ft_calloc(ft_strlen(s1, 0) + ft_strlen(s2, 0) + 1, 1)))
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	free(s1);
	str[i + j] = '\0';
	return (str);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*str;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s, 0))
		return (NULL);
	if (!(str = ft_calloc(len + 1, sizeof(char))))
		return (NULL);
	while (s[start] && len)
	{
		str[i] = s[start];
		i++;
		start++;
		len--;
	}
	str[i] = '\0';
	return (str);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*mem;
	size_t	i;
	char	*s;

	i = 0;
	if (!(mem = malloc(count * size)))
		return (NULL);
	s = mem;
	while (i < count * size)
	{
		s[i] = 0;
		i++;
	}
	return (mem);
}

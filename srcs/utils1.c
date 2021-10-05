/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 16:00:15 by charles           #+#    #+#             */
/*   Updated: 2021/10/05 16:00:17 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned char	*src1;
	unsigned char	*src2;

	i = 0;
	src1 = (unsigned char *)s1;
	src2 = (unsigned char *)s2;
	while (src1[i] && src2[i] && i < n)
	{
		if (src1[i] != src2[i])
			return (src1[i] - src2[i]);
		i++;
	}
	if (i < n && ((src1[i] == '\0' && src2[i] != '\0')
			|| (src2[i] == '\0' && src1[i] != '\0')))
		return (src1[i] - src2[i]);
	return (0);
}

char	*ft_strrchr(const char *s, int c)
{
	const char	*str;

	str = s;
	if (!*s)
		return (NULL);
	while (*s++)
		if (*s == (char)c)
			str = s;
	if (*str == (char)c)
		return ((char *)str);
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	unsigned int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	count_word(char *str, char separator)
{
	int	i;
	int	n;

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

int	count_char(char *str, char separator)
{
	int	c;

	c = 0;
	while ((str[c] != separator) && (str[c] != '\0') && (str[c] != '\n'))
		c++;
	return (c);
}

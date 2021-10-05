/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <cbelpois@students.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 18:36:25 by charles           #+#    #+#             */
/*   Updated: 2020/10/12 18:36:29 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;
	int		i;

	str = (char *)s;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (&str[i]);
		i++;
	}
	if (str[i] == c)
		return (&str[i]);
	return (NULL);
}

void	ft_putchar(char c, t_format *s)
{
	write(1, &c, 1);
	s->ret++;
}

void	ft_putstr(char *str, t_format *s)
{
	int i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		s->ret++;
		i++;
	}
}

void	ft_puthex(unsigned long long x, t_format *s, char *base)
{
	if (x == 0 && s->prec != -1)
		ft_putchar('0', s);
	if (x > 0)
	{
		if (x / 16 > 0)
			ft_puthex((x / 16), s, base);
		ft_putchar(base[x % 16], s);
	}
}

void	ft_putnbr(long int n, t_format *s, int len)
{
	long int	nbr;
	char		digit[ft_putnbr_size(n)];
	int			i;

	i = 0;
	nbr = (n > 0 ? n : -n);
	while (nbr > 0)
	{
		digit[i++] = nbr % 10 + '0';
		nbr /= 10;
	}
	if (n < 0)
		digit[i++] = '-';
	if (n == 0)
	{
		if (s->prec == -1)
			return ;
		digit[i++] = '0';
	}
	digit[i] = '\0';
	while (len > 0)
	{
		ft_putchar(digit[--i], s);
		len--;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_alpha.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <cbelpois@students.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 18:44:38 by charles           #+#    #+#             */
/*   Updated: 2020/10/12 18:44:42 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_c(t_format *s)
{
	char	c;

	c = (unsigned char)va_arg(s->arg, int);
	if (s->minus == 1)
	{
		ft_putchar(c, s);
		while (s->width-- > 1)
			ft_putchar(' ', s);
	}
	else
	{
		while (s->width-- > 1)
			ft_putchar(' ', s);
		ft_putchar(c, s);
	}
}

void	print_s_no_width(t_format *s, char *str, int len)
{
	while (len-- > 0)
		ft_putchar(*str++, s);
}

void	print_s_minus(t_format *s, char *str, int len)
{
	print_s_no_width(s, str, len);
	s->width -= len;
	while (s->width-- > 0)
		ft_putchar(' ', s);
}

void	print_s(t_format *s)
{
	char	*str;
	int		len;

	str = (char*)va_arg(s->arg, char*);
	if (str == NULL)
		str = "(null)";
	len = (s->prec < ((int)ft_strlen(str)) && s->prec >= 0 ?
		s->prec : ((int)ft_strlen(str)));
	if (s->width < len)
		print_s_no_width(s, str, len);
	else if (s->minus == 1)
		print_s_minus(s, str, len);
	else
	{
		while (s->width-- > len)
			ft_putchar(' ', s);
		print_s_no_width(s, str, len);
	}
}

void	print_percent(t_format *s)
{
	if (s->minus)
		ft_putchar('%', s);
	while (s->width-- > 1)
		(s->zero && !s->minus ? ft_putchar('0', s) : ft_putchar(' ', s));
	if (!s->minus)
		ft_putchar('%', s);
}

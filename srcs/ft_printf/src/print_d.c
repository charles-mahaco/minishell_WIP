/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 15:59:39 by charles           #+#    #+#             */
/*   Updated: 2020/10/15 15:59:44 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_d_justify_left(int d, t_format *s, int len, int strlen)
{
	if (d < 0)
	{
		s->plus = 0;
		if (d != -2147483648)
		{
			ft_putchar('-', s);
			d *= -1;
		}
		else
			len++;
	}
	else if (s->plus == 1)
		ft_putchar('+', s);
	while (s->prec-- > len)
		ft_putchar('0', s);
	ft_putnbr(d, s, len);
	if (!(d == 0 && s->prec == -1))
		s->width -= strlen;
	while (s->width-- > 0)
		ft_putchar(' ', s);
}

void	print_d_justify_right(int d, t_format *s, int len, int strlen)
{
	if (d < 0 && (s->zero == 1 && s->prec < 0))
	{
		ft_putchar('-', s);
		d *= -1;
	}
	while (s->width-- > strlen)
		(s->zero == 1 && s->prec < 0 ? ft_putchar('0', s) : ft_putchar(' ', s));
	if (d < 0)
	{
		ft_putchar('-', s);
		d *= -1;
	}
	while (s->prec-- > len)
		ft_putchar('0', s);
	(d == 0 && s->width == 0 && s->prec == -1 ? ft_putchar(' ', s) :
												ft_putnbr(d, s, len));
}

void	print_d(t_format *s)
{
	int	d;
	int	len;
	int	strlen;

	d = (int)va_arg(s->arg, int);
	len = ft_putnbr_size(d);
	strlen = ((s->prec > 0 && s->prec > len) ? s->prec : len);
	(d < 0 ? s->width-- : 0);
	if (s->minus == 1 || s->width < strlen)
		print_d_justify_left(d, s, len, strlen);
	else
		print_d_justify_right(d, s, len, strlen);
}

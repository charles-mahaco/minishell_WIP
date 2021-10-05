/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <cbelpois@students.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 18:44:48 by charles           #+#    #+#             */
/*   Updated: 2020/10/12 18:44:51 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_x(t_format *s, char *base)
{
	unsigned int	x;
	int				len[2];

	x = (unsigned int)va_arg(s->arg, unsigned int);
	len[0] = ft_puthex_size(x);
	len[1] = (s->prec > len[0] ? s->prec : len[0]);
	if (s->minus == 1 || s->width < len[1])
	{
		while (s->prec-- > len[0])
			ft_putchar('0', s);
		(x == 0 && s->prec != -1 ? ft_putchar('0', s) : ft_puthex(x, s, base));
		((!(x == 0 && s->prec == -1)) ? s->width -= len[1] : 0);
		while (s->width-- > 0)
			ft_putchar(' ', s);
	}
	else
	{
		while (s->width-- > len[1])
			ft_putchar((s->zero == 1 && s->prec < 0 ? '0' : ' '), s);
		while (s->prec-- > len[0])
			ft_putchar('0', s);
		(x == 0 && s->prec == -1 ? ft_putchar(' ', s) : ft_puthex(x, s, base));
	}
}

void	print_p_justify_left(long long p, t_format *s, int len, int strlen)
{
	ft_putstr("0x", s);
	while (s->prec-- > len)
		ft_putchar('0', s);
	ft_puthex(p, s, "0123456789abcdef");
	s->width -= strlen;
	while (s->width-- > 0)
		ft_putchar(' ', s);
}

void	print_p_null(t_format *s)
{
	(s->minus == 1 && s->prec == 0 ? ft_putstr("0x", s) : 0);
	(s->minus == 1 && s->prec != 0 ? ft_putstr("0x0", s) : 0);
	while (s->width-- > (s->prec == 0 ? 2 : 3))
		ft_putchar(' ', s);
	(s->minus != 1 && s->prec == 0 ? ft_putstr("0x", s) : 0);
	(s->minus != 1 && s->prec != 0 ? ft_putstr("0x0", s) : 0);
}

void	print_p(t_format *s)
{
	long long	p;
	int			len[2];

	p = va_arg(s->arg, unsigned long long);
	len[0] = ft_puthex_size(p);
	len[1] = (s->prec > len[0] ? s->prec + 2 : len[0] + 2);
	if (!p)
		print_p_null(s);
	else if (s->minus == 1 || s->width < len[1])
		print_p_justify_left(p, s, len[0], len[1]);
	else
	{
		((s->zero == 1) ? ft_putstr("0x", s) : 0);
		while (s->width-- > len[1])
			ft_putchar((s->zero == 1 && s->prec < 0 ? '0' : ' '), s);
		((s->zero == 0) ? ft_putstr("0x", s) : 0);
		while (s->prec-- > len[0])
			ft_putchar('0', s);
		ft_puthex(p, s, "0123456789abcdef");
	}
}

void	print_u(t_format *s)
{
	long int	u;
	int			len[2];

	u = va_arg(s->arg, unsigned int);
	(u < 0 ? u += 4294967296 : u);
	len[0] = (ft_putnbr_size(u));
	len[1] = ((s->prec > 0 && s->prec > len[0]) ? s->prec : len[0]);
	if (s->minus == 1 || s->width < len[1])
	{
		while (s->prec-- > len[0])
			ft_putchar('0', s);
		ft_putnbr(u, s, len[0]);
		if (!(u == 0 && s->prec == -1))
			s->width -= len[1];
		while (s->width-- > 0)
			ft_putchar(' ', s);
	}
	else
	{
		while (s->width-- > len[1])
			ft_putchar((s->zero == 1 && s->prec < 0 ? '0' : ' '), s);
		while (s->prec-- > len[0])
			ft_putchar('0', s);
		u == 0 && s->prec == -1 ? ft_putchar(' ', s) : ft_putnbr(u, s, len[0]);
	}
}

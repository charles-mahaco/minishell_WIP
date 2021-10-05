/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <cbelpois@students.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 18:44:25 by charles           #+#    #+#             */
/*   Updated: 2020/10/12 18:44:29 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	check_types(char *fmt, int i, t_format *s)
{
	if (fmt[i] == 'c')
		print_c(s);
	else if (fmt[i] == 's')
		print_s(s);
	else if (fmt[i] == 'p')
		print_p(s);
	else if (fmt[i] == 'd' || fmt[i] == 'i')
		print_d(s);
	else if (fmt[i] == 'u')
		print_u(s);
	else if (fmt[i] == 'x' || fmt[i] == 'X')
		print_x(s, (fmt[i] == 'x') ? "0123456789abcdef" : "0123456789ABCDEF");
	else if (fmt[i] == '%')
		print_percent(s);
}

void	flag_check(t_format *s, char *fmt, int *i)
{
	if (fmt[*i] == '0' && s->zero == 0)
	{
		s->zero = 1;
		(*i)++;
	}
	else if (fmt[*i] == '-')
	{
		s->minus = 1;
		(*i)++;
	}
}

void	width_check(t_format *s, char *fmt, int *i)
{
	while (ft_strchr("0123456789", fmt[*i]))
	{
		s->width = (s->width * 10) + (fmt[*i] - '0');
		(*i)++;
	}
}

void	prec_check(t_format *s, char *fmt, int *i)
{
	if (fmt[*i] == '.')
	{
		(*i)++;
		s->prec = 0;
		if (fmt[*i] == '*')
		{
			s->prec = va_arg(s->arg, int);
			(*i)++;
		}
		while (ft_strchr("0123456789", fmt[*i]))
		{
			s->prec = (s->prec * 10) + (fmt[*i] - '0');
			(*i)++;
		}
	}
}

void	parsing(t_format *s, char *fmt, int *i)
{
	while (!ft_strchr("cspdiuxX%", fmt[*i]) && fmt[*i])
	{
		if (!ft_strchr(".-*0123456789", fmt[*i]) && fmt[*i])
			return ;
		if (fmt[*i] == '*')
		{
			s->width = va_arg(s->arg, int);
			if (s->width < 0)
			{
				s->minus = 1;
				s->width *= -1;
			}
			(*i)++;
		}
		flag_check(s, fmt, i);
		width_check(s, fmt, i);
		prec_check(s, fmt, i);
	}
}

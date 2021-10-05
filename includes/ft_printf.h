/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <cbelpois@students.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 18:30:22 by charles           #+#    #+#             */
/*   Updated: 2020/10/12 18:30:26 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <stdio.h>
# include "minishell.h"

typedef struct	s_format
{
	va_list		arg;
	int			zero;
	int			minus;
	int			plus;
	int			width;
	int			prec;
	int			ret;
}				t_format;

char			*ft_strchr(const char *s, int c);
void			ft_putchar(char c, t_format *s);
void			ft_putstr(char *str, t_format *s);
int				ft_putnbr_size(long int n);
void			ft_putnbr(long int n, t_format *s, int len);
void			ft_puthex(unsigned long long x, t_format *s, char *base);
int				ft_puthex_size(unsigned long long x);
void			print_x(t_format *s, char *base);
void			print_p(t_format *s);
void			print_p_justify_left(long long int p, t_format *s,
									int len, int strlen);
void			print_p_null(t_format *s);
void			print_u(t_format *s);
void			print_d(t_format *s);
void			print_d_justify_left(int d, t_format *s, int len, int strlen);
void			print_d_justify_right(int d, t_format *s, int len, int strlen);
void			print_c(t_format *s);
void			print_s_no_width(t_format *s, char *str, int len);
void			print_s_minus(t_format *s, char *str, int len);
void			print_s(t_format *s);
void			print_percent(t_format *s);
void			initializer(t_format *s);
void			check_types(char *fmt, int i, t_format *s);
void			flag_check(t_format *s, char *fmt, int *i);
void			width_check(t_format *s, char *fmt, int *i);
void			prec_check(t_format *s, char *fmt, int *i);
void			parsing(t_format *s, char *fmt, int *i);
void			ft_read(char *fmt, t_format *s);
int				ft_printf(const char *format, ...);

#endif

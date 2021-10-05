/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_int.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <cbelpois@students.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 18:37:13 by charles           #+#    #+#             */
/*   Updated: 2020/10/12 18:37:20 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_putnbr_size(long int n)
{
	long int	nbr;
	int			len;

	len = 0;
	nbr = n;
	if (nbr < 0)
		nbr *= -1;
	while (nbr > 0)
	{
		nbr /= 10;
		len++;
	}
	if (n == 0)
		len++;
	return (len);
}

int		ft_puthex_size(unsigned long long x)
{
	int len;

	len = 0;
	if (x == 0)
		return (1);
	while (x > 0)
	{
		x /= 16;
		len++;
	}
	return (len);
}

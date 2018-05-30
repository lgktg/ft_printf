/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_hexa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 21:14:58 by tgelu             #+#    #+#             */
/*   Updated: 2018/05/30 21:26:42 by tgelu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

static int         int_len(uintmax_t c, t_printf *pf)
{
	int     len;

	len = 0;
	if (c == 0 && pf->prec != 0)
		return (1);
	while (c != 0)
	{
		len++;
		c /= 10;
	}
	return (len);
}

static void        print_left_hexa(t_printf *pf, int len, uintmax_t value, char *base)
{
}

static void        print_right_hexa(t_printf *pf, int len, uintmax_t value, char *base)
{
}


void        print_hexa(t_printf *pf, uintmax_t value)
{
	int     i;
	int     offset;
	int     len;
	int     tmpprec;
	char	base[16];

	if (pf->identifier == 'x')
		ft_strcpy(base, "0123456789abcdef");
	else
		ft_strcpy(base, "0123456789ABCDEF");
	len = int_len(value, pf);
	i = 0;
	if (pf->attr & 4)
		print_left_hexa(pf, len, value, base);
	else
		print_right_hexa(pf, len, value, base);
}

void		process_hexa(t_printf *pf)
{
	pf->sign = '+';
	if (pf->identifier == 'X')
		pf->convmod |= 1 << 4;
	if (pf->convmod & 4)
		print_hexa(pf, va_arg(pf->args, uintmax_t));
	else if (pf->convmod & 32)
		print_hexa(pf, va_arg(pf->args, unsigned long long));
	else if (pf->convmod & 16)
		print_hexa(pf, va_arg(pf->args, unsigned long));
	else if (pf->convmod & 8)
		print_hexa(pf, va_arg(pf->args, size_t));
	else if (pf->convmod & 2)
		print_hexa(pf, (unsigned char)va_arg(pf->args, unsigned int));
	else if (pf->convmod & 1)
		print_hexa(pf, (unsigned short)va_arg(pf->args, unsigned int));
	else if (pf->convmod == 0)
		print_hexa(pf, va_arg(pf->args, unsigned int));
}

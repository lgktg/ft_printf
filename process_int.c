/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 12:31:37 by tgelu             #+#    #+#             */
/*   Updated: 2018/05/16 22:52:05 by tgelu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			int_len(intmax_t c)
{
	int		len;

	len = 0;
	while (c != 0)
	{
		len++;
		c /= 10;
	}
	return (len);
}

void		print_left_int(t_printf *pf, int len, intmax_t value)
{
	int		i;

	i = -1;
	if (pf->attr & 16)
	{
		buffer_add_char(pf, pf->sign);
		while (++i < pf->prec - len)
			buffer_add_char(pf, '0');
		ft_itoa_base(value, "0123456789", pf);
		while (++i < pf->width - len)
			buffer_add_char(pf, ' ');
	}
	else
	{
		if (pf->sign == '-')
			buffer_add_char(pf, '-');
		else if (pf->attr & 8)
			buffer_add_char(pf, ' ');
		while (++i < pf->prec - len)
			buffer_add_char(pf, '0');
		ft_itoa_base(value, "0123456789", pf);
		while (++i < pf->width - len + (!(pf->attr & 8) && !(pf->sign == '-')))
			buffer_add_char(pf, ' ');
	}
}

void		print_int(t_printf *pf, int len, intmax_t value)
{
	int		i;

	pf->sign = (value < 0) ? '-' : '+';
	value = (value < 0) ? -value : value;
	i = -1;
	if (pf->attr & 4)
		print_left_int(pf, len, value);
	else
	{
		pf->prec = (pf->prec == 0 && pf->attr & 2) ? pf->width : pf->prec;
		while (++i < pf->width - pf->prec - len - (pf->sign == '-'))
			buffer_add_char(pf, ' ');
		if (pf->sign == '-' || pf->attr & 16)
			buffer_add_char(pf, pf->sign);
		while (pf->prec != 0 &&++i < pf->width - len)
			buffer_add_char(pf, '0');
		ft_itoa_base(value, "0123456789", pf);
	}
}

void		process_int(t_printf *pf)
{
	intmax_t	ret;
	int			len;

	ret = 0;
	if (pf->convmod & 4)
		ret = va_arg(pf->args, intmax_t);
	else if (pf->convmod & 32)
		ret = va_arg(pf->args, long long int);
	else if (pf->convmod & 16)
		ret = va_arg(pf->args, long int);
	else if (pf->convmod & 8)
		ret = va_arg(pf->args, size_t);
	else if (pf->convmod & 2)
		ret = va_arg(pf->args, int);
	else if (pf->convmod & 1)
		ret = va_arg(pf->args, int);
	else if (pf->convmod == 0)
		ret = va_arg(pf->args, int);
	len = int_len(ret);
	print_int(pf, len, ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 12:31:37 by tgelu             #+#    #+#             */
/*   Updated: 2018/05/23 17:29:48 by tgelu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

int			int_len(intmax_t c, t_printf *pf)
{
	int		len;

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

void		print_int(t_printf *pf, intmax_t value)
{
	int		i;
	int		offset;
	int		len;
	int		tmpprec;

	//printf("prec:%d\n", pf->prec);
	tmpprec = (pf->prec == -1) ? 0 : pf->prec;
	len = int_len(value, pf);
	pf->sign = (value < 0) ? '-' : '+';
	offset = (pf->attr & 16 || pf->sign == '-');
	value = (value < 0) ? -value : value;
	i = 0;
	if (pf->attr & 4)
		print_left_int(pf, len, value);
	else
	{
		if (offset && (pf->attr & 2) && pf->prec == -1)
			buffer_add_char(pf, pf->sign);
		else if (pf->attr & 8 && !(pf->attr & 16) && pf->width != 0 && !tmpprec)
			buffer_add_char(pf, ' ');
		while (i < pf->width - tmpprec - (offset || pf->attr & 8) && i < pf->width - len - (offset || pf->attr & 8))
		{
			buffer_add_char(pf, ((pf->attr & 2 && pf->prec == -1) ? '0' : ' '));
			i++;
		}
		if ((offset || (pf->attr & 8)) && (!(pf->attr & 2) || pf->prec != -1))
			buffer_add_char(pf, (offset ? pf->sign : ' '));
		i = 0;
		while (i < tmpprec - len)
		{
			buffer_add_char(pf, '0');
			i++;
		}
		ft_itoa_base(value, "0123456789", pf);
	}
}

void		process_int(t_printf *pf)
{
	void		*ret;
	int			len;

	ret = 0;
	len = 0;
	if (pf->convmod & 4)
		print_int(pf, va_arg(pf->args, intmax_t));
	else if (pf->convmod & 32)
		print_int(pf, va_arg(pf->args, long long));
	else if (pf->convmod & 16)
		print_int(pf, va_arg(pf->args, long));
	else if (pf->convmod & 8)
		print_int(pf, va_arg(pf->args, size_t));
	else if (pf->convmod & 2)
		print_int(pf, (char)va_arg(pf->args, int));
	else if (pf->convmod & 1)
		print_int(pf, (short)va_arg(pf->args, int));
	else if (pf->convmod == 0)
		print_int(pf, va_arg(pf->args, int));
}

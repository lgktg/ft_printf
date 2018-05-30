/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_octal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 14:11:07 by tgelu             #+#    #+#             */
/*   Updated: 2018/05/30 21:00:41 by tgelu            ###   ########.fr       */
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
		c /= 8;
	}
	return (len);
}

static void	print_right_spaces(t_printf *pf, int len, int *i)
{
	if (pf->attr & 4)
	{
		while (*i < pf->width)

		{
			buffer_add_char(pf, ' ');
			(*i)++;
		}
	}
}

static void	print_left_spaces(t_printf *pf, int len, int *i)
{
	if (pf->attr & 4)
	{
		while (*i < pf->prec - len)
		{
			buffer_add_char(pf, '0');
			(*i)++;
		}
	}
	else
	{
		while (*i < pf->width - len - (pf->attr & 1) || *i < pf->prec - len - (pf->attr & 1))
		{
			buffer_add_char(pf, ((pf->attr & 2 && pf->prec == -1) || pf->width == 0) ? '0' : ' ');
			(*i)++;
		}
	}
}

void	print_octal_zero(t_printf *pf)
{
	int		offset;
	int		i;

	i = 0;
	offset = (pf->attr & 1);
	if (!offset && pf->width == 0 && pf->prec == 0)
		return ;
	if (pf->attr & 4)
	{
		while (pf->width != 0 && i < pf->width)
		{
			if (i < pf->prec)
				buffer_add_char(pf, '0');
			else
				buffer_add_char(pf, ' ');
			i++;
		}
	}
	else
	{
		while (i < pf->width - 1 || i < pf->prec - 1)
		{
			if ((pf->prec <= 0 || i < pf->prec) && pf->width != 0
					&& (pf->width > pf->prec) && (!(pf->attr & 2) || pf->prec > 0))
				buffer_add_char(pf, ' ');
			else
				buffer_add_char(pf, '0');
			i++;
		}
		buffer_add_char(pf, (pf->prec == 0 && pf->width > 0) ? ' ' : '0');
	}
}

void	print_octal(t_printf *pf, uintmax_t value)
{
	int		len;
	int		i;
	int		offset;

	if (value == 0)
	{
		print_octal_zero(pf);
		return ;
	}
	i = 0;
	len = int_len(value, pf);
	offset = pf->attr & 1;
	print_left_spaces(pf, len, &i);
	if (offset)
	{
		buffer_add_char(pf, '0');
		i++;
	}
	ft_itoa_base_buff(value, "01234567", pf);
	i += len;
	print_right_spaces(pf, len, &i);
}

void	process_octal(t_printf *pf)
{
	print_octal(pf, va_arg(pf->args, uintmax_t));
}

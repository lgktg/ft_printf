/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 17:44:20 by tgelu             #+#    #+#             */
/*   Updated: 2018/05/26 19:48:54 by tgelu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

void	print_char_left(t_printf *pf, wchar_t value)
{
	int		i;

	i = 0;
	buffer_add_char(pf, value);
	while (i < pf->width - 1)
	{
		buffer_add_char(pf, (pf->attr & 2 ? '0' : ' '));
		i++;
	}
}

void	print_char_right(t_printf *pf, wchar_t value)
{
	int		i;
	
	i = 0;
	while (i < pf->width - 1)
	{
		buffer_add_char(pf, (pf->attr & 2 ? '0' : ' '));
		i++;
	}
	buffer_add_char(pf, value);
}

void	print_char(t_printf *pf, wchar_t value)
{
	int		tmpprec;

	tmpprec = (pf->prec == -1) ? 0 : pf->prec;
	if (pf->attr & 4)
		print_char_left(pf, value);
	else
		print_char_right(pf, value);
}

void	process_char(t_printf *pf)
{
	void	*ret;

	if (pf->identifier == '%')
		print_char(pf, '%');
	else if (pf->convmod & 16)
		print_char(pf, va_arg(pf->args, wchar_t));
	else
		print_char(pf, (char)va_arg(pf->args, wchar_t));
}

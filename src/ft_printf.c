/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 14:04:15 by tgelu             #+#    #+#             */
/*   Updated: 2018/05/29 17:19:55 by tgelu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"
#include <locale.h>

void	process_arg(t_printf *pf)
{
	if (pf->identifier == 'd' || pf->identifier == 'i')
		process_int(pf);
	else if (pf->identifier == 'D')
		process_large_int(pf);
	else if (pf->identifier == 'c' || pf->identifier == 'C' || pf->identifier == '%')
		process_char(pf);
	else if (pf->identifier == 's' || pf->identifier == 'S')
		process_string(pf);
}

int		ft_printf(const char *format, ...)
{
	t_printf	pf;
	int			count;

	setlocale(LC_ALL, "");
	ft_bzero(pf.buff, BUFF_SIZE);
	pf.buff_size = 0;
	pf.total = 0;
	pf.err = 0;
	va_start(pf.args, format);
	count = parse_args(&pf, format);
	if (pf.buff_size != 0 && pf.err == 0)
	{
		pf.total += pf.buff_size;
		write(1, pf.buff, pf.buff_size);
	}
	if (pf.err == 1)
		return (-1);
	return (pf.total);

}

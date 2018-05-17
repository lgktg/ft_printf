/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 14:04:15 by tgelu             #+#    #+#             */
/*   Updated: 2018/05/17 17:22:05 by tgelu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

void	process_arg(t_printf *pf)
{
	if (pf->identifier == 'd' || pf->identifier == 'i')
		process_int(pf);
}

int		ft_printf(const char *format, ...)
{
	t_printf	pf;
	int			count;

	ft_bzero(pf.buff, BUFF_SIZE);
	pf.buff_size = 0;
	va_start(pf.args, format);
	count = parse_args(&pf, format);
	if (pf.buff_size != 0)
		write(1, pf.buff, pf.buff_size);
	return (0);

}

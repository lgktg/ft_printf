/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_int.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 13:56:16 by tgelu             #+#    #+#             */
/*   Updated: 2018/05/26 19:17:58 by tgelu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

void	ft_itoa_base_buff(uintmax_t num, char *base, t_printf *pf)
{
	intmax_t		base_s;
	intmax_t		cpt;
	uintmax_t		numcp;
	char			tmp[50];
	int				i;

	i = -1;
	ft_bzero(tmp, 50);
	base_s = ft_strlen(base);
	cpt = 0;
	numcp = num;
	if (num == 0 && pf->prec != 0)
	{
		buffer_add_char(pf, '0');
		return ;
	}
	while (numcp > 0)
	{
		numcp /= base_s;
		cpt++;
	}
	while (cpt > 0)
	{
		tmp[cpt - 1] = base[(num % base_s)];
		cpt--;
		num /= base_s;
	}
	while (tmp[++i])
		buffer_add_char(pf, tmp[i]);
}

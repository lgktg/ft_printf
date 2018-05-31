/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_pointer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 19:23:15 by tgelu             #+#    #+#             */
/*   Updated: 2018/05/31 19:27:55 by tgelu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

void		process_pointer(t_printf *pf)
{
	pf->attr |= 1;
	pf->convmod |= 1 << 4;
	process_hexa(pf);
}

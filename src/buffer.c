/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 17:11:06 by tgelu             #+#    #+#             */
/*   Updated: 2018/05/17 17:43:51 by tgelu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

void    buffer_add_char(t_printf *pf, char c)
{
	if (pf->buff_size + 2 > BUFF_SIZE)
	{
		write(1, pf->buff, pf->buff_size);
		ft_bzero(pf->buff, BUFF_SIZE);
		pf->total += pf->buff_size;
		pf->buff_size = 0;
		buffer_add_char(pf, c);
	}
	else
	{
		pf->buff[pf->buff_size] = c;
		pf->buff_size += 1;
	}
}

void	buffer_add_string(t_printf *pf, char *str)
{
	int		len;
	int		i;

	len = ft_strlen(str);
	if (pf->buff_size + len > BUFF_SIZE)
	{
		write(1, pf->buff, pf->buff_size);
		pf->buff_size = 0;
		ft_bzero(pf->buff, BUFF_SIZE);
		buffer_add_string(pf, str);
	}
	else
	{
		i = 0;
		while (i < len)
		{
			pf->buff[pf->buff_size + i] = str[i];
			i++;
		}
		pf->buff_size += i;
	}
}

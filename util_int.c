/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_int.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 13:56:16 by tgelu             #+#    #+#             */
/*   Updated: 2018/05/16 22:20:42 by tgelu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strrev(char *str)
{
	int		len;
	char	t;
	int		i;

	i = 0;
	len = ft_strlen(str) - 1;
	while (i <= len)
	{
		t = str[i];
		str[i] = str[len];
		str[len] = t;
		i++;
		len--;
	}
	return (str);
}

void	ft_itoa_base(intmax_t num, char *base, t_printf *pf)
{
	intmax_t		base_s;
	intmax_t		cpt;
	intmax_t		numcp;
	char			tmp[50];
	int				i;

	i = -1;
	ft_bzero(tmp, 50);
	base_s = ft_strlen(base);
	cpt = 0;
	numcp = num;
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

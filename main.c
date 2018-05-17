/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 14:03:59 by tgelu             #+#    #+#             */
/*   Updated: 2018/05/16 22:54:57 by tgelu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stddef.h>
#include <stdint.h>

int		main(void)
{
	ft_printf("my :hello %zd\n", (size_t)SIZE_MAX);
	printf("heu:hello %zd\n", (size_t)SIZE_MAX);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 14:03:59 by tgelu             #+#    #+#             */
/*   Updated: 2018/05/17 17:23:54 by tgelu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/ft_printf.h"
#include <stddef.h>
#include <stdint.h>

int		main(void)
{
	ft_printf("my :hello %hhi\n", (char)42);
	printf("heu:hello %hhi\n", (char)42);
	return (0);
}

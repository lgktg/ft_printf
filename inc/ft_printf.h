/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 15:36:32 by tgelu             #+#    #+#             */
/*   Updated: 2018/05/17 17:23:28 by tgelu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>
# include "../lib/libft.h"
# define BUFF_SIZE 5
# define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
# define BYTE_TO_BINARY(byte)  \
	(byte & 0x80 ? '1' : '0'), \
	(byte & 0x40 ? '1' : '0'), \
	(byte & 0x20 ? '1' : '0'), \
	(byte & 0x10 ? '1' : '0'), \
	(byte & 0x08 ? '1' : '0'), \
	(byte & 0x04 ? '1' : '0'), \
	(byte & 0x02 ? '1' : '0'), \
	(byte & 0x01 ? '1' : '0')
# define BASE "ABCDEF0123456789"


typedef struct		s_printf
{
	va_list			args;
	char			buff[BUFF_SIZE];
	int				buff_size;
	int				width;
	int				prec;
	int				identifier;
	int				attr; // #0- +	
	int				convmod;
	char			sign;
}					t_printf;

int		ft_printf(const char *format, ...);
int		parse_args(t_printf *pf, const char *format);
void	process_arg(t_printf *pf);
void	process_int(t_printf *pf);
void    buffer_add_string(t_printf *pf, char *str);
void	buffer_add_char(t_printf *pf, char c);
void    ft_itoa_base(intmax_t num, char *base, t_printf *pf);
#endif

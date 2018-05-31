/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/13 16:35:26 by tgelu             #+#    #+#             */
/*   Updated: 2018/05/31 21:12:51 by tgelu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

int		is_identifier(char c)
{
	if (c == 'd' || c == 'D' || c == 's' || c == 'S'
			|| c == 'p' || c == 'i' || c == 'o' || c == 'O'
			|| c == 'u' || c == 'U' || c == 'x' || c == 'X'
			|| c == 'c' || c == 'C' || c == '%')
		return (1);
	return (0);
}

int		is_attribute(char c)
{
	if (c == '#' || c == '0' || c == '-' || c == ' ' || c == '+')
		return (1);
	return (0);
}

void	get_attribute(t_printf *pf, const char *format)
{
	while (is_attribute(*format))
	{
		if (*format == '#')
			pf->attr |= 1;
		if (*format == '0' && !ft_isdigit(*(format - 1)))
			pf->attr |= 1 << 1;
		if (*format == '-')
			pf->attr |= 1 << 2;
		if (*format == ' ')
			pf->attr |= 1 << 3;
		if (*format == '+')
			pf->attr |= 1 << 4;
		format++;
	}
}

void	set_conv_modifier(t_printf *pf, const char *format)
{
	if (*format == 'h')
	{
		if (*(format + 1) == 'h')
			pf->convmod |= 1 << 1;
		else if (!(*(format + 1) == 'h'))
			pf->convmod |= 1;
	}
	if (*format == 'l')
	{
		if (*(format + 1) == 'l')
			pf->convmod |= 1 << 5;
		else if (!(*(format + 1) == 'h'))
			pf->convmod |= 1 << 4;
	}
	if (*format == 'j')
		pf->convmod |= 1 << 2;
	if (*format == 'z')
		pf->convmod |= 1 << 3;
}

int		is_conv_modifier(const char *format)
{
	if (*format == 'h')
	{
		if (*(format - 1) == 'h')
			return (0);
		return (1);
	}
	if (*format == 'l')
	{
		if (*(format - 1) == 'l')
			return (0);
		return (1);
	}
	if (*format == 'j' || *format == 'z')
		return (1);
	return (0);
}

void	set_width(t_printf *pf, const char *format, int *i)
{
	if (*(format + *i) != '*')
	{
		pf->width = ft_atoi(format + *i);
	}
	else if (*(format + *i) == '*')
		pf->width = va_arg(pf->args, int);
	while (ft_isdigit(*(format + *i)))
		(*i)++;
	(*i)--;
}

void	set_prec(t_printf *pf, const char *format, int *i)
{
	if (*(format + *i + 1) != '*')
		pf->prec = ft_atoi(format + *i + 1);
	else
		pf->prec = va_arg(pf->args, int);
	while (ft_isdigit(*(format + *i + 1)))
		(*i)++;
}

void	init_pf(t_printf *pf, int *len)
{
	pf->width = 0;
	pf->prec = -1;
	pf->attr = 0;
	pf->convmod = 0;
	*len = 0;
}

int		parse_simple_arg(t_printf *pf, const char *format)
{
	int		len;
	int		i;

	i = -1;
	init_pf(pf, &len);
	while (format[++i])
	{
		if (is_attribute(format[i]))
			get_attribute(pf, format);
		if (!pf->width && ((ft_isdigit(format[i]) && format[i] != '0')
					|| (format[i] == '*')) && format[i - 1] != '.')
			set_width(pf, format, &i);
		if (format[i] == '.')
			set_prec(pf, format, &i);
		if (is_conv_modifier(format + i))
			set_conv_modifier(pf, format + i);
		if (is_identifier(format[i]))
		{
			pf->identifier = format[i];
			break ;
		}
		len++;
	}
	process_arg(pf);
	return (len);
}

int		parse_args(t_printf *pf, const char *format)
{
	int		len;
	int		i;
	int		tmp;

	i = 0;
	len = 0;
	while (pf->err == 0 && format[i])
	{
		if (format[i] == '%')
		{
			i++;
			tmp = parse_simple_arg(pf, format + i);
			while (!is_identifier(format[i]))
				i++;
			i++;
			len += tmp;
		}
		else
		{
			buffer_add_char(pf, format[i]);
			len++;
			i++;
		}
	}
	return (len);
}

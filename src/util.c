/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgelu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 17:29:00 by tgelu             #+#    #+#             */
/*   Updated: 2018/05/31 21:40:51 by tgelu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

static char	*ft_strrev(char *str)
{
	int		i;
	int		l;
	char	temp;

	i = 0;
	l = ft_strlen(str);
	while (i < (l / 2))
	{
		temp = str[i];
		str[i] = str[l - i - 1];
		str[l - i - 1] = temp;
		i++;
	}
	str[l] = '\0';
	return (str);
}

int			ft_atoi_base(char *str, char *base)
{
	long int i;
	long int c;
	long int final;
	long int sign;

	sign = 1;
	i = 0;
	final = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] != '\0' && str[i] != '+' && str[i] != '-')
	{
		c = 0;
		while (base[c] != str[i])
			c++;
		final = (final * ft_strlen(base)) + c;
		i++;
	}
	return (final);
}

char		*ft_itoa_base(int num, char *base)
{
	long int		base_s;
	long int		i;
	long int		cpt;
	char			*str;
	long int		numcp;

	base_s = ft_strlen(base);
	i = -1;
	cpt = 0;
	numcp = num;
	while (numcp > 0)
	{
		numcp /= base_s;
		cpt++;
	}
	if (!(str = malloc(sizeof(*str) * cpt + 2)))
		return (NULL);
	str[cpt] = '\0';
	while (++i < cpt)
	{
		str[i] = base[(num % base_s)];
		num /= base_s;
	}
	return (ft_strrev(str));
}

char		*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	long int		conversion;
	char			*final;
	long int		i;

	conversion = ft_atoi_base(nbr, base_from);
	if (conversion < 0)
	{
		final = ft_itoa_base(-conversion, base_to);
		i = ft_strlen(final);
		while (i >= 0)
		{
			final[i + 1] = final[i];
			i--;
		}
		final[0] = '-';
		return (final);
	}
	else if (conversion == 0)
		return ("0");
	else
	{
		final = ft_itoa_base(conversion, base_to);
		return (final);
	}
}

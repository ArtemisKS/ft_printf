/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/26 20:51:06 by akupriia          #+#    #+#             */
/*   Updated: 2017/12/26 20:51:07 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		parse_format(va_list ap, char *fmt)
{
	int		i;
	int		j;
	t_spec	*ts;

	i = 0;
	j = 0;
	ts = (t_spec *)malloc(sizeof(t_spec));
	while (fmt[i])
	{
		if (fmt[i] == '%' && fmt[i + 1])
		{
			i++;
			i += parse_spec(&fmt[i], ts, ap);
			j = output_fstring(ap, fmt[i], j, ts);
		}
		else if (fmt[i] != '%')
		{
			write(1, &fmt[i], 1);
			j++;
		}
		i++;
	}
	ft_memdel((void**)&ts);
	return (j);
}

int		ft_printf(char *fmt, ...)
{
	va_list	ap;
	int		n;

	va_start(ap, fmt);
	n = parse_format(ap, fmt);
	va_end(ap);
	return (n);
}

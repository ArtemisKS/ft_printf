/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_double.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 13:51:39 by akupriia          #+#    #+#             */
/*   Updated: 2018/12/04 13:51:40 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

/*
** bonuses done :
**   1) *   wildcard_length_modifier
**   2) n   print_len (refer to ft_printf.c : *va_arg(ap, int *) = p->len;)
**   3) m   ft_printf_putstr(strerror(errno), p)
**   4) {}  color
**   5) fF  ldtoa
*/

static double	ft_dabs(double n)
{
	return (n < 0 ? -n : n);
}

/*
** bonus function that handles float
** calculates the size of what should be sent to the buffer
** the decimals are calculated with p->precision
** decimal is first calculated as the right part, then we multiply it by
** 10 power p->precision + 1 in order to get the rounding.
*/

static void		ldtoa_fill(double n, t_global *p, long value, int b)
{
	int		len;
	char	s[48];

	p->c = 'a' - 10 - ((p->f & UPPERC_FL) >> 1);
	len = p->len_tobuf - 1 - p->precision;
	while (p->precision--)
	{
		s[len + p->precision + 1] = value % b + ((value % b < 10) ? '0' : p->c);
		value /= b;
	}
	s[len] = '.';
	value = (long)(n < 0 ? -n : n);
	while (++p->precision < len)
	{
		s[len - p->precision - 1] = value % b + ((value % b < 10) ? '0' : p->c);
		value /= b;
	}
	(p->f & PREC_FL && p->f & NIL_FL) ? s[0] = ' ' : 0;
	(p->f & SP_FL) ? s[0] = ' ' : 0;
	(n < 0) ? s[0] = '-' : 0;
	(p->f & PL_FL && n >= 0) ? s[0] = '+' : 0;
	if (b == 16 && (p->len += 2))
		buffer(p, "0x", 2);
	buffer(p, s, p->len_tobuf);
}

void			pf_putdouble(t_global *p, int base)
{
	double		n;
	long		tmp;
	int			len;
	double		decimal;
	long		value;

	len = 1;
	n = (double)va_arg(p->ap, double);
	(p->f & NIL_FL) ? p->precision = p->len_min : 0;
	if (!(p->f & PREC_FL))
		p->precision = 6 + base - 10;
	tmp = (long)(n < 0 ? -n : n);
	while (tmp && ++len)
		tmp /= base;
	p->len_tobuf = p->precision + len + ((n < 0) ? 1 : 0);
	decimal = ft_dabs(n);
	decimal = (decimal - (long)(ft_dabs(n))) * ft_pow(base, p->precision + 1);
	decimal = ((long)decimal % base > 4) ? decimal / base + 1 : decimal / base;
	value = (long)decimal;
	ldtoa_fill(n, p, value, base);
}

void			buffer(t_global *p, void *new, size_t size)
{
	long		new_i;
	int			diff;

	new_i = 0;
	while (PF_BUF_SIZE - p->buf_ind < size)
	{
		diff = PF_BUF_SIZE - p->buf_ind;
		ft_memcpy(&(p->buff[p->buf_ind]), &(new[new_i]), diff);
		size -= diff;
		new_i += diff;
		p->buf_ind += diff;
		p->len += diff;
		write(p->fd, p->buff, p->buf_ind);
		p->buf_ind = 0;
	}
	ft_memcpy(&(p->buff[p->buf_ind]), &(new[new_i]), size);
	p->buf_ind += size;
	p->len += size;
}

/*
** 32 is ascii for space and 48 for 0, flag 0 is 16 bits if set.
*/

void			padding(t_global *p, int n)
{
	if (p->padding)
	{
		p->c = 32 | (p->f & NIL_FL);
		if (!n && !(p->f & MIN_FL))
			while (p->padding--)
				buffer(p, &p->c, 1);
		else if (n && (p->f & MIN_FL))
			while (p->padding--)
				buffer(p, &p->c, 1);
	}
}

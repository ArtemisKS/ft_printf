/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_num.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 13:51:44 by akupriia          #+#    #+#             */
/*   Updated: 2018/12/04 13:51:45 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

void		pf_putnb(t_global *p)
{
	intmax_t	n;

	if (p->f & L_FL || p->f & L_FL2)
		n = (p->f & L_FL2) ? ((intmax_t)va_arg(p->ap, long long)) :
			((intmax_t)va_arg(p->ap, long));
	else if (p->f & SH_FL || p->f & SH_FL2)
		n = (p->f & SH_FL2) ? (intmax_t)((char)va_arg(p->ap, int)) :
			(intmax_t)((short)va_arg(p->ap, int));
	else if (p->f & IMAX_FL)
		n = (va_arg(p->ap, intmax_t));
	else if (p->f & SIZET_FL)
		n = ((intmax_t)va_arg(p->ap, ssize_t));
	else
		n = ((intmax_t)va_arg(p->ap, int));
	(p->f & NIL_FL) ? p->precision = p->len_min : 0;
	itoa_printf(n, p, 0);
}

void		pf_putnb_base(int base, t_global *p)
{
	uintmax_t	n;

	if (p->f & L_FL || p->f & L_FL2)
		n = (p->f & L_FL2) ? ((intmax_t)va_arg(p->ap, unsigned long long)) :
			((intmax_t)va_arg(p->ap, unsigned long));
	else if (p->f & SH_FL || p->f & SH_FL2)
		n = (p->f & SH_FL2) ? (uintmax_t)((unsigned char)va_arg(p->ap, int))
			: (uintmax_t)((unsigned short)va_arg(p->ap, int));
	else if (p->f & IMAX_FL)
		n = (va_arg(p->ap, uintmax_t));
	else if (p->f & SIZET_FL)
		n = ((uintmax_t)va_arg(p->ap, size_t));
	else
		n = (uintmax_t)va_arg(p->ap, unsigned int);
	itoa_base_printf(n, base, p);
}

static void	itoa_base_fill(uintmax_t tmp, int b, char s[PF_BUF_SIZE],
	t_global *p)
{
	int		len;

	if (tmp && !(p->f & POINT_FL) && (p->f & NIL_FL) && (p->f & HASH_FL) &&
	b == 16 && !(p->f & L_FL2) && p->len_tobuf > 3)
		p->len_tobuf -= 2;
	len = p->len_tobuf;
	p->c = 'a' - 10 - ((p->f & UPPERC_FL) >> 1);
	while (len--)
	{
		s[len] = tmp % b + ((tmp % b < 10) ? '0' : p->c);
		tmp /= b;
	}
	(p->f & PREC_FL && p->f & NIL_FL) ? s[0] = ' ' : 0;
}

void		itoa_printf(intmax_t n, t_global *p, int len)
{
	char		s[21];
	uintmax_t	tmp;

	tmp = n < 0 ? -n : n;
	while (tmp)
	{
		tmp /= 10;
		++len;
	}
	if ((n < 0 || p->f & PL_FL || p->f & SP_FL) && p->f & NIL_FL)
		--p->precision;
	p->len_tobuf = MAX(len, p->precision);
	if (n < 0 || p->f & PL_FL || p->f & SP_FL)
		++p->len_tobuf;
	p->padding = (p->len_tobuf > p->len_min) ? 0 : p->len_min - p->len_tobuf;
	padding(p, 0);
	tmp = n < 0 ? -n : n;
	itoa_base_fill(tmp, 10, s, p);
	(p->f & SP_FL) ? s[0] = ' ' : 0;
	(n < 0) ? s[0] = '-' : 0;
	(p->f & PL_FL && n >= 0) ? s[0] = '+' : 0;
	buffer(p, s, p->len_tobuf);
	padding(p, 1);
}

void		itoa_base_printf(uintmax_t n, int b, t_global *p)
{
	uintmax_t	tmp;
	char		s[21];
	int			ext;

	p->len_tobuf = 0;
	tmp = n;
	while (tmp && ++p->len_tobuf)
		tmp /= b;
	(p->f & NIL_FL) ? p->precision = p->len_min : 0;
	ext = (p->len_tobuf >= p->precision) ? 0 : 1;
	p->len_tobuf = MAX(p->precision, p->len_tobuf);
	((p->f & HASH_FL) && b == 8 && !ext) ? --p->len_min : 0;
	((p->f & HASH_FL) && b == 8 && !n && (p->f & PREC_FL)) ?
	++p->len_tobuf : 0;
	((p->f & HASH_FL) && b == 16 && !(p->f & NIL_FL)) ? p->len_min -= 2 : 0;
	p->padding = MAX(0, (p->len_min - p->len_tobuf));
	padding(p, 0);
	if ((n || (p->f & POINT_FL))
		&& (p->f & HASH_FL) && ((b == 8 && !ext) || (b == 16)))
		buffer(p, "0", 1);
	if ((n || (p->f & POINT_FL)) && (p->f & HASH_FL) && b == 16)
		buffer(p, (p->f & UPPERC_FL) ? "X" : "x", 1);
	itoa_base_fill(n, b, s, p);
	buffer(p, s, p->len_tobuf);
	padding(p, 1);
}

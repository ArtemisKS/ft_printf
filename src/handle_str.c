/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 13:51:49 by akupriia          #+#    #+#             */
/*   Updated: 2018/12/04 13:51:50 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

/*
** 00000000 -- 0000007F: 	0xxxxxxx
** 00000080 -- 000007FF: 	110xxxxx 10xxxxxx
** 00000800 -- 0000FFFF: 	1110xxxx 10xxxxxx 10xxxxxx
** 00010000 -- 001FFFFF: 	11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
** nb_bytes <= MB_CUR_MAX define in stdlib.h
*/

static void	pf_putwchar(t_global *p, unsigned int wc, int wlen, int nb_bytes)
{
	char	tmp[4];

	if (nb_bytes <= wlen && nb_bytes <= MB_CUR_MAX)
	{
		if (nb_bytes == 1)
			tmp[0] = wc;
		else
		{
			if (nb_bytes == 2)
				tmp[0] = ((wc & (0x1f << 6)) >> 6) | 0xC0;
			else
			{
				if (nb_bytes == 3)
					tmp[0] = ((wc >> 12) & 0xf) | 0xE0;
				else
				{
					tmp[0] = ((wc >> 18) & 7) | 0xF0;
					tmp[1] = ((wc >> 12) & 0x3f) | 0x80;
				}
				tmp[nb_bytes - 2] = ((wc >> 6) & 0x3f) | 0x80;
			}
			tmp[nb_bytes - 1] = (wc & 0x3f) | 0x80;
		}
		buffer(p, tmp, nb_bytes);
	}
}

/*
** prints string and returns its len, if no len will print (null) and return 6
*/

void		pf_puterror(char *s, t_global *p)
{
	if (!s)
	{
		if (!(p->f & NIL_FL))
			buffer(p, "(null)", 6);
		else
			while (p->len_min--)
				buffer(p, "0", 1);
	}
	else
		buffer(p, s, ft_strlen(s));
}

/*
** print wide string and returns total len
** please refer to libft for ft_wcharlen and ft_wstrlen
*/

void		pf_putwstr(t_global *p)
{
	wchar_t		*s;
	int			charlen;

	if (!(s = va_arg(p->ap, wchar_t *)))
		pf_puterror(0, p);
	else
	{
		p->len_tobuf = (int)(ft_wstrlen((unsigned *)s));
		if (p->f & PREC_FL)
			p->len_tobuf = p->len_tobuf > p->precision ? p->precision : p->len_tobuf;
		if ((p->padding = (p->len_min - p->len_tobuf)) < 0)
			p->padding = 0;
		p->f = (p->len_min > p->precision) ?
			p->f & ~PREC_FL : p->f | PREC_FL;
		padding(p, 0);
		charlen = 0;
		while ((p->c = *s++) && (p->len_tobuf -= charlen) > 0)
		{
			charlen = ft_wcharlen(p->c);
			pf_putwchar(p, p->c, p->len_tobuf, charlen);
		}
		padding(p, 1);
	}
}

/*
** print regular string and returns its len
*/

void		pf_putstr(t_global *p)
{
	unsigned	*s;

	if (!(s = va_arg(p->ap, unsigned*)))
		pf_puterror(0, p);
	else
	{
		p->len_tobuf = (int)(ft_strlen((char*)s));
		if (p->f & PREC_FL)
			p->len_tobuf = p->len_tobuf > p->precision ? p->precision : p->len_tobuf;
		if ((p->padding = (p->len_min - p->len_tobuf)) > 0)
		{
			p->c = 32 | (p->f & NIL_FL);
			if (!(p->f & MIN_FL))
				while (p->padding--)
					buffer(p, &p->c, 1);
			else
			{
				buffer(p, s, p->len_tobuf);
				while (p->padding--)
					buffer(p, &p->c, 1);
				return ;
			}
		}
		buffer(p, s, p->len_tobuf);
	}
}

/*
** returns a single character len and display it
** refer to libft for putwchar amd wcharlen functions
*/

void		pf_character(t_global *p, unsigned c)
{
	if ((p->f & L_FL || p->f & L_FL2) && (!(p->len_tobuf = ft_wcharlen(c))))
		p->len = -1;
	else
		p->len_tobuf = 1;
	if ((p->padding = p->len_min - p->len_tobuf) < 0)
		p->padding = 0;
	padding(p, 0);
	pf_putwchar(p, c, p->len_tobuf, p->len_tobuf);
	padding(p, 1);
}

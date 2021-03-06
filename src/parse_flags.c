/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 13:51:53 by akupriia          #+#    #+#             */
/*   Updated: 2018/12/04 13:52:11 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

/*
** 						~ FLAGS ~
**
** flags interract between them, if there is a minus then it
** cancels the zero flag. if there is a + it cancels the sp flag.
** sharp is to add the prefix 0x for hexa for example
*/

static inline void	parse_flags(t_global *p)
{
	while ((p->n = ft_strchr_index("# +-0*", *p->format)) > -1 && ++p->format)
		p->f |= (1 << p->n);
	((p->f & MIN_FL) && !(p->f & WCARD_FL)) ? p->f &= ~NIL_FL : 0;
	(p->f & PL_FL) ? p->f &= ~SP_FL : 0;
	if (p->f & WCARD_FL)
	{
		p->f &= ~WCARD_FL;
		if ((p->n = (int)va_arg(p->ap, int)) < 0)
		{
			p->f |= MIN_FL;
			p->n = -p->n;
		}
		else
			p->f &= ~MIN_FL;
		if (!(p->f & PREC_FL))
			p->len_min = p->n;
		else
		{
			p->precision = (!(p->f & MIN_FL)) ? p->n : 0;
			p->f = (!p->n) ? p->f | PREC_FL : p->f & ~PREC_FL;
		}
	}
}

/*
** 						~ FIELD WIDTH ~
** if (48 < *p->format && *p->format < 58)
** An optional decimal digit string (with nonzero first digit) specifying a
** minimum field width. If the converted value has fewer characters than the
** field width, it will be padded with spaces on the left (or right, if the
** left-adjustment flag has been given). Instead of a decimal digit string
** one may write "*" or "*m$" (for some decimal integer m) to specify that
** the field width is given in the next argument, or in the m-th argument,
** respectively, which must be of type int. A negative field width is taken
** as a '-' flag followed by a positive field width. In no case does a
** nonexistent or small field width cause truncation of a field; if the result
** of a conversion is wider than the field width, the field is expanded to
** contain the conversion result.
**
** 2nd if : if there is a conv. specifier after the field width for a base it
** will reset the len_min to 0 EXCEPT if it was a padding with 0s ...
**
** 49 is ASCII for 1 and 57 for 9
*/

/*
** 						~ PRECISION ~
** if (*p->format == '.')
** An optional precision, in the form of a period ('.') followed by an optional
** decimal digit string. Instead of a decimal digit string one may write "*" or
** "*m$" (for some decimal integer m) to specify that the precision is given in
** the next argument, or in the m-th argument, respectively, which must be of
** type int. If the precision is given as just '.', or the precision is
** negative, the precision is taken to be zero. This gives the minimum number
** of digits to appear for d, i, o, u, x, and X conversions, the number of
** digits to appear after the radix character for a, A, e, E, f, and F
** conversions, the maximum number of significant digits for g and G
** conversions, or the maximum number of characters to be len_tobuf from a
** string for s and S conversions.
*/

/*
** 						~ LENGTH MODIFIER ~
** while (ft_strchr("hljzL", *p->format))
** converts into short, shortshort, long, long long, int_max, size_t depending
** on the input, respectively : h, hh, l, ll, j, z
*/

static inline int	ft_max(int a, int b)
{
	return (a > b ? a : b);
}

static inline void	field_width_precision(t_global *p)
{
	if (48 < *p->format && *p->format < 58)
		p->len_min = ft_max(ft_atoi_parse(&p->format), 1);
	if (*p->format == '.')
	{
		++p->format;
		p->precision = ft_max(ft_atoi_parse(&p->format), 0);
		p->f |= PREC_FL;
	}
	while (42)
	{
		if (*p->format == 'h')
			p->f |= (p->format[1] == 'h' && ++p->format) ? SH_FL2 : SH_FL;
		else if (*p->format == 'l')
			p->f |= (p->format[1] == 'l' && ++p->format) ? L_FL2 : L_FL;
		else if (*p->format == 'j')
			p->f |= IMAX_FL;
		else if (*p->format == 'z')
			p->f |= SIZET_FL;
		else if (*p->format == 'L')
			p->f |= L_FL2;
		else
			break ;
		++p->format;
	}
}

/*
** 						~ CONVERSION SPECIFIER ~
**
** A character that specifies the type of conversion to be applied
** if the character following % is a % then is it acts as an ESC char
** The conversion specifiers and their meanings are:
** 1) d, i, D : signed int
** 2) o, u, x, X : unsigned octal, uns. decimal, uns. hexa lower and uppercase
** 3) b, B for unsigned binary
** 3) c, C : char and large char
** 4) s : pointer to a string
** 5) n : the number of characters written so far is stored into the integer
** indicated by the int * pointer argument. No argument is converted.
** 6) m : Print output of strerror(errno). no arg. required
** 7) {} : adds color
** if the character is uppercase then p->cs.uppercase will be set to 1.
*/

static inline void	conversion_specifier(t_global *p)
{
	if (ft_strchr_index("CDSUOBX", p->c) > -1)
		p->f |= (p->c != 'X') ? L_FL : UPPERC_FL;
	if (p->c == 's')
		(p->f & L_FL || p->f & L_FL2) ? pf_putwstr(p) : pf_putstr(p);
	else if (p->c == 'd' || p->c == 'i' || p->c == 'D')
		pf_putnb(p);
	else if (p->c == 'f' || p->c == 'F')
		(p->f & PREC_FL && !p->precision) ? pf_putnb(p) : pf_putdouble(p, 10);
	else if ((p->len_tobuf = ft_strchr_index("dDbBdDdDoOuUdDdDxX", p->c)) > -1)
		pf_putnb_base(p->len_tobuf & ~1, p);
	else if (p->c == 'c' || p->c == 'C')
		pf_character(p, va_arg(p->ap, unsigned));
	else if (p->c == 'S')
		pf_putwstr(p);
	else if (p->c == 'p')
		print_pointer_address(p);
	else if (p->c == 'n')
		*va_arg(p->ap, int *) = p->len;
	else if (p->c == 'm')
		pf_puterror(strerror(errno), p);
	else if (p->c == 'a' || p->c == 'A')
		(p->f & PREC_FL && !p->precision) ? pf_putnb(p) : pf_putdouble(p, 16);
	else
		cs_not_found(p);
	p->len > 0 ? p->i = 0 : 0;
}

/*
** 						~ PARSING OPTONAL INPUTS ~
**
** here we parse the % to check for optional inputs :
** 1) flags, 2) field width, 3) precision and 4) length modifiers.
** Please refer to the man for a more accurate and full description.
** 5) the call to wildcard_length_modifier is a bonus where the '*' given
** the field_width or precision in the va_list ap.
** 6) the second call to parse_flags is to handle undefined behaviors.
*/

void		parse_optionals(t_global *p)
{
	p->f = 0;
	p->len_min = 0;
	p->precision = 1;
	parse_flags(p);
	field_width_precision(p);
	parse_flags(p);
	(p->f & PL_FL) ? p->f &= ~SP_FL : 0;
	p->c = *p->format;
	conversion_specifier(p);
}

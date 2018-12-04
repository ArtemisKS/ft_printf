/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 13:51:34 by akupriia          #+#    #+#             */
/*   Updated: 2018/12/04 13:51:35 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

/*
** main function : printf will return the total len of chars displayed by printf
*/

int		ft_printf(const char *format, ...)
{
	t_global	p;

	ft_bzero(&p, sizeof(p));
	p.fd = 1;
	p.format = (char *)format;
	va_start(p.ap, format);
	while (*p.format && p.len > -1)
	{
		if (*p.format == '%')
		{
			++p.format;
			if (!*p.format || (*p.format == ' ' && (!p.format[1]
			|| (!p.format[2] && p.format[1] == 'h'))))
				break ;
			else
				parse_optionals(&p);
		}
		else if (++p.i)
			buffer(&p, &*p.format, 1);
		++p.format;
	}
	(p.len < 0) ? write(p.fd, p.buff, p.buf_ind - p.i)
		: write(p.fd, p.buff, p.buf_ind);
	va_end(p.ap);
	return (p.len);
}

/*
** bonus function to specify a specific fd, similar to libc dprintf
*/

int		ft_dprintf(int fd, const char *format, ...)
{
	t_global	p;

	ft_bzero(&p, sizeof(p));
	p.fd = fd;
	p.format = (char *)format;
	va_start(p.ap, format);
	while (*p.format && p.len > -1)
	{
		if (*p.format == '%')
		{
			++p.format;
			if (!*p.format || (*p.format == ' ' && (!p.format[1]
			|| (!p.format[2] && p.format[1] == 'h'))))
				break ;
			else
				parse_optionals(&p);
		}
		else if (++p.i)
			buffer(&p, &*p.format, 1);
		++p.format;
	}
	(p.len < 0) ? write(p.fd, p.buff, p.buf_ind - p.i)
		: write(p.fd, p.buff, p.buf_ind);
	va_end(p.ap);
	return (p.len);
}

/*
** sprintf returns the string
** Caution : intended for string < 64 (BUFF in define) characters.
*/

char	*ft_sprintf(const char *format, ...)
{
	t_global	p;
	char		*ret;

	ft_bzero(&p, sizeof(p));
	p.fd = 1;
	p.format = (char *)format;
	va_start(p.ap, format);
	while (*p.format && p.len > -1)
	{
		if (*p.format == '%')
			parse_optionals(&p);
		else if (++p.i)
			buffer(&p, &*p.format, 1);
		++p.format;
	}
	p.buff[p.buf_ind + 1] = '\0';
	if (!(ret = ft_strdup(p.buff)))
		return (NULL);
	va_end(p.ap);
	return (ret);
}

/*
** function that displays pointer address
*/

void	print_pointer_address(t_global *p)
{
	void	*pointer;

	pointer = va_arg(p->ap, void *);
	p->f &= ~HASH_FL;
	p->len_min -= (p->f & NIL_FL ? 2 : 0);
	p->padding = (p->len_tobuf > p->len_min - 3) ? 0 :
		p->len_min - 3 - p->len_tobuf;
	p->f |= HASH_FL;
	p->f |= POINT_FL;
	p->len_tobuf = 0;
	itoa_base_printf((uintmax_t)pointer, 16, p);
}

/*
** function if no conversion specifier was found.
*/

void	cs_not_found(t_global *p)
{
	if ((p->padding = p->len_min - 1) > 0)
	{
		padding(p, 0);
		buffer(p, p->format, 1);
		padding(p, 1);
	}
	else
		buffer(p, p->format, 1);
}

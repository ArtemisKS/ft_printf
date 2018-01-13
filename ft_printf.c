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

// if (*fmt == '%' && *(fmt + 1) && *(fmt + 1) == 's') 
// 		{
// 			s = va_arg(ap, char *);
// 			ft_putstr(s);
// 			fmt += 2;
// 		}
// 		else if (*fmt == '%' && *(fmt + 1) && *(fmt + 1) == 'o')
// 		{
// 			d = va_arg(ap, int);
// 			s = ft_itoa_base(d, 8);
// 			ft_putstr(s);
// 			fmt += 2;
// 		}
// 		else if (*fmt == '%' && *(fmt + 1) && (*(fmt + 1) == 'X' || *(fmt + 1) == 'x'))
// 		{
// 			d = va_arg(ap, int);
// 			s = ft_itoa_base(d, 16);
// 			*fmt == 'X' ? ft_putstr(s) : ft_putstr(s_tolower(s));
// 			fmt += 2;
// 		}
// 		else if (*fmt == '%' && *(fmt + 1) && (*(fmt + 1) == 'd' || *(fmt + 1) == 'i'))
// 		{
// 			d = va_arg(ap, int);
// 			ft_putnbr(d);
// 			fmt += 2;
// 		}
// 		else if (*fmt == '%' && *(fmt + 1) && *(fmt + 1) == 'c')
// 		{
// 			c = (char) va_arg(ap, int);
// 			write(1, &c, 1);
// 			fmt += 2;
// 		}
// 		else if (*fmt == '\\' && *(fmt + 1) && *(fmt + 1) == 'n')
// 		{
// 			write(1, "\n", 1);
// 			fmt += 2;
// 		}
// 		else if (*fmt == '%' && *(fmt + 1) && *(fmt + 1) == '%')
// 		{
// 			write(1, "%", 1);
// 			fmt += 2;
// 		}
// 		else
// 		{
// 			write(1, &(*fmt), 1);
// 			fmt++;
// 		}

void	print_struct(t_spec *ts)
{
	write(1, "space\n", 6);
	ft_putnbr(ts->space);
	write(1, "\nhash\n", 6);
	ft_putnbr(ts->hash);
	write(1, "\nmin\n", 5);
	ft_putnbr(ts->min);
	write(1, "\nplus\n", 6);
	ft_putnbr(ts->plus);
	write(1, "\nnil\n", 5);
	ft_putnbr(ts->nil);
	write(1, "\nwidth\n", 7);
	ft_putnbr(ts->width);
	write(1, "\nprec\n", 6);
	ft_putnbr(ts->prec);
	write(1, "\nhh\n", 4);
	ft_putnbr(ts->hh);
	write(1, "\nh\n", 3);
	ft_putnbr(ts->h);
	write(1, "\nl\n", 3);
	ft_putnbr(ts->l);
	write(1, "\nll\n", 4);
	ft_putnbr(ts->ll);
	write(1, "\nj\n", 3);
	ft_putnbr(ts->j);
	write(1, "\nz\n", 3);
	ft_putnbr(ts->z);
}

int max(int a, int b)
{
	return a > b ? a : b;
}

int min(int a, int b)
{
	return a < b ? a : b;
}

char 	*handle_digit(va_list ap, t_spec *ts)
{
	long long int i;
	int il;
	int f_len;
	char *fs;
	int j;
	int j1;
	char *is;

	if (ts->l == 1)
		i = va_arg(ap, long int);
	else if (ts->ll == 1)
		i = va_arg(ap, long long int);
	else if (ts->h == 1)
		i = (short int)va_arg(ap, int);
	else if (ts->hh)
		i = (char)va_arg(ap, int);
	else
		i = va_arg(ap, int);
	//printf("%lld\n", i);
	il = ft_nbrlen(i);
	f_len = max(il, ts->width);
	f_len = max(f_len, ts->prec);
	fs = (char *)ft_memalloc(f_len + 1);
	is = ft_itoa_base(i, 10);
	//ft_putnbr(i);
	//ft_putstr(is);
	if (ts->nil == 1 && il < f_len && ts->min == 0 && ts->plus == 0 && ts->space == 0)
	{
		j = 0;
		while (j < f_len - il)
		{
			fs[j] = '0';
			j++;
		}
		j1 = 0;
		while (j < f_len)
		{
			fs[j] = is[j1];
			j++;
			j1++;
		}
	}
	else if (ts->min == 1 && il < f_len && ts->plus == 0 && ts->space == 0)
	{
		j = 0;
		if (ts->prec <= il)
		{
			j1 = 0;
			//write(1, "douche!\n", 8);
			while (j < il)
			{
				fs[j] = is[j1];
				j++;
				j1++;
			}
			while (j < f_len)
			{
				fs[j] = ' ';
				j++;
			}
		}
		else
		{
			while (j < ts->prec - il)
			{
				fs[j] = '0';
				j++;
			}
			j1 = 0;
			//write(1, "douche!\n", 8);
			while (j < ts->prec)
			{
				fs[j] = is[j1];
				j++;
				j1++;
			}
			while (j < f_len)
			{
				fs[j] = ' ';
				j++;
			}

		}
	}
	else if (ts->plus == 0 && ts->min == 0 && ts->nil == 0 && ts->space == 0)
	{
		j = 0;
		if (ts->prec <= il)
		{
			while (j < f_len - il)
			{
				fs[j] = ' ';
				j++;
			}
			j1 = 0;
			while (j < f_len)
			{
				fs[j] = is[j1];
				j++;
				j1++;
			}
		}
		else
		{
			while (j < f_len - ts->prec)
			{
				fs[j] = ' ';
				j++;
			}
			while (j < f_len - il)
			{
				fs[j] = '0';
				j++;
			}
			j1 = 0;
			while (j < f_len)
			{
				fs[j] = is[j1];
				j++;
				j1++;
			}
		}
	}
	else if ((ts->plus == 1 && ts->min == 0 && ts->nil == 1) || (ts->plus == 1 && ts->min == 0 && ts->width != 0))
	{
		j = 0;
		if (ts->prec != 0)
		{
			while (j < f_len - max(il, ts->prec))
			{
				fs[j] = ' ';
				j++;
			}
			while (j < f_len - min(il, ts->prec))
			{
				fs[j] = '0';
				j++;
			}
			j1 = 0;
			while (j < f_len)
			{
				fs[j] = is[j1];
				j++;
				j1++;
			}
			while (fs[j--] != ' ')
				;
			if (i > 0)
				fs[++j] = '+';
			else 
				fs[++j] = '-';
		}
		else
		{
			f_len++;
			//write(1, "douche!\n", 8);
			if (i > 0)
				fs[j++] = '+';
			else 
				fs[j++] = '-';
			while (j < f_len - il)
			{
				fs[j] = '0';
				j++;
			}
			j1 = 0;
			while (j < f_len)
			{
				fs[j] = is[j1];
				j++;
				j1++;
			}
			//ft_putnbr(j);
		}
	}
	else if ((ts->plus == 1 && ts->min == 1 && ts->nil == 1) || (ts->plus == 1 && ts->min == 1 && ts->width != 0))
	{
		j = 0;
		if (ts->prec != 0)
		{
			//write(1, "douche!\n", 8);
			if (i > 0)
				fs[j++] = '+';
			else 
				fs[j++] = '-';
			while (j < ts->prec - il + 1)
			{
				fs[j] = '0';
				j++;
			}
			j1 = 0;
			while (j < ts->prec + 1)
			{
				fs[j] = is[j1];
				j++;
				j1++;
			}
			while (j < f_len)
			{
				fs[j] = ' ';
				j++;
			}
		}
		else
		{
			if (i > 0)
				fs[j++] = '+';
			else 
				fs[j++] = '-';
			j1 = 0;
			while (j1 < il)
			{
				fs[j] = is[j1];
				j++;
				j1++;
			}
			while (j < f_len)
			{
				fs[j] = ' ';
				j++;
			}
			//ft_putnbr(j);
		}
	}
	else if (ts->plus == 1 && ts->nil == 0 && ts->width == 0 && ts->prec != 0)
	{
		f_len++;
		j = 0;
		if (i > 0)
				fs[j++] = '+';
		else 
			fs[j++] = '-';
		while (j < f_len - il)
		{
			fs[j] = '0';
			j++;
		}
		j1 = 0;
		while (j < f_len)
		{
			fs[j] = is[j1];
			j++;
			j1++;
		}
	}
	else if (ts->plus == 0 && ts->space == 1 && ts->nil == 0 && ts->width == 0 && ts->prec != 0)
	{
		f_len++;
		j = 0;
		fs[j++] = ' ';
		//write(1, "douche!\n", 8);
		while (j < f_len - il)
		{
			fs[j] = '0';
			j++;
		}
		j1 = 0;
		while (j < f_len)
		{
			fs[j] = is[j1];
			j++;
			j1++;
		}
	}
	else if ((ts->plus == 0 && ts->space == 1 && ts->min == 1 && ts->nil == 1) || (ts->plus == 0 && ts->space == 1 && ts->min == 1 && ts->width != 0))
	{
		j = 0;
		if (ts->prec != 0)
		{
			//write(1, "douche!\n", 8);
			fs[j++] = ' ';
			while (j < f_len - max(il, ts->prec))
			{
				fs[j] = '0';
				j++;
			}
			j1 = 0;
			while (j < f_len - (max(il, ts->prec) - min(il, ts->prec)))
			{
				fs[j] = is[j1];
				j++;
				j1++;
			}
			while (j < f_len)
			{
				fs[j] = ' ';
				j++;
			}
		}
		else
		{
			//write(1, "douche!\n", 8);
			fs[j++] = ' ';
			j1 = 0;
			while (j1 < il)
			{
				fs[j] = is[j1];
				j++;
				j1++;
			}
			while (j < f_len)
			{
				fs[j] = ' ';
				j++;
			}
			//ft_putnbr(j);
		}
	}
		else if ((ts->plus == 0 && ts->space == 1 && ts->min == 0 && ts->nil == 1) || (ts->plus == 0 && ts->space == 1 && ts->min == 0 && ts->width != 0))
		{
			j = 0;
			if (ts->prec != 0)
			{
				//write(1, "douche!\n", 8);
				while (j < f_len - max(il, ts->prec))
				{
					fs[j] = ' ';
					j++;
				}
				while (j < f_len - min(il, ts->prec))
				{
					fs[j] = '0';
					j++;
				}
				j1 = 0;
				while (j < f_len)
				{
					fs[j] = is[j1];
					j++;
					j1++;
				}
			}
			else
			{
				//write(1, "douche!\n", 8);
				fs[j++] = ' ';
				while (j < f_len - il)
				{
					fs[j] = '0';
					j++;
				}
				j1 = 0;
				while (j < f_len)
				{
					fs[j] = is[j1];
					j++;
					j1++;
				}
			}
		}
	return (fs);
}

char	*print_format(va_list ap, t_spec *ts, char c)
{
	char *res;

	res = (char *)ft_memalloc(1);
 	if (c == 'd' || c == 'i')
 		res = handle_digit(ap, ts);
// 	else if (c == 'u' || c == 'o' || c == 'X' || c == 'x')
// 		res = handle_unsigned(ap, ts);
// 	else if (c == 'c')
// 		res = handle_char(ap, ts);
// 	else
// 		res = handle_string(ap, ts);
	return (res);
}

t_spec 	*init_struct(t_spec *ts)
{
	ts->hash = 0;
	ts->min = 0;
	ts->space = 0;
	ts->plus = 0;
	ts->nil = 0;
	ts->hh = 0;
	ts->h = 0;
	ts->l = 0;
	ts->ll = 0;
	ts->j = 0;
	ts->z = 0;
	ts->width = 0;
	ts->prec = 0;
	return (ts);
}

int		parse_width(char *fmt, t_spec *ts)
{
	int i;
	char *wid;

	i = 0;
	while (fmt[i] >= '0' && fmt[i] <= '9')
		i++;
	wid = (char *)ft_memalloc(i + 1);
	i = 0;
	while (fmt[i] >= '0' && fmt[i] <= '9')
	{
		wid[i] = fmt[i];
		i++;
	}
	wid[i] = 0;
	ts->width = ft_atoi(wid);
	return (i);
}

int		parse_pres(char *fmt, t_spec *ts)
{
	int i;
	char *prec;

	i = 0;
	while (fmt[i] >= '0' && fmt[i] <= '9')
		i++;
	prec = (char *)ft_memalloc(i + 1);
	i = 0;
	while (fmt[i] >= '0' && fmt[i] <= '9')
	{
		prec[i] = fmt[i];
		i++;
	}
	prec[i] = 0;
	ts->prec = ft_atoi(prec);
	return (i);
}

int		parse_spec(char *fmt, t_spec *ts)
{
	int i;

	i = 0;
	ts = init_struct(ts);
	while (fmt[i] == '-' || fmt[i] == '+' || fmt[i] == ' ' || fmt[i] == '0' || fmt[i] == '#')
	{
		if (fmt[i] == '-')
			ts->min = 1;
		else if (fmt[i] == '+')
			ts->plus = 1;
		else if (fmt[i] == ' ')
			ts->space = 1;
		else if (fmt[i] == '0')
			ts->nil = 1;
		else if (fmt[i] == '#')
			ts->hash = 1;
		i++;
	}
	// write(1, &fmt[i], 1);
	// write(1, "\n", 1);
	i += parse_width(&fmt[i], ts);
	// write(1, &fmt[i], 1);
	// write(1, "\n", 1);
	if (fmt[i] == '.')
		i += parse_pres(&fmt[i + 1], ts) + 1;
	// write(1, &fmt[i], 1);
	// write(1, "\n", 1);
	if (fmt[i] == 'l' && fmt[i + 1] && fmt[i + 1] == 'l')
	{
		ts->ll = 1;
		i += 2;
	}
	else if (fmt[i] == 'h' && fmt[i + 1] && fmt[i + 1] == 'h')
	{
		ts->hh = 1;
		i += 2;
	}
	else if (fmt[i] == 'l' && fmt[i + 1] && fmt[i + 1] != 'l')
	{
		ts->l = 1;
		i++;
	}
	else if (fmt[i] == 'h' && fmt[i + 1] && fmt[i + 1] != 'h')
	{
		ts->h = 1;
		i++;
	}
	else if (fmt[i] == 'j')
	{
		ts->j = 1;
		i++;
	}
	else if (fmt[i] == 'z')
	{
		ts->z = 1;
		i++;
	}
	// write(1, &fmt[i], 1);
	// write(1, "\n", 1);
	return (i);
}

// char	*print_format(va_list ap, t_specform *ts)
// {
// 	if (ts->type[0] == 49)
// 		handle_digit(ap, ts);
// 	else if (ts->type[1] == 49)
// 		handle_octal(ap, ts);
// 	else if (ts->type[2] == 49)
// 		handle_unsigned(ap, ts);
// 	else if (ts->type[3] == 49 || ts->type[3] == 50)
// 		handle_hex(ap, ts);
// 	else if (ts->type[4] == 49 || ts->type[4] == 50)
// 		handle_float(ap, ts);
// 	else if (ts->type[5] == 49 || ts->type[5] == 50)
// 		handle_efloat(ap, ts);
// 	else if (ts->type[6] == 49 || ts->type[6] == 50)
// 		handle_gfloat(ap, ts);
// 	else if (ts->type[7] == 49 || ts->type[7] == 50)
// 		handle_hexfloat(ap, ts);
// 	else if (ts->type[8] == 49 || ts->type[8] == 50)
// 		handle_char(ap, ts);
// 	else if (ts->type[9] == 49 || ts->type[9] == 50)
// 		hanlde_string(ap, ts);
// 	else if (ts->type[10] == 49)
// 		handle_pointer(ap, ts);
// 	else if (ts->type[11] == 49)
// 		handle_intn(ap, ts);

// }

// int		parse_spec(char *fmt, t_specform *ts)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	init_struct(ts);
// 	i += parse_flags(&fmt[i], ts);
// 	i += parse_width(&fmt[i], ts);
// 	if (fmt[i] == '.')
// 		i += parse_pres(&fmt[++i], ts);
// 	i += parse_size(&fmt[i], ts);
// 	i += parse_type(&fmt[i], ts);
// 	return (i);
// }

// int		parse_width(char *fmt, t_specform *ts)
// {
// 	int i;
// 	char *wid;

// 	i = 0;
// 	while (fmt[i] > '0' && fmt[i] < '9')
// 		i++;
// 	wid = (char *)ft_memalloc(i + 1);
// 	i = 0;
// 	while (fmt[i] > '0' && fmt[i] < '9')
// 		wid[i] = fmt[i++];
// 	wid[i] = 0;
// 	ts->width = ft_atoi(wid);
// 	return (i);
// }

// int		parse_size(char *fmt, t_specform *ts)
// {
// 	int i;

// 	i = 0;
// 	if (fmt[i] == 'l' && fmt[i + 1] && fmt[i + 1] != 'l')
// 		ts->size[0]++;
// 	else if (fmt[i] == 'h' && fmt[i + 1] && fmt[i + 1] != 'h')
// 		ts->size[2]++;
// 	else if (fmt[i] == 'j')
// 		ts->size[4]++;
// 	else if (fmt[i] == 'z')
// 		ts->size[5]++;
// 	else if (fmt[i] == 'h' && fmt[i + 1] && fmt[i + 1] == 'h')
// 		ts->size[1]++;
// 	else if (fmt[i] == 'l' && fmt[i + 1] && fmt[i + 1] == 'l')
// 		ts->size[3]++;
// 	if (ts->size[1] != 48 || ts->size[3] != 48)
// 		i += 2;
// 	else
// 		i++;
// 	return (i);
// }


// int		parse_type(char *fmt, t_specform *ts)
// {
// 	int i;

// 	i = 0;
// 	if (fmt[i] == 'd' || fmt[i] == 'i')
// 		ts->type[0]++;
// 	else if (fmt[i] == 'o')
// 		ts->type[1]++;
// 	else if (fmt[i] == 'u')
// 		ts->type[2]++;
// 	else if (fmt[i] == 'x' || fmt[i] == 'X')
// 		fmt[i] == 'x' ? ts->type[3]++ : ts->type[3] += 2;
// 	else if (fmt[i] == 'f' || fmt[i] == 'F')
// 		fmt[i] == 'f' ? ts->type[4]++ : ts->type[4] += 2;
// 	else if (fmt[i] == 'e' || fmt[i] == 'E')
// 		fmt[i] == 'e' ? ts->type[5]++ : ts->type[5] += 2;
// 	else if (fmt[i] == 'g' || fmt[i] == 'G')
// 		fmt[i] == 'g' ? ts->type[6]++ : ts->type[6] += 2;
// 	else if (fmt[i] == 'a' || fmt[i] == 'A')
// 		fmt[i] == 'a' ? ts->type[7]++ : ts->type[7] += 2;
// 	else if (fmt[i] == 'c' || fmt[i] == 'C')
// 		fmt[i] == 'c' ? ts->type[8]++ : ts->type[8]++ && ts->size[0]++;
// 	else if (fmt[i] == 's' || fmt[i] == 'S')
// 		fmt[i] == 's' ? ts->type[9]++ : ts->type[9]++ && ts->size[0]++;
// 	else if (fmt[i] == 'p')
// 		ts->type[10]++;
// 	else if (fmt[i] == 'n')
// 		ts->type[11]++;
// 	i++;
// 	return (i);
// }
// int		parse_pres(char *fmt, t_specform *ts)
// {
// 	int i;
// 	char *prec;

// 	i = 0;
// 	while (fmt[i] > '0' && fmt[i] < '9')
// 		i++;
// 	prec = (char *)ft_memalloc(i + 1);
// 	i = 0;
// 	while (fmt[i] > '0' && fmt[i] < '9')
// 		prec[i] = fmt[i++];
// 	prec[i] = 0;
// 	ts->precision = ft_atoi(prec);
// 	return (i);
// }

// void init_struct(t_specform *ts)
// {
// 	int i;

// 	i = 0;
// 	ts = (t_specform *)malloc(sizeof(t_specform));
// 	ts->flags = (char *)ft_memalloc(5);
// 	while (i < 4)
// 		ts->flags[i++] = 48;
// 	ts->flags[i] = 0;
// 	ts->width = 0;
// 	ts->precision = 0;
// 	ts->size = (char *)ft_memalloc(7);
// 	i = 0;
// 	while (i < 6)
// 		ts->size[i++] = 48;
// 	ts->size[i] = 0;
// 	i = 0;
// 	ts->type = (char *)ft_memalloc(13);
// 	while (i < 12)
// 		ts->type[i++] = 48;
// 	ts->type[i] = 0;
// }

// char		*parse_flags(char *fmt, t_specform *ts)
// {
// 	int j;
// 	int fl;

// 	j = 0;
// 	fl = 1;
// 	while (fmt[j] == '-' || fmt[j] == '+' || fmt[j] == ' ' || fmt[j] == '#' ||fmt[j] == '0')
// 	{
// 		if (!flags_to_parse(fmt, ts, j) && fmt[j + 1] && fmt[j + 1] != '-'
// 			&& fmt[j + 1] != '+' && fmt[j + 1] != ' ' && fmt[j + 1] != '#' && fmt[j + 1] != '0')
// 			break ;
// 		j++;
// 	}
// 	return (j);
// }

// int  flags_to_parse(char *fmt, t_specform *ts, int j)
// {
// 		if (fmt[j] == '-' && ts->flags[0] == 48)
// 			ts->flags[0]++;
// 		else if (fmt[j] == '+' && ts->flags[1] == 48)
// 			ts->flags[1]++;
// 		else if (fmt[j] == ' ' && ts->flags[1] == 48)
// 			ts->flags[1] += 2;
// 		else if (fmt[j] == '#' && ts->flags[2] == 48)
// 			ts->flags[2]++;
// 		else if (fmt[j] == '0' && ts->flags[3] == 48)
// 			ts->flags[3]++;
// 		else 
// 			return (0);
// 		return (1);
// }

char	*parse_format(va_list ap, char *fmt)
{
	//int d, 
	int i, j;
	//char c, 
	char *s;
	char *out;
	t_spec *ts;

	i = 0;
	j = 0;
	//d = va_arg(ap, int);
	ts = (t_spec *)malloc(sizeof(t_spec));
	out = (char *)ft_memalloc(1);
	while (fmt[i])
	{
		if (fmt[i] == '%' && fmt[i + 1] && fmt[i + 1] != '%')
		{
			//s = ft_strsub(fmt, j, i - j);
			//out = ft_strjoin(out, s);
			i++;
			i += parse_spec(&fmt[i], ts);
			// write(1, &fmt[i], 1);
			// write(1, "\n", 1);
			s = print_format(ap, ts, fmt[i]);
			ft_putstr(s);
			//out = ft_strjoin(out, s);
			j = i + 1;
			//print_struct(ts);
		}
		else if (fmt[i] == '%' && fmt[i + 1] && fmt[i + 1] == '%')
		{
			s = ft_strdup("%");
			ft_putstr(s);
			i++;
		}
		else
			write(1, &fmt[i], 1);
		// else if (fmt[i] == '%' && fmt[i + 1] && fmt[i + 1] == '%')
		// {
		// 	s = ft_strsub(fmt, j, i - j);
		// 	out = ft_strjoin(out, s);
		// 	s = ft_strdup("%");
		// 	out = ft_strjoin(out, s);
		// 	i++;
		// 	j = i + 1;
		// }
		i++;
	}
	return (out);
}


int	ft_printf(char *fmt, ...)
{
	va_list ap;
	char* res;

	res = fmt;
	va_start(ap, fmt);
	fmt = parse_format(ap, fmt);
	va_end(ap);
	return (fmt - res);
}

int main()
{
	ft_printf("My_printf: |%+013.8d| %%|", 1278);
	write(1, "\n", 1);
	//printf("%-+8d", 1234);
	printf("DefPrintf: |%+013.8d| %%|", 1278);
	printf("\n");
	//printf("%+07.5d", 1234);
	return (0);
}

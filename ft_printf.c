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

char	*min_handle(char *is)
{
	int i;
	char *res;
	int fl;
	int j;

	i = 1;
	fl = 0;
	j = 0;
	res = (char *)ft_memalloc(ft_strlen(is) - 1);
	while (is[i])
	{
		if (is[i] > '0' && is[i] <= '9')
			fl = 1;
		if (fl)
		{
			res[j] = is[i];
			j++;
		}
		i++;
	}
	return (res);
}

char	*handle_str(t_spec *ts, char *s)
{
	int j;
	int j1;
	char *fs;
	int il;
	int f_len;
	char *is;

	il = ft_strlen(s);
	f_len = max(il, ts->width);
	f_len = max(f_len, ts->prec);
	is = ft_strdup(s);
	fs = (char *)ft_memalloc(f_len + 1);
	if (ts->min == 1)
	{
		j = 0;
		if (ts->prec != 0 && ts->width != 0)
			f_len = max(ts->prec, ts->width);
		else if (ts->prec != 0)
			f_len = ts->prec;
		if (ts->prec != 0)
		{
			if (s[0])
			{
				j1 = 0;
				while (j < (int)ts->prec)
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
				if (f_len != (int)ts->prec)
					while (j < f_len)
					{
						fs[j] = ' ';
						j++;
					}
		}
		else
		{
			j1 = 0;
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
	}
	else if (ts->plus == 0 && ts->min == 0 && ts->nil == 0 && ts->space == 0)
	{
		j = 0;
		// write(1, "douche!\n", 8);
		// ft_putnbr(f_len);
		// write(1, "\n", 1);
		// ft_putstr(s);
		// write(1, "\n", 1);
		// ft_putnbr(il);
		// write(1, "\n", 1);
		if (ts->prec != 0 && ts->width != 0)
			f_len = max(ts->prec, ts->width);
		else if (ts->prec != 0)
			f_len = ts->prec;
		// write(1, "douche!\n", 8);
		// ft_putnbr(f_len);
		// write(1, "\n", 1);
		// ft_putstr(s);
		// write(1, "\n", 1);
		// ft_putnbr(il);
		// write(1, "\n", 1);
		if ((int)ts->prec > il)
		{
			j1 = 0;
			// ft_putnbr(f_len);
			// write(1, "\n", 1);
			if (s[0] && ts->width != 0)
			{
				while (j < f_len - (int)ts->prec)
						fs[j++] = ' ';
				while (j < f_len - il)
					fs[j++] = ' ';
				while (j < f_len && j1 < (int)ft_strlen(is))
				{
					fs[j] = is[j1];
					j++;
					j1++;
				}
			}
			else if (!ts->width)
			{
				while (j < f_len && j1 < (int)ft_strlen(is))
				{
					fs[j] = is[j1];
					j++;
					j1++;
				}
			}
			else
			{
				if (f_len != (int)ts->prec)
					while (j < f_len)
					{
						fs[j] = ' ';
						j++;
					}
			}
		}
		else
		{
			if (!ts->width)
			{
				if (!ts->prec)
				while (j < f_len - (int)il)
				{
					fs[j] = ' ';
					j++;
				}
			else
				while (j < f_len - (int)ts->prec)
				{
					fs[j] = ' ';
					j++;
				}
			}
			j1 = 0;
			while (j < f_len && j1 < (int)ft_strlen(is))
			{
				fs[j] = is[j1];
				j++;
				j1++;
			}
		}
	}
	return (fs);
}

char	*handle_dig(t_spec *ts, intmax_t i)
{
	int j;
	int j1;
	char *fs;
	int il;
	int f_len;
	char *is;

	if (i < 0)
		il = ft_nbrlen(i * -1);
	else
		il = ft_nbrlen(i);
	// ft_putnbr(il);
	// write(1, "\n", 1);
	f_len = max(il, ts->width);
	f_len = max(f_len, ts->prec);
	// ft_putstr(is);
	// write(1, "\n", 1);
	is = ft_itoa_base(i, 10);
	if (i < 0)
		is = min_handle(is);
	fs = (char *)ft_memalloc(f_len + 1);

	if (ts->dot == 1 && ts->prec == 0 && i == 0)
	{
		j = 0;
		if (ts->width == 0)
		{
			fs[0] = 0;
			return  (fs);
		}
		else
		{
			while (j < f_len)
			{
				fs[j] = ' ';
				j++;
			}
		}
	}
	else if (ts->min == 0 && ts->space == 0 && ts->plus == 0 
		&& ts->nil == 0 && ts->width == 0 && ts->prec == 0 && i >= 0)
	{
		j = 0;
		while (j < il)
			{
				fs[j] = is[j];
				j++;
			}
			// ft_putstr(fs);
 		// 	write(1, "\n", 1);
	}
	else if (ts->nil == 1 && ts->min == 0 && ts->plus == 0 && ts->space == 0 && i >= 0)
	{
		j = 0;
		//write(1, "douche!\n", 8);
		if ((int)ts->prec <= il)
		{
			while (j < f_len - max(max(il, ts->prec), ts->width))
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
		else
		{
			while (j < f_len - (int)ts->prec)
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
	else if (ts->min == 1 && ts->plus == 0 && ts->space == 0 && i >= 0)
	{
		j = 0;
		if ((int)ts->prec <= il)
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
			while (j < (int)(ts->prec - il))
			{
				fs[j] = '0';
				j++;
			}
			j1 = 0;
			//write(1, "douche!\n", 8);
			while (j < (int)ts->prec)
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
	else if (ts->plus == 0 && ts->min == 0 && ts->nil == 0 && ts->space == 0 && i >= 0)
	{
		j = 0;
		// write(1, "douche!\n", 8);
		// ft_putnbr(f_len);
		// write(1, "\n", 1);
		// ft_putnbr(il);
		// write(1, "\n", 1);
		if ((int)ts->prec <= il)
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
			while (j < (int)(f_len - ts->prec))
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
	else if ((ts->plus == 1 && ts->min == 0 && ts->nil == 1) || 
		(i < 0 && ts->min == 0 && ts->nil == 1))
	{
		j = 0;
		if (f_len == il)
			f_len++;
		//ft_putnbr(f_len);
		//write(1, "\n", 1);
		if (ts->prec != 0)
		{
			//write(1, "douche!\n", 8);
			while (j < f_len - max(il, ts->prec))
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
			while (fs[j--] != ' ')
				;
			if (i >= 0)
				fs[++j] = '+';
			else 
				fs[++j] = '-';
		}
		else
		{
			//write(1, "douche!\n", 8);
			if (i >= 0)
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
	else if ((ts->plus == 1 && ts->min == 0 && ts->width != 0) || 
		(i < 0 && ts->min == 0 && ts->width != 0))
	{
		j = 0;
		//f_len++;
		 // ft_putnbr(f_len);
		 // write(1, "\n", 1);
		 // ft_putnbr(il);
		 // write(1, "\n", 1);
		if (ts->prec != 0)
		{
			//write(1, "douche!\n", 8);
			while (j < f_len - max(il, ts->prec))
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
			while (fs[j--] != ' ')
				;
			if (i > 0)
				fs[++j] = '+';
			else 
				fs[++j] = '-';
		}
		else
		{
			//write(1, "douche!\n", 8);
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
			while (fs[j] != ' ')
				j--;
			if (i >= 0)
				fs[j++] = '+';
			else 
				fs[j++] = '-';
			//ft_putnbr(j);
		}
	}
	else if ((ts->plus == 1 && ts->min == 1 && ts->nil == 1) ||
		(i < 0 && ts->min == 1 && ts->nil == 1) ||
		 (ts->plus == 1 && ts->min == 1 && ts->width != 0) || 
		 (i < 0 && ts->min == 1 && ts->width != 0))
	{
		j = 0;
		if (ts->prec != 0)
		{
			//write(1, "douche!\n", 8);
			if (i >= 0)
				fs[j++] = '+';
			else 
				fs[j++] = '-';
			while (j < (int)(ts->prec - il + 1))
			{
				fs[j] = '0';
				j++;
			}
			j1 = 0;
			while (j < (int)(ts->prec + 1))
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
			if (i >= 0)
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
	else if ((ts->plus == 1 && ts->nil == 0 && ts->width == 0) ||
		(i < 0 && ts->nil == 0 && ts->width == 0))
	{
		//write(1, "douche!\n", 8);
		//if (il == f_len)
			f_len++;
		j = 0;
		if (i >= 0)
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
	else if (ts->plus == 0 && ts->space == 1 && ts->nil == 0 && ts->width == 0 && i >= 0)
	{
		if (il == f_len)
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
	else if ((ts->plus == 0 && ts->space == 1 && ts->min == 1 && ts->nil == 1 && i >= 0) 
		|| (ts->plus == 0 && ts->space == 1 && ts->min == 1 && ts->width != 0 && i >= 0))
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
		else if ((ts->plus == 0 && ts->space == 1 && ts->min == 0 && ts->nil == 1 && i >= 0) 
			|| (ts->plus == 0 && ts->space == 1 && ts->min == 0 && ts->width != 0 && i >= 0))
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

char	*print_unsigned(t_spec *ts, uintmax_t i, int fl)
{
	int j;
	int j1;
	char *fs;
	int il;
	int f_len;
	char *is;

	if (!fl)
		il = ft_nbrlen_u(i);
	else if (fl == 1)
		il = ft_strlen(is = ft_itoa_base_u(i, 8));
	else
		il = ft_strlen(is = ft_itoa_base_u(i, 16));
		//write(1, "douche1\n", 8);
	// ft_putnbr(il);
	// write(1, "\n", 1);
	f_len = max(il, ts->width);
	f_len = max(f_len, ts->prec);
	// ft_putstr(is);
	// write(1, "\n", 1);
	if (!fl)
		is = ft_itoa_base_u(i, 10);
	fs = (char *)ft_memalloc(f_len + 1);
	//ft_putstr(is);

	if (ts->dot == 1 && ts->prec == 0 && i == 0)
	{
		j = 0;
		if ((!ts->width && !ts->hash) || (!ts->width && ts->hash && fl != 1))
		{
			fs[0] = 0;
			return  (fs);
		}
		else
		{
			if (ts->hash && fl == 1)
				fs[j++] = '0';
			while (j < f_len)
			{
				fs[j] = ' ';
				j++;
			}
		}
	}
	else if (ts->min == 0 && ts->nil == 0 && ts->width == 0 && ts->prec == 0)
	{
		j = 0;
		if (ts->hash == 1 && fl == 2 && i != 0)
		{
			fs[j++] = '0';
			fs[j++] = 'X';
			il += 2;
		}
		else if (ts->hash == 1 && fl == 1 && i != 0)
		{
			fs[j++] = '0';
			il++;
		}
		j1 = 0;
		while (j < il)
			{
				fs[j] = is[j1];
				j++;
				j1++;
			}
			// ft_putstr(fs);
 		// 	write(1, "\n", 1);
	}
	else if (ts->nil == 1 && il < f_len && ts->min == 0)
	{
		j = 0;
		//write(1, "douche!\n", 8);
		// ft_putnbr(f_len);
		// write(1, "\n", 1);
		if ((int)ts->prec <= il)
		{
			while (j < f_len - max(max(il, ts->prec), ts->width))
			{
				fs[j] = ' ';
				j++;
			}
			if (ts->hash == 1 && fl == 2 && i != 0)
			{
				fs[j++] = '0';
				fs[j++] = 'X';
			}
			else if (ts->hash == 1 && fl == 1 && i != 0)
				fs[j++] = '0';
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
		else
		{
			while (j < f_len - (int)ts->prec)
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
	else if (ts->min == 1 && il < f_len)
	{
		j = 0;
		if ((int)ts->prec <= il)
		{
			j1 = 0;
			if (ts->hash == 1 && fl == 2 && i != 0)
			{
				fs[j++] = '0';
				fs[j++] = 'X';
				il += 2;
			}
			else if (ts->hash == 1 && fl == 1 && i != 0)
			{
				fs[j++] = '0';
				il++;
			}
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
			while (j < (int)(ts->prec - il))
			{
				fs[j] = '0';
				j++;
			}
			j1 = 0;
			//write(1, "douche!\n", 8);
			while (j < (int)ts->prec)
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
	else if (ts->min == 0 && ts->nil == 0)
	{
		j = 0;
		// write(1, "douche!\n", 8);
		// ft_putnbr(f_len);
		// write(1, "\n", 1);
		// ft_putnbr(il);
		// write(1, "\n", 1);
		if ((int)ts->prec <= il)
		{
			if (ts->hash == 1 && fl == 2)
				il += 2;
			else if (ts->hash == 1 && fl == 1)
				il++;
			while (j < f_len - il)
			{
				fs[j] = ' ';
				j++;
			}
			j1 = 0;
			if (ts->hash == 1 && fl == 2 && i != 0)
			{
				fs[j++] = '0';
				fs[j++] = 'X';
			}
			else if (ts->hash == 1 && fl == 1 && i != 0)
				fs[j++] = '0';
			while (j < f_len)
			{
				fs[j] = is[j1];
				j++;
				j1++;
			}
		}
		else
		{
			while (j < (int)(f_len - ts->prec))
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
		return (fs);
}

char	*print_char(t_spec *ts, char c)
{
	int len;
	int j;
	int j1;
	int f_len;
	char *fs;

	len = 1;
	f_len = max(len, ts->width);
	f_len = max(f_len, ts->prec);
	fs = (char *)ft_memalloc(f_len + 1);
	if (ts->min == 0)
	{
		j = 0;
		// write(1, "douche!\n", 8);
		// ft_putnbr(f_len);
		// write(1, "\n", 1);
		// ft_putstr(s);
		// write(1, "\n", 1);
		// ft_putnbr(il);
		// write(1, "\n", 1);
		if (ts->prec != 0 && ts->width != 0)
			f_len = max(ts->prec, ts->width);
		else if (ts->prec != 0)
			f_len = ts->prec;
		// write(1, "douche!\n", 8);
		// ft_putnbr(f_len);
		// write(1, "\n", 1);
		// ft_putstr(s);
		// write(1, "\n", 1);
		// ft_putnbr(il);
		// write(1, "\n", 1);
		if (ts->prec != 0)
		{
			if (ts->width != 0)
			{
				if (c)
					while (j < f_len - (int)ts->prec)
					{
						//write(1, "douche!\n", 8);
						fs[j] = ' ';
						j++;
					}
			}
			j1 = 0;
			// ft_putnbr(f_len);
			// write(1, "\n", 1);
			if (c)
				while (j < f_len)
				{
					fs[j] = c;
					j++;
					j1++;
				}
			else
			{
				if (f_len != (int)ts->prec)
					while (j < f_len)
					{
						fs[j] = ' ';
						j++;
					}
				fs[j++] = '^';
				fs[j] = '@';
			}

		}
		else
		{
			while (j < f_len - (int)len)
			{
				fs[j] = ' ';
				j++;
			}
			j1 = 0;
			if (c)
				while (j < f_len)
				{
					fs[j] = c;
					j++;
					j1++;
				}
			else
			{
				fs[j++] = '^';
				fs[j] = '@';
			}
		}
	}
	else if (ts->min == 1)
	{
		j = 0;
		if (ts->prec != 0 && ts->width != 0)
			f_len = max(ts->prec, ts->width);
		else if (ts->prec != 0)
			f_len = ts->prec;
		if (ts->prec != 0)
		{
			if (c)
			{
				j1 = 0;
				while (j < (int)ts->prec)
				{
					fs[j] = c;
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
				if (f_len != (int)ts->prec)
					while (j < f_len)
					{
						fs[j] = ' ';
						j++;
					}
				fs[j++] = '^';
				fs[j] = '@';
		}
		else
		{
			j1 = 0;
			if (c)
				while (j < len)
				{
					fs[j] = c;
					j++;
					j1++;
				}
			else
			{
				fs[j++] = '^';
				fs[j] = '@';
			}
			while (j < f_len)
			{
				fs[j] = ' ';
				j++;
			}
		}
	}
	return (fs);
}

char 	*handle_digit(va_list ap, t_spec *ts, char c)
{
	intmax_t i;
	char *fs;

	if (c == 'D')
		ts->l = 1;
	if (ts->l == 1)
		i = va_arg(ap, long int);
	else if (ts->ll == 1)
		i = va_arg(ap, long long int);
	else if (ts->h == 1)
		i = (short int)va_arg(ap, int);
	else if (ts->hh)
		i = (char)va_arg(ap, int);
	else if (ts->z == 1)
		i = (ssize_t)va_arg(ap, size_t);
	else if (ts->j == 1)
		i = va_arg(ap, intmax_t);
	else
		i = va_arg(ap, int);
	//printf("%jd\n", i);
	//printf("%s", is);
	//ft_putnbr(i);
	// ft_putstr(is);
	// write(1, "\n", 1);
	fs = handle_dig(ts, i);
	return (fs);
}

char 	*handle_string(va_list ap, t_spec *ts)
{
	char *fs;
	char *s;
	
	s = va_arg(ap, char *);
	//printf("%jd\n", i);
	//printf("%s", is);
	//ft_putnbr(i);
	// ft_putstr(is);
	// write(1, "\n", 1);
	if (!s)
		return (s);
	fs = handle_str(ts, s);
	return (fs);
}

char	*handle_char(va_list ap, t_spec *ts)
{
	char *fs;
	char c;
	
	c = (char)va_arg(ap, int);
	//printf("%jd\n", i);
	//printf("%s", is);
	//ft_putnbr(i);
	// ft_putstr(is);
	// write(1, "\n", 1);
	fs = print_char(ts, c);
	return (fs);
}

char	*handle_percent(t_spec *ts)
{
	char *fs;

	fs = print_char(ts, '%');
	return (fs);
}

char*	handle_unsigned(va_list ap, t_spec *ts, char c)
{
	char *fs;
	uintmax_t i;
	int j;

	j = 0;
	i = 0;
	if (c == 'U' || c == 'O')
		ts->l = 1;
	if (ts->l)
		i = va_arg(ap, unsigned long);
	else if (ts->ll)
		i = va_arg(ap, unsigned long long);
	else if (ts->h)
		i = (unsigned short)va_arg(ap, unsigned int);
	else if (ts->hh)
		i = (unsigned char)va_arg(ap, unsigned int);
	else if (ts->z)
		i = va_arg(ap, size_t);
	else if (ts->j)
		i = va_arg(ap, uintmax_t);
	else
		i = va_arg(ap, unsigned int);
	if (c == 'u' || c == 'U')
		fs = print_unsigned(ts, i, 0);
	else if (c == 'o' || c == 'O')
		fs = print_unsigned(ts, i, 1);
	else
		fs = print_unsigned(ts, i, 2);
	if (c == 'x')
		while(fs[j])
		{
			fs[j] = ft_tolower(fs[j]);
			j++;
		}
	return (fs);
}

char	*handle_pointer(va_list ap, t_spec *ts)
{
	char *fs;
	uintmax_t i;

	i = va_arg(ap, uintmax_t);
	ts->hash = 1;
	fs = print_unsigned(ts, i, 2);
	return (fs);
}

char	*print_format(va_list ap, t_spec *ts, char c)
{
	char *res;

	res = (char *)ft_memalloc(1);
 	if (c == 'd' || c == 'D' || c == 'i')
 		res = handle_digit(ap, ts, c);
 	else if (c == 'u' || c == 'U' || c == 'o' || c == 'O' || c == 'X' || c == 'x')
 		res = handle_unsigned(ap, ts, c);
 	else if (c == 'c')
 		res = handle_char(ap, ts);
 	else if (c == 's')
 	 	res = handle_string(ap, ts);
 	else if (c == 'p')
 		res = handle_pointer(ap, ts);
 	else if (c == '%')
 		res = handle_percent(ts);
	return (res);
}

t_spec 	*init_struct(t_spec *ts)
{
	ts->hash = 0;
	ts->min = 0;
	ts->space = 0;
	ts->plus = 0;
	ts->nil = 0;
	ts->dot = 0;
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
	{
		ts->dot = 1;
		i += parse_pres(&fmt[i + 1], ts) + 1;
	}
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

int		is_type(char c)
{
	int		i;
	char	*s = "psScCdDioOuUxX%";

	i = 0;
	while (s[i])
	{
		if (s[i++] == c)
			return (1);
	}
	return (0);
}

int		parse_format(va_list ap, char *fmt)
{
	//int d, 
	int i, j, len;
	//char c, 
	char *s;
	char *out;
	t_spec *ts;

	i = 0;
	j = 0;
	len = 0;
	//d = va_arg(ap, int);
	ts = (t_spec *)malloc(sizeof(t_spec));
	out = (char *)ft_memalloc(1);
	while (fmt[i])
	{
		if (fmt[i] == '%' && fmt[i + 1])
		{
			//s = ft_strsub(fmt, j, i - j);
			//out = ft_strjoin(out, s);
			i++;
			i += parse_spec(&fmt[i], ts);
			// write(1, &fmt[i], 1);
			// write(1, "\n", 1);
			if (is_type(fmt[i]))
			{
				s = print_format(ap, ts, fmt[i]);
				if (!s)
					s = ft_strdup("(null)");
				ft_putstr(s);
				j += ft_strlen(s);
				if (s[ft_strlen(s) - 1] == '@' && s[ft_strlen(s) - 2] == '^')
					j--;
			}
			else
			{
				write(1, &fmt[i], 1);
				j++;
			}
			//out = ft_strjoin(out, s);
			//j = i + 1;
			//print_struct(ts);
		}
		else if (fmt[i] != '%')
		{
			write(1, &fmt[i], 1);
			j++;
		}
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
	return (j);
}


int	ft_printf(char *fmt, ...)
{
	va_list ap;
	char* res;
	int n;

	res = fmt;
	va_start(ap, fmt);
	n = parse_format(ap, fmt);
	va_end(ap);
	return (n);
}

// int main()
// {
// 	int i = 4;
// 	int n = printf("%p", &i);
// 	//ft_printf("%.4s", "42");
// 	//ft_printf("%5.2s is a string", "this"); 
// 	//ft_printf("%.2s is a string", "");
// 	//ft_printf("%U", 4294967296);  
// 	// ft_printf("%U", 4294967295);
// 	//ft_printf("%.2s is a string", ""); 
// 	//ft_printf("%-5%");
// 	//ft_printf("%5%");
// 	//ft_printf("%#08x", 42);
// 	//ft_printf("%#6o", 2500);
// 	//ft_printf("%#X", 42);
// 	//ft_printf("%#x", 0);
// 	//ft_printf("%X", -42);
// 	//ft_printf("%#08x", 42);
// 	//ft_printf("%#-8x", 42);
// 	//ft_printf("%-+8.4d", 42);
// 	//ft_printf("%10x", 42);
// 	//ft_printf("%2c", 0); 
// 	//ft_printf("%5c", 42);
// 	//ft_printf("%-.2s is a string", "");
// 	//ft_printf("%-.2s is a string", "this");
// 	//ft_printf("%5.5s is a string", "");
// 	//ft_printf("%.2s is a string", "this");
// 	//ft_printf("%10s is a string", "this");
// 	//ft_printf("%5d", 42);
// 	//ft_printf("%s", "abc");
// 	//ft_printf("%0+5d", 42);
// 	//ft_printf("@moulitest: %5.d %5.0d", 0, 0); 
// 	//int n = ft_printf("%jd", 9223372036854775807);
// 	//int n = ft_printf("%zd", 4294967295);
// 	//int n = ft_printf("%++d", 42);
// 	//int n = ft_printf("My_printf: |%+011.8zd| %%!", -567);
// 	printf("\n\t%d\t\n", n);
// 	//write(1, "\n", 1);
// 	//printf("%-+8d", 1234);
// 	n = printf("%p", &i);
// 	//printf("DefPrintf: |%+011.8zd| %%!", (ssize_t)-567);
// 	printf("\n\t%d\t\n", n);
// 	printf("\n");
// 	//printf("%+07.5d", 1234);
// 	return (0);
// }

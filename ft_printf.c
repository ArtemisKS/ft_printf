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
#include <locale.h>

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

char	*handle_str(t_spec *ts, char *s, char c, int *ia)
{
	int j;
	int j1;
	char *fs;
	int il;
	int f_len;
	char *is;

	if (s)
	{
		il = ft_strlen(s);
		//f_len = max(f_len, ts->prec);
		is = ft_strdup(s);
	}
	else
	{
		il = 0;
		is = ft_strdup("");
	}
	if (ts->asterisk2 && ts->min && (int)ts->prec > il)
		ts->prec = 0;
	f_len = max(il, ts->width);
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
				j1 = 0;
				int n = 0;
				int cnt = 0;
				int n_sum = 0;
				if (c == 's')
					while (j < (int)ts->prec && j1 < (int)ft_strlen(is))
					{
						fs[j++] = is[j1];
						j1++;
					}
					// write(1, "precision :\n", 11);
					// ft_putnbr(f_len);
					// write(1, "\n", 1);
				else if (c == 'S')
					while (j < (int)ts->prec)
					{
						n_sum += ia[n];
						if (n_sum > (int)ts->prec)
							break ;
						while (cnt < ia[n] && j1 < (int)ft_strlen(is))
						{
							fs[j++] = is[j1];
							j1++;
							cnt++;
							// if (j == (int)ts->prec - 1)
							// 	break ;
						}
						// if (j == (int)ts->prec - 1)
						// 		break ;
						n++;
						cnt = 0;
					}
				while (j < f_len && il != 0)
					fs[j++] = ' ';
				if (f_len != (int)ts->prec)
					while (j < f_len)
						fs[j++] = ' ';
					// write(1, "j :\n", 4);
					// ft_putnbr(j);
					// write(1, "\n", 1);
		}
		else
		{
			j1 = 0;
			while (j < il && j1 < (int)ft_strlen(is))
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
		j1 = 0;
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
				// ft_putnbr(f_len);
				// write(1, "\n", 1);
				f_len = max(ts->width, il);
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
			if (!ts->prec)
			{
				if (!ts->dot)
				{
					while (j < f_len - (int)il)
					{
						fs[j] = ' ';
						j++;
					}
					while (j < f_len && j1 < (int)ft_strlen(is))
					{
						fs[j] = is[j1];
						j++;
						j1++;
					}
				}
				else if (ts->dot && ft_strcmp(is, "^@"))
					while (j < (int)ts->width)
						fs[j++] = ' ';
				else
					fs = ft_strdup(is);
			}
			else
			{
				int n = 0;
				int cnt = 0;
				int n_sum = 0;
				if (ts->width)
				{
					int fl;

					fl = 0;
					f_len = max(ts->prec, ts->width);
					while (j < f_len - (int)ts->prec)
					{
						fs[j] = ' ';
						j++;
					}
					if (c == 's')
						while (j < f_len && j1 < (int)ft_strlen(is))
						{
							fs[j] = is[j1];
							j++;
							j1++;
						}
					else if (c == 'S')
					{
						while (ia[n])
						{
							n_sum += ia[n];
							// write(1, "n-sum :\n", 8);
							// ft_putnbr(n_sum);
							// write(1, "\n", 1);
							if (n_sum == (int)ts->prec)
								fl = 1;
							else if (n_sum > (int)ts->prec)
							{
								n_sum -= (int)ts->prec;
								break ;
							}
							n++;
						}
						n = 0;
						while (!fl && n++ < n_sum)
							fs[j++] = ' ';
						n = 0;
						n_sum = 0;
						while (j < f_len && j1 < (int)ft_strlen(is))
						{
							n_sum += ia[n];
							if (n_sum > (int)ts->prec)
							{
								while (j < f_len)
									fs[j++] = ' ';
								break ;
							}
							while (cnt < ia[n])
							{
								fs[j++] = is[j1];
								j1++;
								cnt++;
							}
							n++;
							cnt = 0;
						}
					}
				}
				else
				{
					if (c == 's')
						while (j < (int)ts->prec && j1 < (int)ft_strlen(is))
						{
							fs[j] = is[j1];
							j++;
							j1++;
						}
					else if (c == 'S')
						// while (j < (int)ts->prec)
						// {
						// 	while (cnt < ia[n])
						// 	{
						// 		fs[j++] = is[j1];
						// 		j1++;
						// 		if (j == (int)ts->prec - 1)
						// 			break ;
						// 	}
						// 	if (j == (int)ts->prec - 1)
						// 			break ;
						// 	n++;
						// 	cnt = 0;
						// }
						while (j < (int)ts->prec)
						{
							n_sum += ia[n];
							if (n_sum > (int)ts->prec)
							{
								while (j++ < f_len)
									;
								break ;
							}
							while (cnt < ia[n])
							{
								fs[j++] = is[j1];
								j1++;
								cnt++;
								// if (j == (int)ts->prec - 1)
								// 	break ;
							}
							// if (j == (int)ts->prec - 1)
							// 		break ;
							n++;
							cnt = 0;
						}
				}
			}
		}
	}
	else if (ts->min == 0 && ts->nil == 1)
	{
		j = 0;
		j1 = 0;
		if (ts->prec != 0 && ts->width != 0)
			f_len = max(ts->prec, ts->width);
		else if (ts->prec != 0)
			f_len = ts->prec;
		// if (ts->prec != 0 && ts->width != 0)
		// 	f_len = max(ts->prec, ts->width);
		// else if (ts->prec != 0)
		// 	f_len = ts->prec;
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
			if (ts->width != 0)
			{
				// ft_putnbr(f_len);
				// write(1, "\n", 1);
				while (j < f_len - (int)ts->prec)
						fs[j++] = '0';
				while (j < f_len - il)
					fs[j++] = '0';
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
						fs[j] = '0';
						j++;
					}
			}
		}
		else
		{
			if (!ts->prec)
			{
				if (!ts->dot)
				{
					while (j < f_len - (int)il)
					{
						fs[j] = '0';
						j++;
					}
					while (j < f_len && j1 < (int)ft_strlen(is))
					{
						fs[j] = is[j1];
						j++;
						j1++;
					}
				}
				else if (ts->dot && ft_strcmp(is, "^@"))
					while (j < (int)ts->width)
						fs[j++] = '0';
				else
					fs = ft_strdup(is);
			}
			else
			{
				int n = 0;
				int cnt = 0;
				int fl = 0;
				int n_sum = 0;
				if (ts->width)
				{
					while (j < f_len - (int)ts->prec)
					{
						fs[j] = '0';
						j++;
					}
					if (c == 's')
						while (j < f_len && j1 < (int)ft_strlen(is))
						{
							fs[j] = is[j1];
							j++;
							j1++;
						}
					else if (c == 'S')
					{
						// while (ia[n])
						// 	if (ia[n++] == 1)
						// 		fl = 1;
						// if (ts->width > ts->prec && !fl)
						// 		fs[j++] = '0';
						// 	fl = 0;
						// while (j < f_len && j1 < (int)ft_strlen(is))
						// {
						// 	while (cnt < ia[n])
						// 	{
						// 		fs[j] = is[j1];
						// 		j1++;
						// 		cnt++;
						// 		if (j == f_len - 1)
						// 		{
						// 			fl = 1;
						// 			break ;
						// 		}
						// 		j++;
						// 	}
						// 	if (fl)
						// 			break ;
						// 	n++;
						// 	cnt = 0;
						// }
						// write(1, "precision :\n", 11);
						// ft_putnbr(ts->prec);
						// write(1, "\n", 1);
						while (ia[n])
						{
							n_sum += ia[n];
							// write(1, "n-sum :\n", 8);
							// ft_putnbr(n_sum);
							// write(1, "\n", 1);
							if (n_sum == (int)ts->prec)
								fl = 1;
							else if (n_sum > (int)ts->prec)
							{
								n_sum -= (int)ts->prec;
								break ;
							}
							n++;
						}
						n = 0;
						while (!fl && n++ < n_sum)
							fs[j++] = '0';
						n = 0;
						n_sum = 0;
						while (j < f_len && j1 < (int)ft_strlen(is))
						{
							n_sum += ia[n];
							if (n_sum > (int)ts->prec)
							{
								while (j < f_len)
									fs[j++] = ' ';
								break ;
							}
							while (cnt < ia[n])
							{
								fs[j++] = is[j1];
								j1++;
								cnt++;
							}
							n++;
							cnt = 0;
						}
					}
				}
				else
				{
					if (c == 's')
						while (j < (int)ts->prec && j1 < (int)ft_strlen(is))
						{
							fs[j] = is[j1];
							j++;
							j1++;
						}
					else if (c == 'S')
						// while (j < (int)ts->prec)
						// {
						// 	while (cnt < ia[n])
						// 	{
						// 		fs[j++] = is[j1];
						// 		j1++;
						// 		if (j == (int)ts->prec - 1)
						// 			break ;
						// 	}
						// 	if (j == (int)ts->prec - 1)
						// 			break ;
						// 	n++;
						// 	cnt = 0;
						// }
						while (j < (int)ts->prec)
						{
							n_sum += ia[n];
							if (n_sum > (int)ts->prec)
							{
								while (j++ < f_len)
									;
								break ;
							}
							while (cnt < ia[n])
							{
								fs[j++] = is[j1];
								j1++;
								cnt++;
								// if (j == (int)ts->prec - 1)
								// 	break ;
							}
							// if (j == (int)ts->prec - 1)
							// 		break ;
							n++;
							cnt = 0;
						}
				}
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
	if (ts->asterisk2 && ts->min && (int)ts->prec > il)
	{
		ts->prec = 0;
		if (ts->nil)
			ts->min = 0;
	}
	f_len = max(il, ts->width);
	f_len = max(f_len, ts->prec);
	// ft_putstr(is);
	//write(1, "\n", 1);
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
		// if ((int)ts->prec <= il)
		// {
		// 	// while (j < f_len - max(max(il, ts->prec), ts->width))
		// 	// {
		// 	// 	fs[j] = ' ';
		// 	// 	j++;
		// 	// }

		// 	while (j < f_len - il)
		// 	{
		// 		fs[j] = '0';
		// 		j++;
		// 	}
		// 	j1 = 0;
		// 	while (j < f_len && j1 < (int)ft_strlen(is))
		// 	{
		// 		fs[j] = is[j1];
		// 		j++;
		// 		j1++;
		// 	}
		// }
		// else
		// {
			if ((int)ts->prec >= il)
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
			while (j < f_len && j1 < (int)ft_strlen(is))
			{
				fs[j] = is[j1];
				j++;
				j1++;
			}
		//}
	}
	else if (ts->min == 1 && ts->plus == 0 && ts->space == 0 && i >= 0)
	{
		j = 0;
		if ((int)ts->prec <= il)
		{
			j1 = 0;
			//write(1, "douche!\n", 8);
			while (j < il && j1 < (int)ft_strlen(is))
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
			while (j < (int)ts->prec && j1 < (int)ft_strlen(is))
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
			while (j < f_len && j1 < (int)ft_strlen(is))
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
			while (j < f_len && j1 < (int)ft_strlen(is))
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
		// ft_putnbr(f_len);
		// write(1, "\n", 1);
		if (ts->prec != 0)
		{
			//write(1, "douche!\n", 8);
			if (ts->prec > ts->width)
				f_len++;
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
			while (j < f_len && j1 < (int)ft_strlen(is))
			{
				fs[j] = is[j1];
				j++;
				j1++;
			}
			while (fs[j] != ' ' && j-- >= -1)
				;
			// if (j == 0)
			// {
			// 	char *s;
			// 	s = ft_strdup(fs);
			// 	if (i >= 0)
			// 		fs[j++] = '+';
			// 	else 
			// 		fs[j++] = '-';
			// 	while (fs[j])
			// 	{
			// 		fs[j] = s[j - 1];
			// 		j++;
			// 	}
			// }
			// ft_putnbr(j);
			// write(1, "\n", 1);
			if (i >= 0)
				fs[j] = '+';
			else 
				fs[j] = '-';
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
			while (j < f_len && j1 < (int)ft_strlen(is))
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
		if ((int)ts->width < f_len)
			f_len++;
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
			while (j < f_len && j1 < (int)ft_strlen(is))
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
			while (j < f_len && j1 < (int)ft_strlen(is))
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
			while (j < (int)(ts->prec + 1) && j1 < (int)ft_strlen(is))
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
			while (j1 < il && j1 < (int)ft_strlen(is))
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
		while (j < f_len && j1 < (int)ft_strlen(is))
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
		while (j < f_len && j1 < (int)ft_strlen(is))
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
			while (j < f_len - (max(il, ts->prec) - min(il, ts->prec)) && j1 < (int)ft_strlen(is))
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
			while (j1 < il && j < f_len)
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
				while (j < f_len && j1 < (int)ft_strlen(is))
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
				while (j < f_len - il && ts->nil)
				{
					fs[j] = '0';
					j++;
				}
				while (j < f_len - il && !ts->nil)
				{
					fs[j] = ' ';
					j++;
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
		while (j < il && j1 < (int)ft_strlen(is))
			{
				fs[j] = is[j1];
				j++;
				j1++;
			}
			// ft_putstr(fs);
 		// 	write(1, "\n", 1);
	}
	else if (ts->nil == 1 && ts->min == 0)
	{
		j = 0;
		//write(1, "douche!\n", 8);
		// ft_putnbr(f_len);
		// write(1, "\n", 1);
		if ((int)ts->prec <= il)
		{
			// while (j < f_len - max(max(il, ts->prec), ts->width))
			// {
			// 	fs[j] = ' ';
			// 	j++;
			// }
			if (ts->hash == 1 && fl == 2 && i != 0)
			{
				fs[j++] = '0';
				fs[j++] = 'X';
				if ((int)ts->width < il)
					f_len += 2;
			}
			else if (ts->hash == 1 && fl == 1 && i != 0)
			{
				fs[j++] = '0';
				if ((int)ts->width < il)
					f_len++;
			}
			while (j < f_len - il)
			{
				fs[j] = '0';
				j++;
			}
			// ft_putnbr(f_len);
			// write(1, "\n", 1);
			j1 = 0;
			while (j < f_len && j1 < (int)ft_strlen(is))
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
			while (j < f_len && j1 < (int)ft_strlen(is))
			{
				fs[j] = is[j1];
				j++;
				j1++;
			}
		}
	}
	else if (ts->min == 1)
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
			while (j < il && j1 < (int)ft_strlen(is))
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
			while (j < (int)ts->prec && j1 < (int)ft_strlen(is))
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
			while (j < f_len && j1 < (int)ft_strlen(is))
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
			if (ts->hash == 1 && fl == 2 && i != 0)
			{
				fs[j++] = '0';
				fs[j++] = 'X';
				f_len += 2;
			}
			else if (ts->hash == 1 && fl == 1 && i != 0)
			{
				fs[j++] = '0';
				//f_len++;
			}
			while (j < f_len - il)
			{
				fs[j] = '0';
				j++;
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

char	*print_char(t_spec *ts, char *s)
{
	int len;
	int j;
	int j1;
	int f_len;
	char *fs;

	len = ft_strlen(s);
	if (!s[0])
		len = 1;
	f_len = max(len, ts->width);
	//f_len = max(f_len, ts->prec);
	fs = (char *)ft_memalloc(f_len + 1);
	// write(1, &c, 1);
	// write(1, "\n", 1);
	if (ts->min == 0 && ts->nil == 0)
	{
		j = 0;
		// if (ts->prec != 0 && ts->width != 0)
		// 	f_len = max(ts->prec, ts->width);
		// else if (ts->prec != 0)
		// 	f_len = ts->prec;
		// write(1, "douche!\n", 8);
		// ft_putnbr(f_len);
		// write(1, "\n", 1);
		// ft_putstr(s);
		// write(1, "\n", 1);
		// ft_putnbr(il);
		// write(1, "\n", 1);
		if (ts->prec)
		{
			if (ts->width)
			{
				if (s[0])
				{
					if (!s[1])
						while (j < f_len - (int)ts->prec)
						{
							//write(1, "douche!\n", 8);
							fs[j] = ' ';
							j++;
						}
					else
						while (j < f_len - (int)ft_strlen(s))
						{
							fs[j] = ' ';
							j++;
						}
				}
			}
			j1 = 0;
			// ft_putnbr(f_len);
			// write(1, "\n", 1);
			if (s[0])
				while (j < f_len && j1 < (int)ft_strlen(s))
				{
					fs[j] = s[j1];
					j++;
					j1++;
				}
			else
			{
				// if (f_len != (int)ts->prec)
				// 	while (j < f_len)
				// 	{
				// 		fs[j] = ' ';
				// 		j++;
				// 	}
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
			if (s[0])
				while (j < f_len && j1 < (int)ft_strlen(s))
				{
					fs[j] = s[j1];;
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
	else if (ts->min == 0 && ts->nil == 1)
	{
		j = 0;
		// if (ts->prec != 0 && ts->width != 0)
		// 	f_len = max(ts->prec, ts->width);
		// else if (ts->prec != 0)
		// 	f_len = ts->prec;
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
				if (s[0])
				{
					if (!s[1])
						while (j < f_len - (int)ts->prec)
						{
							//write(1, "douche!\n", 8);
							fs[j] = '0';
							j++;
						}
					else
						while (j < f_len - (int)ft_strlen(s))
						{
							fs[j] = '0';
							j++;
						}
				}
			}
			j1 = 0;
			// ft_putnbr(f_len);
			// write(1, "\n", 1);
			if (s[0])
				while (j < f_len && j1 < (int)ft_strlen(s))
				{
					fs[j] = s[j1];;
					j++;
					j1++;
				}
			else
			{
				if (f_len != (int)ts->prec)
					while (j < f_len)
					{
						fs[j] = '0';
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
				fs[j] = '0';
				j++;
			}
			j1 = 0;
			if (s[0])
				while (j < f_len && j1 < (int)ft_strlen(s))
				{
					fs[j] = s[j1];;
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
		// if (ts->prec != 0 && ts->width != 0)
		// 	f_len = max(ts->prec, ts->width);
		// else if (ts->prec != 0)
		// 	f_len = ts->prec;
		if (ts->prec != 0)
		{
			if (s[0])
			{
				j1 = 0;
				if (!s[1])
					while (j < (int)ts->prec && j1 < (int)ft_strlen(s))
					{
						fs[j] = s[j1];
						j++;
						j1++;
					}
				else
					while (j < f_len && j1 < (int)ft_strlen(s))
					{
						fs[j] = s[j1];
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
			j1 = 0;
			if (s[0])
				while (j < f_len && j1 < (int)ft_strlen(s))
				{
					fs[j] = s[j1];;
					j++;
					j1++;
				}
			else
			{
				fs[j++] = '^';
				fs[j++] = '@';
			}
			while (j < f_len)
				fs[j++] = ' ';
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
		i = va_arg(ap, ssize_t);
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

int		size_bin(int value)
{
	char *vbin;
	int len;

	vbin = ft_itoa_base(value, 2);
	//ft_putstr(vbin);
	//write(1, "\n", 1);
	len = ft_strlen(vbin);
	return (len);
}

char	*print_unicode(int value, int *ia, int i)
{
	//unsigned int mask0 = 0;
	unsigned int mask1 = 49280;
	unsigned int mask2 = 14712960;
	unsigned int mask3 = 4034953344;
 

 	unsigned int v = value;
	int size = size_bin(value);
	//int res = 0;
	//printf("size %d\n", size);
	unsigned char octet;
	char *res;

if (size <= 7)
	{
		//write(1, "erg", 3);
		octet = value;
		res = (char *)ft_memalloc(2);
		res[0] = octet;
		ia[i]++;
		res[1] = 0;
		//write(1, &octet, 1);
		return (res);
	}
	else  if (size <= 11)
	{
		//write(1, "erg", 3);
		unsigned char o2 = (v << 26) >> 26; // Восстановление первых 6 бит 110xxxxx 10(xxxxxx)
		unsigned char o1 = ((v >> 6) << 27) >> 27; // Восстановление последних 5 бит 110(xxxxx) 10xxxxxx
       
		octet = (mask1 >> 8) | o1; // Применение первой битовой маски ко первому байту
		res = (char *)ft_memalloc(3);
		res[0] = octet;
		ia[i]++;
		//write(1, &octet, 1);
		octet = ((mask1 << 24) >> 24) | o2; // Применение второй битовой маски ко второму байту
		res[1] = octet;
		ia[i]++;
		res[2] = 0;
		//write(1, &octet, 1);
		return (res);
		//write(1, "\n", 1);
	}
	else  if (size <= 16)
	{
		//write(1, "erg", 3);
		unsigned char o3 = (v << 26) >> 26; // Восстановление первых 6 бит 1110xxxx 10xxxxxx 10(xxxxxx)
		unsigned char o2 = ((v >> 6) << 26) >> 26; // Восстановление вторых 6 бит 1110xxxx 10(xxxxxx) 10xxxxxx
		unsigned char o1 = ((v >> 12) << 28) >> 28; // Восстановление последних 4 бит 1110(xxxx) 10xxxxxx 10xxxxxx
       
		octet = (mask2 >> 16) | o1; // Применение первой битовой маски ко первому байту
		res = (char *)ft_memalloc(4);
		res[0] = octet;
		ia[i]++;
		//write(1, &octet, 1);
		octet = ((mask2 << 16) >> 24) | o2; // Применение второй битовой маски ко второму байту
		res[1] = octet;
		ia[i]++;
		//write(1, &octet, 1);
		octet = ((mask2 << 24) >> 24) | o3; // Применение третьей битовой маски ко третьему байту
		res[2] = octet;
		ia[i]++;
		res[3] = 0;
		return (res);
		//write(1, &octet, 1);
		//write(1, "\n", 1);
	}
	else
	{
		//write(1, "erg", 3);
		unsigned char o4 = (v << 26) >> 26; // Восстановление первых 6 11110xxx 10xxxxxx 10xxxxxx 10(xxxxxx)
		unsigned char o3 = ((v >> 6) << 26) >> 26; // Восстановление вторых 6 бит 11110xxx 10xxxxxx 10(xxxxxx) 10xxxxxx
		unsigned char o2 = ((v >> 12) << 26) >> 26;  // Восстановление третьих 6 бит bits 11110xxx 10(xxxxxx) 10xxxxxx 10xxxxxx
		unsigned char o1 = ((v >> 18) << 29) >> 29; // Восстановление последних 3 бита 11110(xxx) 10xxxxxx 10xxxxxx 10xxxxxx
       
		octet = (mask3 >> 24) | o1; // Применение бит первого байта на первый байт маски
		res = (char *)ft_memalloc(5);
		res[0] = octet;
		ia[i]++;
		//write(1, &octet, 1);
		octet = ((mask3 << 8) >> 24) | o2; // Применение второй битовой маски ко второму байту
		//write(1, &octet, 1);
		res[1] = octet;
		ia[i]++;
		octet = ((mask3 << 16) >> 24) | o3; // Применение третьей битовой маски ко третьему байту
		res[2] = octet;
		ia[i]++;
		//write(1, &octet, 1);
		octet = ((mask3 << 24) >> 24) | o4; // Применение последней битовой маски ко последнему байту
		//write(1, &octet, 1);
		res[3] = octet;
		ia[i]++;
		res[4] = 0;
		return (res);
		//write(1, "\n", 1);
	}
}


char 	*handle_string(va_list ap, t_spec *ts, char c)
{
	char *fs;
	char *s;
	wchar_t *wa;
	int i;
	int ia[100];

	i = 0;
	while (i < 100)
		ia[i++] = 0;
	i = 0;
	s = (char *)ft_memalloc(1);
	if (c == 's' && !ts->l)
		s = va_arg(ap, char *);
	if (c == 'S' || ts->l)
	{
		wa = va_arg(ap, wchar_t *);
		if (wa)
		{
			while (wa[i])
			{
				s = ft_strjoin(s, print_unicode(wa[i], ia, i));
				i++;
			}
			fs = handle_str(ts, s, 'S', ia);
		}
		else
			s = NULL;
	}
	//printf("%jd\n", i);
	//printf("%s", is);
	//ft_putnbr(i);
	// ft_putstr(is);
	// write(1, "\n", 1);
	if (!s && !ts->nil && !ts->min)
		return (s);
	if (c == 's')
		fs = handle_str(ts, s, 's', ia);
	return (fs);
}

char	*handle_char(va_list ap, t_spec *ts, char c)
{
	char *fs;
	int value;
	int ia[100];
	int i;

	i = 0;
	while (i < 100)
		ia[i++] = 0;
	value = 0;
	fs = ft_strnew(1);
	if (c == 'c' && !ts->l)
	{
		fs[0] = (char)va_arg(ap, int);
		fs = print_char(ts, fs);
	}
	if (c == 'C' || ts->l)
	{
		value = va_arg(ap, int);
		fs = print_unicode(value, ia, i);
		if (!fs[0])
			fs = ft_strdup("^@");
		fs = print_char(ts, fs);
	}
	//printf("%jd\n", i);
	//printf("%s", is);
	//ft_putnbr(i);
	// ft_putstr(fs);
	// write(1, "\n", 1);
	return (fs);
}

char	*handle_percent(t_spec *ts)
{
	char *fs;

	fs = ft_strdup("%");
	fs = print_char(ts, fs);
	return (fs);
}

char	*ft_lower(char *fs)
{
	int j;
	j = 0;
	while(fs[j])
		{
			fs[j] = ft_tolower(fs[j]);
			j++;
		}
	return (fs);
}

char	*handle_unsigned(va_list ap, t_spec *ts, char c)
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
		fs = ft_lower(fs);
	return (fs);
}

char	*point_at_beg(char *fs, t_spec *ts)
{
	int i;
	int j;
	int fl;

	j = 0;
	i = 0;
	while (fs[i++] == '0')
		j++;
	i = 0;
	//if ((int)ts->width == j)
		//fl = ts->width;
	fl = max(ts->prec, ts->width);
	if (fl == (int)ts->prec)
		fl += 2;
	//if (fl == (int)ts->prec)
		//fl += 2;
	fs = ft_strnew(fl);
	// ft_putnbr(fl);
	// write(1, "\n", 1);
	while (i < fl)
	{
		if (i == 0)
			fs[i] = '0';
		else if (i == 1)
			fs[i] = 'x';
		else if (i > 1 && j)
			fs[i] = '0';
		else if (i > 1)
			fs[i] = ' ';
		if (fs[i] == '0' && i != 0)
			j--;
		i++;
	}
	return (fs);
}

char	*cor_pointer(char *fs, t_spec *ts)
{
	int i;

	i = 0;
	if (!ft_strchr(fs, 'x'))
	{
		while (fs[i])
		{
			if (fs[i] == '0')
				break ;
			i++;
		}
		if (i == (int)ft_strlen(fs) - 1 && !fs[i + 1])
			fs = ft_strjoin(fs, "x0");
		else if (fs[0] == 0)
			fs = ft_strdup("0x");
		else if (i == 0)
			fs = point_at_beg(fs, ts);
		else if (fs[i + 1] && fs[i + 2])
		{
			fs[i + 1] = 'x';
			fs[i + 2] = '0';
		}
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
	fs = ft_lower(fs);
	fs = cor_pointer(fs, ts);
	return (fs);
}

char	*print_format(va_list ap, t_spec *ts, char c)
{
	char *res;

	res = ft_strnew(1);
 	if (c == 'd' || c == 'D' || c == 'i')
 		res = handle_digit(ap, ts, c);
 	else if (c == 'u' || c == 'U' || c == 'o' || c == 'O' || c == 'X' || c == 'x')
 		res = handle_unsigned(ap, ts, c);
 	else if (c == 'c' || c == 'C')
 		res = handle_char(ap, ts, c);
 	else if (c == 's' || c == 'S')
 	 	res = handle_string(ap, ts, c);
 	else if (c == 'p')
 		res = handle_pointer(ap, ts);
 	else if (c == '%')
 		res = handle_percent(ts);
 	else
 	{
 		res[0] = c;
 		res = print_char(ts, res);
 	}
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
	ts->asterisk1 = 0;
	ts->asterisk2 = 0;
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

int		parse_spec(char *fmt, t_spec *ts, va_list ap)
{
	int i;
	int tmp;

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
	if (fmt[i] == '*')
	{
		if ((tmp = va_arg(ap, int)) < 0)
		{
				ts->width = tmp * -1;
				ts->min = 1;
		}
		else
			ts->width = tmp;
		ts->asterisk1 = 1;
		i++;
	}
	else
		i += parse_width(&fmt[i], ts);
	// write(1, &fmt[i], 1);
	// write(1, "\n", 1);
	if (fmt[i] == '*')
		{
			if ((tmp = va_arg(ap, int)) < 0)
			{
				ts->width = tmp * -1;
				ts->min = 1;
			}
			else
				ts->width = tmp;
			ts->asterisk1 = 1;
			i++;
		}
	else if (fmt[i] >= '0' && fmt[i] <= '9')
		i += parse_width(&fmt[i], ts);
	if (fmt[i] == '.')
	{
		ts->dot = 1;
		if (fmt[++i] == '*')
		{
			if ((tmp = va_arg(ap, int)) < 0)
			{
				ts->prec = tmp * -1;
				ts->min = 1;
			}
			else
				ts->prec = tmp;
			ts->asterisk2 = 1;
			i++;
		}
		else
			i += parse_pres(&fmt[i], ts);
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

int	str_zero(char *fs)
{
	int i;

	i = 0;
	while (fs[i])
	{
		if (fs[i] == '^' && fs[i + 1] && fs[i + 1] == '@')
			write(1, "", 1);
		else if (fs[i] == '@' && !fs[i + 1])
			return (i);
		else if (fs[i] == '@' && fs[i - 1] && fs[ i - 1] == '^')
			write(1, " ", 1);
		else
			write(1, &fs[i], 1);
		i++;
	}
	return (i);
}

int		parse_format(va_list ap, char *fmt)
{
	//int d, 
	int i, j, k;
	//char c, 
	char *s;
	char *out;
	t_spec *ts;

	i = 0;
	j = 0;
	int fl = 0;
	k = 0;
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
			i += parse_spec(&fmt[i], ts, ap);
			// write(1, &fmt[i], 1);
			// write(1, "\n", 1);
			if ((is_type(fmt[i])) || (!(is_type(fmt[i])) && 
				(ts->nil || ts->min || ts->width || ts->prec)))
			{
				s = print_format(ap, ts, fmt[i]);
				if (!s)
					s = ft_strdup("(null)");
				while (s[k])
				{
					if (s[k] == '^' && s[k + 1] && s[k + 1] == '@')
					{
						fl = 1;
						j += str_zero(s);
						break ;
					}
					k++;
				}
				//if (fmt[i] != 'C' && fmt[i] != 'S')
				if (!fl)
				{
					j += ft_strlen(s);
					ft_putstr(s);
				}
				fl = 0;
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
// 	setlocale(LC_ALL, "en_US.UTF-8");
// 	int strlen = 4;
// 	int	x = L'ÁM-^L´';
// 	int n = ft_printf("%C, %-13.8S", 0, L"米фып");
// 	//ft_printf("%C, %-20.9s", 0, "douche1docuhe2");
// 	//ft_printf("%C, %-5.9S", 0, L"米фып");
// 	//ft_printf("%-015.5S", L"Темкаитемкаитемкаитемка");
// 	//ft_printf("%015.5s", "o[jasrgjajfdohssdjfghjodihjdgodghgdhdshfgih");
// 	//ft_printf("%4.16S", L"Темкаитемкаитемкаитемка");
// 	//ft_printf("{%*3d}", 0, 0);
// 	//ft_printf("{%.*s}", -5, "42");
// 	//ft_printf("{%.*d}", -5, 42);
// 	//ft_printf("%+c", 0);
// 	//ft_printf("%*c", -15, 0);
// 	//ft_printf("{%*d}", 5, 42);
// 	//ft_printf("%4.3S", L"ыambon");
// 	//ft_printf("%lc, %lc", L'ÊM-^ZM-^V', L'ÿ≠');
// 	//ft_printf("{%05.S}", L"42 c est cool");
// 	//ft_printf("%hhC, %hhC", 0, L'Á±≥');
// 	//ft_printf("%lc, %lc", L'ÊM-^ZM-^V', L'ÿ≠');
// 	//ft_printf("% 4i", 42);
// 	//ft_printf("|%.10S|", L"ÊM-M-^QÊM-^XØ‰∏M-ÂM-^O™ÁM-^L´„M-M-^B");
// 	//ft_printf("{%-15p}", 0);
// 	//ft_printf("%.5p", 0);
// 	//ft_printf("{%05p}", &strlen);
// 	//ft_printf("%#08x", 42);
// 	//ft_printf("%C", x);
// 	//ft_printf("%C", 0);
// 	//ft_printf("%.5p", 0);
// 	//ft_printf("%.p, %.0p", 0, 0);
// 	//ft_printf("{%-15p}", 0);
// 	// int i[2] = {206, 177};
// 	// write(1, &(i[0]), 1);
// 	// write(1, &(i[1]), 1);
// 	//ft_printf("%4.15s", "I am 42");
// 	//ft_printf("%4.15s", "42 is the answer");
// 	//ft_printf("%4.15s", "42");
// 	//ft_printf("%15.4s", "42 is the answer");
// 	//ft_printf("%4.15s", "42 is the answer");
// 	//ft_printf("%#.3o", 1);
// 	//ft_printf("%.5p", 0);
// 	//ft_printf("{%#.5x}", 1);
// 	//ft_printf("{%05.Z}", 0);
// 	//ft_printf("{%05.s}", 0);
// 	//ft_printf("%-5.2s is a string", "");
// 	//ft_printf("%.p, %.0p", 0, 0);
// 	//ft_printf("%8.4d", -424242424);
// 	//ft_printf("%.2c", NULL);
// 	//ft_printf("%.3%");
// 	//ft_printf("{%05s}", "abc");
// 	//ft_printf("{%03c}", 0);
// 	//ft_printf("%.2s is a string", "this"); 
// 	//ft_printf("%5.2s is a string", "this");
// 	//ft_printf("%4.15s", "42");
// 	//ft_printf("{%5p}", 0);
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
// 	n = printf("%C, %-13.8S", 0, L"米фып");
// 	//printf("DefPrintf: |%+011.8zd| %%!", (ssize_t)-567);
// 	printf("\n\t%d\t\n", n);
// 	printf("\n");
// 	//printf("%+07.5d", 1234);
// 	return (0);
// }

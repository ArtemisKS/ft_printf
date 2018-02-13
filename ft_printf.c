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
	res = (char *)ft_strnew(ft_strlen(is));
	while (is[i])
	{
		if (is[i] > '0' && is[i] <= '9')
			fl = 1;
		if (fl)
			res[j++] = is[i];
		i++;
	}
	return (res);
}

int		str_min_prec_uni(t_spec *ts, char **fs, char *is)
{
	int j1;
	int n;
	int cnt;
	int n_sum;
	int j;

	j1 = 0;
	n = 0;
	cnt = 0;
	n_sum = 0;
	j = 0;
	while (j < (int)ts->prec)
	{
		if ((n_sum += ts->ia[n]) > (int)ts->prec)
			break ;
		while (cnt < ts->ia[n] && j1 < (int)ft_strlen(is))
		{
			*fs[j++] = is[j1++];
			cnt++;
		}
		n++;
		cnt = 0;
	}
	return (j);
}

char	*str_min_prec(t_spec *ts, char *fs, char *is, int *j)
{
	int j1;

	j1 = 0;
	while (*j < (int)ts->prec && j1 < (int)ft_strlen(is))
		fs[(*j)++] = is[j1++];
	return (fs);
}

char	*str_min_prec_end(t_spec *ts, char *fs, int *j)
{
	if (ts->f_len != (int)ts->prec)
		while (*j < ts->f_len)
			fs[(*j)++] = ' ';
	return (fs);
}

char	*str_min_prec_nil(t_spec *ts, char *fs, int *j)
{
	if (ts->f_len != (int)ts->prec)
		while (*j < ts->f_len)
			fs[(*j)++] = '0';
	return (fs);
}

char	*str_min_noprec(int j, char *fs, char *is, t_spec *ts)
{
	int j1;

	j1 = 0;
	while (j < (int)ft_strlen(is) && j1 < (int)ft_strlen(is))
		fs[j++] = is[j1++];
	while (j < ts->f_len)
		fs[j++] = ' ';
	return (fs);
}

int		figure_flen(t_spec *ts)
{
	if (ts->prec != 0 && ts->width != 0)
			ts->f_len = max(ts->prec, ts->width);
	else if (ts->prec != 0)
		ts->f_len = ts->prec;
	return (ts->f_len);
}

char	*f_leniter(char *fs, char *is, int *j, t_spec *ts)
{
	int j1;

	j1 = 0;
	while (*j < ts->f_len && j1 < (int)ft_strlen(is))
		fs[(*j)++] = is[j1++];
	return (fs);
}

char	*preciter(char *fs, char *is, int *j, t_spec *ts)
{
	int j1;

	j1 = 0;
	while (*j < (int)ts->prec && j1 < (int)ft_strlen(is))
		fs[(*j)++] = is[j1++];
	return (fs);
}

char		*str_prec_width(t_spec *ts, char *fs, char *is)
{
	int j;
	int j1;

	j = 0;
	j1 = 0;
	if (is[0] && ts->width)
	{
		ts->f_len = max(ts->width, (int)ft_strlen(is));
		while (j < ts->f_len - (int)ts->prec)
				fs[j++] = ' ';
		while (j < ts->f_len - (int)ft_strlen(is))
			fs[j++] = ' ';
		while (j < ts->f_len && j1 < (int)ft_strlen(is))
			fs[j++] = is[j1++];
	}
	else if (!ts->width)
		fs = f_leniter(fs, is, &j, ts);
	else
		fs = str_min_prec_end(ts, fs, &j);
	return (fs);
}

char	*str_prec_nowidth_uni(t_spec *ts, char *fs, char *is)
{
	int n;
	int cnt;
	int n_sum;
	int j;
	int j1;
	
	n = 0;
	cnt = 0;
	n_sum = 0;
	j = 0;
	j1 = 0;
	while (j < (int)ts->prec)
	{
		if ((n_sum += ts->ia[n]) > (int)ts->prec)
			break ;
		while (cnt < ts->ia[n])
		{
			fs[j++] = is[j1++];
			cnt++;
		}
		n++;
		cnt = 0;
	}
	return (fs);
}

int		uni_cycle(t_spec *ts, int n_sum, int *fl)
{
	int n;

	n = 0;
	while (ts->ia[n])
	{
		n_sum += ts->ia[n];
		if (n_sum == (int)ts->prec)
			*fl = 1;
		else if (n_sum > (int)ts->prec)
		{
			if (ts->ia[n - 1])
			{
				n_sum -= ts->ia[n];
				if (ts->ia[n - 1] + n_sum <= (int)ts->prec)
					n_sum = ts->ia[n - 1];
				else
					n_sum = (int)ts->prec - ts->ia[n - 1];
			}
			else
				n_sum -= (int)ts->prec;
			break ;
		}
		n++;
	}
	return (n_sum);
}

void		uni_cycle_def(int j, t_spec *ts, char **fs, char *is)
{
	int n;
	int n_sum;
	int j1;
	int cnt;

	n = 0;
	n_sum = 0;
	j1 = 0;
	cnt = 0;
	while (j < ts->f_len && j1 < (int)ft_strlen(is))
	{
		if ((n_sum += ts->ia[n]) > (int)ts->prec)
		{
			while (j < ts->f_len)
				(*fs)[j++] = ' ';
			break ;
		}
		while (cnt < ts->ia[n])
		{
			(*fs)[j++] = is[j1++];
			cnt++;
		}
		n++;
		cnt = 0;
	}
}

int		flen_prec(char **fs, t_spec *ts, char c)
{
	int j;

	j = 0;
	while (j < ts->f_len - (int)ts->prec)
		(*fs)[j++] = c;
	return (j);
}

char	*str_prec_width_uni(t_spec *ts, char *fs, char *is, char c)
{
	int fl;
	int n;
	int n_sum;
	int j;

	fl = 0;
	n = 0;
	n_sum = 0;
	j = 0;
	j = flen_prec(&fs, ts, ' ');
	n_sum = uni_cycle(ts, n_sum, &fl);
	while (!fl && n++ < n_sum)
		fs[j++] = c;
	uni_cycle_def(j, ts, &fs, is);
	return (fs);
}

int		flen_lenis(char **fs, char *is, char c, t_spec *ts)
{
	int j;

	j = 0;
	while (j < ts->f_len - (int)ft_strlen(is))
		(*fs)[j++] = c;
	return (j);
}

char	*str_noprec(t_spec *ts, char *fs, char *is)
{
	int j;
	int j1;

	j = 0;
	j1 = 0;
	if (!ts->dot)
	{
		j = flen_lenis(&fs, is, ' ', ts);
		while (j < ts->f_len && j1 < (int)ft_strlen(is))
			fs[j++] = is[j1++];
	}
	else if (ts->dot && ft_strcmp(is, "^@"))
		while (j < (int)ts->width)
			fs[j++] = ' ';
	else
	{
		ft_strdel(&fs);
		fs = ft_strdup(is);
	}
	return (fs);
}

char	*handle_str_min(t_spec *ts, char *fs, char *is, char c)
{
	int j;

	j = 0;
	ts->f_len = figure_flen(ts);
	if (ts->prec != 0)
	{
		if (c == 's')
			fs = str_min_prec(ts, fs, is, &j);
		else if (c == 'S')
			j = str_min_prec_uni(ts, &fs, is);
		while (j < ts->f_len && (int)ft_strlen(is) != 0)
			fs[j++] = ' ';
		fs = str_min_prec_end(ts, fs, &j);
	}
	else
		fs = str_min_noprec(j, fs, is, ts);
	return (fs);
}

char	*handle_str_nmn_prec(t_spec *ts, char *fs, char *is, char c)
{
	int j;

	j = 0;
	if (ts->width)
	{
		ts->f_len = max(ts->prec, ts->width);
		j = flen_prec(&fs, ts, ' ');
		if (c == 's')
			fs = f_leniter(fs, is, &j, ts);
		else if (c == 'S')
			fs = str_prec_width_uni(ts, fs, is, ' ');
	}
	else
	{
		if (c == 's')
			fs = str_min_prec(ts, fs, is, &j);
		else if (c == 'S')
			fs = str_prec_nowidth_uni(ts, fs, is);
	}
	return (fs);
}

char	*handle_str_nomin_nil(t_spec *ts, char *fs, char *is, char c)
{
	ts->f_len = figure_flen(ts);
	if ((int)ts->prec > (int)ft_strlen(is))
		fs = str_prec_width(ts, fs, is);			
	else
	{
		if (!ts->prec)
			fs = str_noprec(ts, fs, is);
		else
			fs = handle_str_nmn_prec(ts, fs, is, c);
	}
	return (fs);
}

char	*handle_str_nil_prec(t_spec *ts, char *fs, char *is)
{
	int j;

	j = 0;
	if (ts->width != 0)
	{
		while (j < ts->f_len - (int)ts->prec)
			fs[j++] = '0';
		while (j < ts->f_len - (int)ft_strlen(is))
			fs[j++] = '0';
		fs = f_leniter(fs, is, &j, ts);
	}
	else if (!ts->width)
		fs = f_leniter(fs, is, &j, ts);
	else
		str_min_prec_nil(ts, fs, &j);
	return (fs);
}

char	*handle_str_nil_noprec(t_spec *ts, char *fs, char *is)
{
	int j;

	j = 0;
	if (!ts->dot)
	{
		j = flen_lenis(&fs, is, '0', ts);
		fs = f_leniter(fs, is, &j, ts);
	}
	else if (ts->dot && ft_strcmp(is, "^@"))
		while (j < (int)ts->width)
			fs[j++] = '0';
	else
	{
		ft_strdel(&fs);
		fs = ft_strdup(is);
	}
	return (fs);
}

char	*handle_str_nil_smprec(t_spec *ts, char *fs, char *is, char c)
{
	int j;

	j = 0;
	if (ts->width)
	{
		j = flen_prec(&fs, ts, '0');
		if (c == 's')
			fs = f_leniter(fs, is, &j, ts);
		else if (c == 'S')
			fs = str_prec_width_uni(ts, fs, is, '0');
	}
	else
	{
		if (c == 's')
			fs = preciter(fs, is, &j, ts);
		else if (c == 'S')
			fs = str_prec_nowidth_uni(ts, fs, is);
	}
	return (fs);
}

char	*handle_str_nil(t_spec *ts, char *fs, char *is, char c)
{
	ts->f_len = figure_flen(ts);
	if ((int)ts->prec > (int)ft_strlen(is))
		fs = handle_str_nil_prec(ts, fs, is);
	else
	{
		if (!ts->prec)
			fs = handle_str_nil_noprec(ts, fs, is);
		else
			fs = handle_str_nil_smprec(ts, fs, is, c);
	}
	return (fs);
}

char	*handle_str(t_spec *ts, char *s, char c)
{
	char *fs;
	char *is;

	if (s)
		is = ft_strdup(s);
	else
		is = ft_strdup("");
	if (ts->asterisk2 && ts->min && (int)ts->prec > (int)ft_strlen(is))
		ts->prec = 0;
	ts->f_len = max(ft_strlen(is), ts->width);
	fs = (char *)ft_strnew(2 * ts->f_len);
	if (ts->min == 1)
		fs = handle_str_min(ts, fs, is, c);
	else if (ts->min == 0 && ts->nil == 0)
		fs = handle_str_nomin_nil(ts, fs, is, c);
	else if (ts->min == 0 && ts->nil == 1)
		fs = handle_str_nil(ts, fs, is, c);
	ft_strdel(&is);
	return (fs);
}

char	*handle_dig_dot(t_spec *ts, char *fs)
{
	int j;

	j = 0;
	if (ts->width == 0)
	{
		fs[j] = 0;
		return (fs);
	}
	else
	{
		while (j < ts->f_len)
			fs[j++] = ' ';
	}
	return (fs);
}

char	*handle_dig_allnil(char *fs, char *is)
{
	int j;

	j = 0;
	while (j < (int)ft_strlen(is))
	{
		fs[j] = is[j];
		j++;
	}
	return (fs);
}

char	*f_leniterdig(int j, char *is, char *fs, t_spec *ts)
{
	int j1;

	j1 = 0;
	while (j < ts->f_len && j1 < (int)ft_strlen(is))
	{
		fs[j++] = is[j1];
		j1++;
	}
	return (fs);
}

char	*handle_dig_nil(t_spec *ts, char *fs, char *is)
{
	int j;

	j = 0;
	if ((int)ts->prec >= (int)ft_strlen(is))
		while (j < ts->f_len - (int)ts->prec)
		{
			fs[j] = ' ';
			j++;
		}
	while (j < ts->f_len - (int)ft_strlen(is))
	{
		fs[j] = '0';
		j++;
	}
	fs = f_leniterdig(j, is, fs, ts);
	return (fs);
}

char	*dig_min_smprec(char *fs, char *is, t_spec *ts)
{
	int j1;
	int j;

	j = 0;
	j1 = 0;
	while (j < (int)ft_strlen(is) && j1 < (int)ft_strlen(is))
		fs[j++] = is[j1++];
	while (j < ts->f_len)
		fs[j++] = ' ';
	return (fs);
}

char	*dig_min_prec(t_spec *ts, char *fs, char *is)
{
	int j1;
	int j;

	j = 0;
	j1 = 0;
	while (j < (int)(ts->prec - (int)ft_strlen(is)))
		fs[j++] = '0';
	while (j < (int)ts->prec && j1 < (int)ft_strlen(is))
		fs[j++] = is[j1++];
		j1++;
	while (j < ts->f_len)
		fs[j++] = ' ';
	return (fs);
}

char	*handle_dig_min(t_spec *ts, char *fs, char *is)
{
	if ((int)ts->prec <= (int)ft_strlen(is))
		fs = dig_min_smprec(fs, is, ts);
	else
		fs = dig_min_prec(ts, fs, is);
	return (fs);
}

char	*dig_precwidth_smprec(char *fs, char *is, t_spec *ts)
{
	int j1; 
	int j;

	j1 = 0;
	j = 0;
	while (j < ts->f_len - (int)ft_strlen(is))
			fs[j++] = ' ';
	while (j < ts->f_len && j1 < (int)ft_strlen(is))
		fs[j++] = is[j1++];
	return (fs);
}

char	*dig_precwidth_prec(t_spec *ts, char *fs, char *is)
{
	int j1; 
	int j;

	j1 = 0;
	j = 0;
	while (j < (int)(ts->f_len - ts->prec))
			fs[j++] = ' ';
	while (j < ts->f_len - (int)ft_strlen(is))
		fs[j++] = '0';
	while (j < ts->f_len && j1 < (int)ft_strlen(is))
		fs[j++] = is[j1++];
	return (fs);
}

char 	*handle_dig_precwidth(t_spec *ts, char *fs, char *is)
{
	if ((int)ts->prec <= (int)ft_strlen(is))
		fs = dig_precwidth_smprec(fs, is, ts);
	else
		fs = dig_precwidth_prec(ts, fs, is);
	return (fs);
}

char	*dig_plusnil_prec(t_spec *ts, char *fs, char *is, intmax_t i)
{
	int j;
	int j1;

	j = 0;
	j1 = 0;
	if (ts->prec > ts->width)
			ts->f_len++;
		while (j < ts->f_len - max((int)ft_strlen(is), ts->prec))
			fs[j++] = ' ';
		while (j < ts->f_len - (int)ft_strlen(is))
			fs[j++] = '0';
		while (j < ts->f_len && j1 < (int)ft_strlen(is))
			fs[j++] = is[j1++];
		while (fs[j] != ' ' && j-- >= -1)
			;
		if (i >= 0)
			fs[j] = '+';
		else 
			fs[j] = '-';
		return (fs);
}

char	*dig_plusnil_noprec(char *fs, char *is, intmax_t i, t_spec *ts)
{
	int j;
	int j1;

	j = 0;
	j1 = 0;
	if (i >= 0)
		fs[j++] = '+';
	else 
		fs[j++] = '-';
	while (j < ts->f_len - (int)ft_strlen(is))
		fs[j++] = '0';
	while (j < ts->f_len && j1 < (int)ft_strlen(is))
		fs[j++] = is[j1++];
	return (fs);
}

char	*handle_dig_plusnil(t_spec *ts, char *fs, char *is, intmax_t i)
{
	if (ts->f_len == (int)ft_strlen(is))
		ts->f_len++;
	if (ts->prec)
		fs = dig_plusnil_prec(ts, fs, is, i);
	else
		fs = dig_plusnil_noprec(fs, is, i, ts);
	return (fs);
}

char	*dig_pluswidth_prec(t_spec *ts, char *fs, char *is, intmax_t i)
{
	int j;
	int j1;

	j = 0;
	j1 = 0;
	while (j < ts->f_len - max((int)ft_strlen(is), ts->prec))
		fs[j++] = ' ';
	while (j < ts->f_len - (int)ft_strlen(is))
		fs[j++] = '0';
	while (j < ts->f_len && j1 < (int)ft_strlen(is))
		fs[j++] = is[j1++];
	while (fs[j--] != ' ')
		;
	if (i >= 0)
		fs[++j] = '+';
	else 
		fs[++j] = '-';
	return (fs);
}

char	*dig_pluswidth_noprec(char *fs, char *is, intmax_t i, t_spec *ts)
{
	int j;
	int j1;

	j = 0;
	j1 = 0;
	while (j < ts->f_len - (int)ft_strlen(is))
		fs[j++] = ' ';
	while (j < ts->f_len && j1 < (int)ft_strlen(is))
		fs[j++] = is[j1++];
	while (fs[j] != ' ')
		j--;
	if (i >= 0)
		fs[j++] = '+';
	else 
		fs[j++] = '-';
	return (fs);
}

char	*handle_dig_pluswidth(t_spec *ts, char *fs, char *is, intmax_t i)
{
	
	if ((int)ts->width < ts->f_len)
		ts->f_len++;
	if (ts->prec)
		fs = dig_pluswidth_prec(ts, fs, is, i);
	else
		fs = dig_pluswidth_noprec(fs, is, i, ts);
	return (fs);

}

char	*dig_plminnil_prec(t_spec *ts, char *fs, char *is, intmax_t i)
{
	int j;
	int j1;

	j = 0;
	j1 = 0;
	if (i >= 0)
		fs[j++] = '+';
	else 
		fs[j++] = '-';
	while (j < (int)(ts->prec - (int)ft_strlen(is) + 1))
		fs[j++] = '0';
	while (j < (int)(ts->prec + 1) && j1 < (int)ft_strlen(is))
		fs[j++] = is[j1++];
	while (j < ts->f_len)
		fs[j++] = ' ';
	return (fs);
}

char	*dig_plminnil_noprec(char *fs, char *is, intmax_t i, t_spec *ts)
{
	int j;
	int j1;

	j = 0;
	j1 = 0;
	if (i >= 0)
		fs[j++] = '+';
	else 
		fs[j++] = '-';
	j1 = 0;
	while (j1 < (int)ft_strlen(is) && j1 < (int)ft_strlen(is))
		fs[j++] = is[j1++];
	while (j < ts->f_len)
		fs[j++] = ' ';
	return (fs);
}

char	*handle_dig_plminnil(t_spec *ts, char *fs, char *is, intmax_t i)
{
	if (ts->prec)
		fs = dig_plminnil_prec(ts, fs, is, i);
	else
		fs = dig_plminnil_noprec(fs, is, i, ts);
	return (fs);
}

char	*handle_dig_plus(char *fs, char *is, intmax_t i, t_spec *ts)
{
	int j;
	int j1;

	j1 = 0;
	j = 0;
	ts->f_len++;
	if (i >= 0)
		fs[j++] = '+';
	else 
		fs[j++] = '-';
	while (j < ts->f_len - (int)ft_strlen(is))
		fs[j++] = '0';
	while (j < ts->f_len && j1 < (int)ft_strlen(is))
		fs[j++] = is[j1++];
	return (fs);
}

char	*handle_dig_space(char *fs, char *is, t_spec *ts)
{
	int j;
	int j1;

	j1 = 0;
	j = 0;
	if ((int)ft_strlen(is) == ts->f_len)
		ts->f_len++;
	fs[j++] = ' ';
	while (j < ts->f_len - (int)ft_strlen(is))
		fs[j++] = '0';
	while (j < ts->f_len && j1 < (int)ft_strlen(is))
		fs[j++] = is[j1++];
	return (fs);
}

char	*dig_spaceminnil_prec(t_spec *ts, char *fs, char *is)
{
	int j;
	int j1;

	j1 = 0;
	j = 0;
	fs[j++] = ' ';
	while (j < ts->f_len - max((int)ft_strlen(is), ts->prec))
		fs[j++] = '0';
	while (j < ts->f_len - (max((int)ft_strlen(is), ts->prec) - min((int)ft_strlen(is),
		ts->prec)) && j1 < (int)ft_strlen(is))
		fs[j++] = is[j1++];
	while (j < ts->f_len)
		fs[j++] = ' ';
	return (fs);
}

char	*dig_spaceminnil_noprec(char *fs, char *is, t_spec *ts)
{
	int j;
	int j1;

	j1 = 0;
	j = 0;
	fs[j++] = ' ';
	while (j1 < (int)ft_strlen(is) && j < ts->f_len)
		fs[j++] = is[j1++];
	while (j < ts->f_len)
		fs[j++] = ' ';
	return (fs);
}

char	*handle_dig_spaceminnil(t_spec *ts, char *fs, char *is)
{
	if (ts->prec)
		fs = dig_spaceminnil_prec(ts, fs, is);
	else
		fs = dig_spaceminnil_noprec(fs, is, ts);
	return (fs);
}

char	*dig_spacenil_prec(t_spec *ts, char *fs, char *is)
{
	int j;
	int j1;

	j1 = 0;
	j = 0;
	while (j < ts->f_len - max((int)ft_strlen(is), ts->prec))
		fs[j++] = ' ';
	while (j < ts->f_len - min((int)ft_strlen(is), ts->prec))
		fs[j++] = '0';
	while (j < ts->f_len && j1 < (int)ft_strlen(is))
		fs[j++] = is[j1++];
	return (fs);
}

char	*dig_spacenil_noprec(t_spec *ts, char *fs, char *is)
{
	int j;
	int j1;

	j1 = 0;
	j = 0;
	fs[j++] = ' ';
	while (j < ts->f_len - (int)ft_strlen(is) && ts->nil)
		fs[j++] = '0';
	while (j < ts->f_len - (int)ft_strlen(is) && !ts->nil)
		fs[j++] = ' ';
	while (j < ts->f_len && j1 < (int)ft_strlen(is))
		fs[j++] = is[j1++];
	return (fs);
}

char	*handle_dig_spacenil(t_spec *ts, char *fs, char *is)
{
	if (ts->prec)
		fs = dig_spacenil_prec(ts, fs, is);
	else
		fs = dig_spacenil_noprec(ts, fs, is);
	return (fs);
}

int		handle_dig1(t_spec *ts, intmax_t i, char **fs, char *is)
{
	if (ts->dot && !ts->prec && i == 0)
	{
		*fs = handle_dig_dot(ts, *fs);
		return (1);
	}
	else if (!ts->min && !ts->space && !ts->plus 
		&& !ts->nil && !ts->width && !ts->prec && i >= 0)
	{
		*fs = handle_dig_allnil(*fs, is);
		return (1);
	}
	else if (ts->nil && !ts->min && !ts->plus && !ts->space && i >= 0)
	{
		*fs = handle_dig_nil(ts, *fs, is);
		return (1);
	}
	else if (ts->min && !ts->plus && !ts->space && i >= 0)
	{
		*fs = handle_dig_min(ts, *fs, is);
		return (1);
	}
	return (0);
}

char	*handle_dig2(t_spec *ts, intmax_t i, char *fs, char *is)
{
	if (!ts->plus && !ts->min && !ts->nil && !ts->space && i >= 0)
		fs = handle_dig_precwidth(ts, fs, is);
	else if ((ts->plus && !ts->min && ts->nil) || 
		(i < 0 && !ts->min && ts->nil))
		fs = handle_dig_plusnil(ts, fs, is, i);
	else if ((ts->plus && !ts->min && ts->width) || 
		(i < 0 && !ts->min && ts->width))
		fs = handle_dig_pluswidth(ts, fs, is, i);
	else if ((ts->plus && ts->min && ts->nil) ||
		(i < 0 && ts->min && ts->nil) ||
		 (ts->plus && ts->min && ts->width) || 
		 (i < 0 && ts->min && ts->width))
		fs = handle_dig_plminnil(ts, fs, is, i);
	else if ((ts->plus && !ts->nil && !ts->width) ||
		(i < 0 && !ts->nil && !ts->width))
		fs = handle_dig_plus(fs, is, i, ts);
	else if (!ts->plus && ts->space && !ts->nil && !ts->width && i >= 0)
		fs = handle_dig_space(fs, is, ts);
	else if ((!ts->plus && ts->space && ts->min && ts->nil && i >= 0) 
		|| (!ts->plus && ts->space && ts->min && ts->width && i >= 0))
		fs = handle_dig_spaceminnil(ts, fs, is);
	else if ((!ts->plus && ts->space && !ts->min && ts->nil && i >= 0) 
			|| (!ts->plus && ts->space && !ts->min && ts->width && i >= 0))
		fs = handle_dig_spacenil(ts, fs, is);
	return (fs);
}

char	*handle_dig(t_spec *ts, intmax_t i)
{
	char *fs;
	char *is;

	is = ft_itoa_base(i, 10);
	if (i < 0)
		is = min_handle(is);
	if (ts->asterisk2 && ts->min && (int)ts->prec > (int)ft_strlen(is))
	{
		ts->prec = 0;
		if (ts->nil)
			ts->min = 0;
	}
	ts->f_len = max(max((int)ft_strlen(is), ts->width), ts->prec);
	fs = (char *)ft_strnew(2 * ts->f_len);
	if (!handle_dig1(ts, i, &fs, is))
		fs = handle_dig2(ts, i, fs, is);
	ft_strdel(&is);
	return (fs);
}

char	*handle_uns_dot(t_spec *ts, char *fs)
{
	int j;

	j = 0;
	if ((!ts->width && !ts->hash) || (!ts->width && ts->hash && ts->fl != 1))
	{
		fs[0] = 0;
		return (fs);
	}
	else
	{
		if (ts->hash && ts->fl == 1)
			fs[j++] = '0';
		while (j < ts->f_len)
			fs[j++] = ' ';
	}
	return (fs);
}

char	*handle_uns_allnil(t_spec *ts, char *fs, char *is, uintmax_t i)
{
	int j;
	int j1;

	j1 = 0;
	j = 0;
	if (ts->hash == 1 && ts->fl == 2 && i != 0)
	{
		fs[j++] = '0';
		fs[j++] = 'X';
		ts->il += 2;
	}
	else if (ts->hash == 1 && ts->fl == 1 && i != 0)
	{
		fs[j++] = '0';
		ts->il++;
	}
	while (j < ts->il && j1 < (int)ft_strlen(is))
		fs[j++] = is[j1++];
	return (fs);
}

char	*uns_nil_smprec(t_spec *ts, char *fs, char *is, uintmax_t i)
{
	int j;
	int j1;

	j1 = 0;
	j = 0;
	if (ts->hash == 1 && ts->fl == 2 && i != 0)
	{
		fs[j++] = '0';
		fs[j++] = 'X';
		if ((int)ts->width < ts->il)
			ts->f_len += 2;
	}
	else if (ts->hash == 1 && ts->fl == 1 && i != 0)
	{
		fs[j++] = '0';
		if ((int)ts->width < ts->il)
			ts->f_len++;
	}
	while (j < ts->f_len - ts->il)
		fs[j++] = '0';
	while (j < ts->f_len && j1 < (int)ft_strlen(is))
		fs[j++] = is[j1++];
	return (fs);
}

char	*uns_nil_prec(t_spec *ts, char *fs, char *is)
{
	int j;
	int j1;

	j1 = 0;
	j = 0;
	while (j < ts->f_len - (int)ts->prec)
		fs[j++] = ' ';
	while (j < ts->f_len - ts->il)
		fs[j++] = '0';
	while (j < ts->f_len && j1 < (int)ft_strlen(is))
		fs[j++] = is[j1++];
	return (fs);
}

char	*handle_uns_nil(t_spec *ts, char *fs, char *is, uintmax_t i)
{
	if ((int)ts->prec <= ts->il)
		fs = uns_nil_smprec(ts, fs, is, i);
	else
		fs = uns_nil_prec(ts, fs, is);
	return (fs);
}

char	*uns_min_smprec(t_spec *ts, char *fs, char *is, uintmax_t i)
{
	int j;
	int j1;

	j1 = 0;
	j = 0;
	if (ts->hash == 1 && ts->fl == 2 && i != 0)
	{
		fs[j++] = '0';
		fs[j++] = 'X';
		ts->il += 2;
	}
	else if (ts->hash == 1 && ts->fl == 1 && i != 0)
	{
		fs[j++] = '0';
		ts->il++;
	}
	while (j < ts->il && j1 < (int)ft_strlen(is))
		fs[j++] = is[j1++];
	while (j < ts->f_len)
		fs[j++] = ' ';
	return (fs);
}

char	*uns_min_prec(t_spec *ts, char *fs, char *is)
{
	int j;
	int j1;

	j1 = 0;
	j = 0;
	while (j < (int)(ts->prec - ts->il))
		fs[j++] = '0';
	while (j < (int)ts->prec && j1 < (int)ft_strlen(is))
		fs[j++] = is[j1++];
	while (j < ts->f_len)
		fs[j++] = ' ';
	return (fs);
}

char	*handle_uns_min(t_spec *ts, char *fs, char *is, uintmax_t i)
{
	if ((int)ts->prec <= ts->il)
		fs = uns_min_smprec(ts, fs, is, i);
	else
		fs = uns_min_prec(ts, fs, is);
	return (fs);
}

char	*uns_nominnil_smprec(t_spec *ts, char *fs, char *is, uintmax_t i)
{
	int j;
	int j1;

	j1 = 0;
	j = 0;
	if (ts->hash == 1 && ts->fl == 2)
			ts->il += 2;
	else if (ts->hash == 1 && ts->fl == 1)
		ts->il++;
	while (j < ts->f_len - ts->il)
		fs[j++] = ' ';
	if (ts->hash == 1 && ts->fl == 2 && i != 0)
	{
		fs[j++] = '0';
		fs[j++] = 'X';
	}
	else if (ts->hash == 1 && ts->fl == 1 && i != 0)
		fs[j++] = '0';
	while (j < ts->f_len && j1 < (int)ft_strlen(is))
		fs[j++] = is[j1++];
	return (fs);
}

char	*uns_nominnil_prec(t_spec *ts, char *fs, char *is, uintmax_t i)
{
	int j;
	int j1;

	j1 = 0;
	j = 0;
	while (j < (int)(ts->f_len - ts->prec))
		fs[j++] = ' ';
	if (ts->hash == 1 && ts->fl == 2 && i != 0)
	{
		fs[j++] = '0';
		fs[j++] = 'X';
		ts->f_len += 2;
	}
	else if (ts->hash == 1 && ts->fl == 1 && i != 0)
		fs[j++] = '0';
	while (j < ts->f_len - ts->il)
		fs[j++] = '0';
	while (j < ts->f_len && j1 < (int)ft_strlen(is))
		fs[j++] = is[j1++];
	return (fs);
}

char	*handle_uns_nominnil(t_spec *ts, char *fs, char *is, uintmax_t i)
{
	if ((int)ts->prec <= ts->il)
		fs = uns_nominnil_smprec(ts, fs, is, i);
	else
		fs = uns_nominnil_prec(ts, fs, is, i);
	return (fs);
}

char	*print_unsigned1(t_spec *ts, char *fs, char *is, uintmax_t i)
{
	if (ts->dot == 1 && ts->prec == 0 && i == 0)
		fs = handle_uns_dot(ts, fs);
	else if (ts->min == 0 && ts->nil == 0 && ts->width == 0 && ts->prec == 0)
		fs = handle_uns_allnil(ts, fs, is, i);
	else if (ts->nil == 1 && ts->min == 0)
		fs = handle_uns_nil(ts, fs, is, i);
	else if (ts->min == 1)
		fs = handle_uns_min(ts, fs, is, i);
	else if (ts->min == 0 && ts->nil == 0)
		fs = handle_uns_nominnil(ts, fs, is, i);
	return (fs);
}

char	*print_unsigned(t_spec *ts, uintmax_t i, int fl)
{
	char *fs;
	int il;
	char *is;

	if (!fl)
		il = ft_nbrlen_u(i);
	else if (fl == 1)
		il = ft_strlen(is = ft_itoa_base_u(i, 8));
	else
		il = ft_strlen(is = ft_itoa_base_u(i, 16));
	ts->f_len = max(max(il, ts->width), ts->prec);
	ts->fl = fl;
	ts->il = il;
	if (!fl)
		is = ft_itoa_base_u(i, 10);
	fs = (char *)ft_strnew(2 * ts->f_len);
	fs = print_unsigned1(ts, fs, is, i);
	ft_strdel(&is);
		return (fs);
}

char	*char_nominnil_prec(t_spec *ts, char *s, char *fs, int j)
{
	int j1;

	j1 = 0;
	if (ts->width)
	{
		if (s[0])
		{
			if (!s[1])
				while (j < ts->f_len - (int)ts->prec)
					fs[j++] = ' ';
			else
				while (j < ts->f_len - (int)ft_strlen(s))
					fs[j++] = ' ';
		}
	}
	if (s[0])
		while (j < ts->f_len && j1 < (int)ft_strlen(s))
			fs[j++] = s[j1++];
	else
	{
		fs[j++] = '^';
		fs[j] = '@';
	}
	return (fs);
}

char	*char_nominnil_noprec(char *s, char *fs, int j, t_spec *ts)
{
	int j1;

	j1 = 0;
	while (j < ts->f_len - ts->len)
			fs[j++] = ' ';
	if (s[0])
		while (j < ts->f_len && j1 < (int)ft_strlen(s))
			fs[j++] = s[j1++];
	else
	{
		fs[j++] = '^';
		fs[j] = '@';
	}
	return (fs);
}

char	*handle_char_nominnil(t_spec *ts, char *s, char *fs)
{
	int j;

	j = 0;
	if (ts->prec)
		fs = char_nominnil_prec(ts, s, fs, j);
	else
		fs = char_nominnil_noprec(s, fs, j, ts);
	return (fs);
}

int		char_nil_precwidth(t_spec *ts, char *s, char **fs)
{
	int j;

	j = 0;
	if (s[0])
	{
		if (!s[1])
			while (j < ts->f_len - (int)ts->prec)
				(*fs)[j++] = '0';
		else
			while (j < ts->f_len - (int)ft_strlen(s))
				(*fs)[j++] = '0';
	}
	return (j);
}

char	*char_nil_noprec(char *s, char *fs, t_spec *ts)
{
	int j;
	int j1;

	j = 0;
	j1 = 0;
	while (j < ts->f_len - ts->len)
		fs[j++] = '0';
	if (s[0])
		while (j < ts->f_len && j1 < (int)ft_strlen(s))
			fs[j++] = s[j1++];
	else
	{
		fs[j++] = '^';
		fs[j] = '@';
	}
	return (fs);
}


char	*handle_char_nil(t_spec *ts, char *s, char *fs)
{
	int j;
	int j1;

	j = 0;
	j1 = 0;
	if (ts->prec)
	{
		if (ts->width)
			j = char_nil_precwidth(ts, s, &fs);
		if (s[0])
			while (j < ts->f_len && j1 < (int)ft_strlen(s))
				fs[j++] = s[j1++];
		else
		{
			if (ts->f_len != (int)ts->prec)
				while (j < ts->f_len)
					fs[j++] = '0';
			fs[j++] = '^';
			fs[j] = '@';
		}
	}
	else
		fs = char_nil_noprec(s, fs, ts);
	return (fs);
}

char	*char_min_prec(t_spec *ts, char *s, char *fs, int j)
{
	int j1;

	j1 = 0;
	if (s[0])
	{
		j1 = 0;
		if (!s[1])
			while (j < (int)ts->prec && j1 < (int)ft_strlen(s))
				fs[j++] = s[j1++];
		else
			while (j < ts->f_len && j1 < (int)ft_strlen(s))
				fs[j++] = s[j1++];
		while (j < ts->f_len)
			fs[j++] = ' ';
	}
	else
	{
		if (ts->f_len != (int)ts->prec)
			while (j < ts->f_len)
				fs[j++] = ' ';
		fs[j++] = '^';
		fs[j] = '@';
	}
	return (fs);
}

char	*handle_char_min(t_spec *ts, char *s, char *fs)
{
	int j;
	int j1;

	j = 0;
	j1 = 0;
	if (ts->prec)
		fs = char_min_prec(ts, s, fs, j);
	else
	{
		if (s[0])
			while (j < ts->f_len && j1 < (int)ft_strlen(s))
				fs[j++] = s[j1++];
		else
		{
			fs[j++] = '^';
			fs[j++] = '@';
		}
		while (j < ts->f_len)
			fs[j++] = ' ';
	}
	return (fs);
}

char	*print_char(t_spec *ts, char *s)
{
	int len;
	
	char *fs;

	len = ft_strlen(s);
	if (!s[0])
		len = 1;
	ts->f_len = max(len, ts->width);
	ts->len = len;
	fs = (char *)ft_strnew(2 * ts->f_len);
	if (ts->min == 0 && ts->nil == 0)
		fs = handle_char_nominnil(ts, s, fs);
	else if (ts->min == 0 && ts->nil == 1)
		fs = handle_char_nil(ts, s, fs);
	else if (ts->min == 1)
		fs = handle_char_min(ts, s, fs);
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
	fs = handle_dig(ts, i);
	return (fs);
}

int		size_bin(int value)
{
	char *vbin;
	int len;

	vbin = ft_itoa_base(value, 2);
	len = ft_strlen(vbin);
	ft_strdel(&vbin);
	return (len);
}

char	*print_uni_7(int value, t_spec *ts, int i)
{
	unsigned char octet;
	char *res;

	octet = value;
	res = (char *)ft_strnew(5);
	res[0] = octet;
	ts->ia[i]++;
	return (res);
}

char	*print_uni_11(int value, t_spec *ts, int i, t_uni *tu)
{
	unsigned int v;
	unsigned char octet;
	char *res;

	v = value;
	tu->o2 = (v << 26) >> 26;
	tu->o1 = ((v >> 6) << 27) >> 27;
	octet = (tu->mask1 >> 8) | tu->o1;
	res = (char *)ft_strnew(5);
	res[0] = octet;
	ts->ia[i]++;
	octet = ((tu->mask1 << 24) >> 24) | tu->o2;
	res[1] = octet;
	ts->ia[i]++;
	return (res);
}

char	*print_uni_16(int value, t_spec *ts, int i, t_uni *tu)
{
	unsigned int v;
	unsigned char octet;
	char *res;

	v = value;
	tu->o3 = (v << 26) >> 26;
	tu->o2 = ((v >> 6) << 26) >> 26;
	tu->o1 = ((v >> 12) << 28) >> 28;
	octet = (tu->mask2 >> 16) | tu->o1;
	res = (char *)ft_strnew(5);
	res[0] = octet;
	ts->ia[i]++;
	octet = ((tu->mask2 << 16) >> 24) | tu->o2;
	res[1] = octet;
	ts->ia[i]++;
	octet = ((tu->mask2 << 24) >> 24) | tu->o3;
	res[2] = octet;
	ts->ia[i]++;
	return (res);
}

char	*print_uni_21(int value, t_spec *ts, int i, t_uni *tu)
{
	unsigned int v;
	unsigned char octet;
	char *res;

	v = value;
	tu->o4 = (v << 26) >> 26;
	tu->o3 = ((v >> 6) << 26) >> 26;
	tu->o2 = ((v >> 12) << 26) >> 26;
	tu->o1 = ((v >> 18) << 29) >> 29;
	octet = (tu->mask3 >> 24) | tu->o1;
	res = (char *)ft_strnew(10);
	res[0] = octet;
	ts->ia[i]++;
	octet = ((tu->mask3 << 8) >> 24) | tu->o2;
	res[1] = octet;
	ts->ia[i]++;
	octet = ((tu->mask3 << 16) >> 24) | tu->o3;
	res[2] = octet;
	ts->ia[i]++;
	octet = ((tu->mask3 << 24) >> 24) | tu->o4;
	res[3] = octet;
	ts->ia[i]++;
	return (res);
}

t_uni	*init_uni(t_uni *tu)
{
	tu->mask1 = 0;
	tu->mask2 = 0;
	tu->mask3 = 0;
	tu->o1 = 0;
	tu->o2 = 0;
	tu->o3 = 0;
	tu->o4 = 0;
	return (tu);
}

char	*print_unicode(int value, t_spec *ts, int i)
{
	t_uni *tu;
	int size;
	char *res;

	tu = (t_uni *)malloc(sizeof(t_uni));
	tu = init_uni(tu);
	tu->mask1 = 49280;
	tu->mask2 = 14712960;
	tu->mask3 = 4034953344;
	size = size_bin(value);

	if (size <= 7)
		res = print_uni_7(value, ts, i);
	else  if (size <= 11)
		res = print_uni_11(value, ts, i, tu);
	else  if (size <= 16)
		res = print_uni_16(value, ts, i, tu);
	else
		res = print_uni_21(value, ts, i, tu);
	ft_memdel((void**)&tu);
	return (res);
}

char	*handle_string_uni(va_list ap, t_spec *ts, char *s)
{
	wchar_t *wa;
	char *s1;
	char *tmp;
	int i;

	wa = va_arg(ap, wchar_t *);
	i = 0;
	if (wa)
	{
		while (wa[i])
		{
			tmp = s;
			s1 = print_unicode(wa[i], ts, i);
			s = ft_strjoin(s, s1);
			ft_strdel(&s1);
			ft_strdel(&tmp);
			i++;
		}
		tmp = s;
		s = handle_str(ts, s, 'S');
		ft_strdel(&tmp);
	}
	else
		ft_strdel(&s);
	return (s);
}


char 	*handle_string(va_list ap, t_spec *ts, char c)
{
	char *s;

	s = (char *)ft_strnew(1);
	if (c == 's' && !ts->l)
	{
		ft_strdel(&s);
		s = va_arg(ap, char *);
	}
	if (c == 'S' || ts->l)
		s = handle_string_uni(ap, ts, s);
	if (!s && !ts->nil && !ts->min)
		return (s);
	if (c == 's')
		s = handle_str(ts, s, 's');
	return (s);
}

char	*handle_char_uni(va_list ap, t_spec *ts, char *fs)
{
	int value;
	char *tmp;
	int i;

	value = va_arg(ap, int);
	i = 0;
	tmp = fs;
	fs = print_unicode(value, ts, i);
	ft_strdel(&tmp);
	if (!fs[0])
	{
		ft_strdel(&fs);
		fs = ft_strdup("^@");
	}
	tmp = fs;
	fs = print_char(ts, fs);
	ft_strdel(&tmp);
	return (fs);
}

char	*handle_char(va_list ap, t_spec *ts, char c)
{
	char *fs;
	char *tmp;

	fs = ft_strnew(1);
	tmp = fs;
	if (c == 'c' && !ts->l)
	{
		fs[0] = (char)va_arg(ap, int);
		fs = print_char(ts, fs);
		ft_strdel(&tmp);
	}
	if (c == 'C' || ts->l)
		fs = handle_char_uni(ap, ts, fs);
	return (fs);
}

char	*handle_percent(t_spec *ts)
{
	char *fs;
	char *tmp;

	fs = ft_strdup("%");
	tmp = fs;
	fs = print_char(ts, fs);
	ft_strdel(&tmp);
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

char	*handle_unsigned1(va_list ap, t_spec *ts, char c, uintmax_t i)
{
	char *fs;

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
	return (fs);
}

char	*handle_unsigned(va_list ap, t_spec *ts, char c)
{
	char *fs;
	uintmax_t i;
	fs = NULL;

	i = 0;
	if (c == 'U' || c == 'O')
		ts->l = 1;
	fs = handle_unsigned1(ap, ts, c, i);
	if (c == 'x')
		fs = ft_lower(fs);
	return (fs);
}

char	*point_at_beg1(char *fs, int j, int fl)
{
	int i;

	i = 0;
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

char	*point_at_beg(char *fs, t_spec *ts)
{
	int i;
	int j;
	int fl;

	j = 0;
	i = 0;
	while (fs[i++] == '0')
		j++;
	fl = max(ts->prec, ts->width);
	if (fl == (int)ts->prec)
		fl += 2;
	fs = ft_strnew(fl);
	fs = point_at_beg1(fs, j, fl);
	return (fs);
}

int		cor_pointer1(int i, char **fs, t_spec *ts)
{
	int fl;

	fl = 1;
	if (i == (int)ft_strlen(*fs) - 1 && !((*fs)[i + 1]))
		*fs = ft_strjoin(*fs, "x0");
	else if (fs[0] == 0)
		*fs = ft_strdup("0x");
	else if (i == 0)
		*fs = point_at_beg(*fs, ts);
	else if ((*fs)[i + 1] && (*fs)[i + 2])
	{
		(*fs)[i + 1] = 'x';
		(*fs)[i + 2] = '0';
		fl = 0;
	}
	return (fl);
}

char	*cor_pointer(char *fs, t_spec *ts)
{
	int i;
	char *tmp;

	i = 0;
	tmp = fs;
	if (!ft_strchr(fs, 'x'))
	{
		while (fs[i] && fs[i] != '0')
			i++;
		if (cor_pointer1(i, &fs, ts))
			ft_strdel(&tmp);
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
	char *tmp;

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
 		res = ft_strnew(1);
 		tmp = res;
 		res[0] = c;
 		res = print_char(ts, res);
 		ft_strdel(&tmp);
 	}
	return (res);
}

void 	init_struct(t_spec *ts)
{
	int i;

	i = 0;
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
	ts->f_len = 0;
	ts->fl = 0;
	ts->il = 0;
	while (i < 100)
		ts->ia[i++] = 0;
	ts->len = 0;
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
	ft_strdel(&wid);
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
	ft_strdel(&prec);
	return (i);
}

int		parse_flags(char *fmt, t_spec *ts)
{
	int i;

	i = 0;
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
	return (i);
}

int		parse_width_bon(char *fmt, t_spec *ts, int i, va_list ap)
{
	int tmp;

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
	return (i);
}

int		parse_width_bon1(char *fmt, t_spec *ts, int i, va_list ap)
{
	int tmp;

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
	return (i);
}

int		parse_prec_bon(char *fmt, t_spec *ts, int i, va_list ap)
{
	int tmp;

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
	return (i);
}

int		parse_specif(char *fmt, t_spec *ts, int *i)
{
	int fl;

	fl = 0;
	if (fmt[*i] == 'l' && fmt[*i + 1] && fmt[*i + 1] == 'l')
	{
		ts->ll = 1;
		*i += 2;
		fl = 1;
	}
	else if (fmt[*i] == 'h' && fmt[*i + 1] && fmt[*i + 1] == 'h')
	{
		ts->hh = 1;
		*i += 2;
		fl = 1;
	}
	else if (fmt[*i] == 'l')
	{
		ts->l = 1;
		(*i)++;
		fl = 1;
	}
	return (fl);
}

int		parse_specif1(char *fmt, t_spec *ts, int i)
{
	if (fmt[i] == 'h')
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
	return (i);
}

int		parse_spec(char *fmt, t_spec *ts, va_list ap)
{
	int i;

	init_struct(ts);
	i = parse_flags(fmt, ts);
	i = parse_width_bon(fmt, ts, i, ap);
	i = parse_width_bon1(fmt, ts, i, ap);
	i = parse_prec_bon(fmt, ts, i, ap);
	if (!parse_specif(fmt, ts, &i))
		i = parse_specif1(fmt, ts, i);
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

int		output_fstring1(char *s, int fl, int j)
{
	int k;

	k = 0;
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
	if (!fl)
	{
		j += ft_strlen(s);
		ft_putstr(s);
	}
	return (j);
}

int		output_fstring(va_list ap, char c, int j, t_spec *ts)
{
	char *s;
	int fl;

	fl = 0;
	if ((is_type(c)) || (!(is_type(c)) && 
		(ts->nil || ts->min || ts->width || ts->prec)))
	{
		s = print_format(ap, ts, c);
		if (!s)
			s = ft_strdup("(null)");
		j = output_fstring1(s, fl, j);
		fl = 0;
		ft_strdel(&s);
	}
	else
	{
		write(1, &c, 1);
		j++;
	}
	return (j);
}

int		parse_format(va_list ap, char *fmt)
{
	int i;
	int j;
	t_spec *ts;

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


int	ft_printf(char *fmt, ...)
{
	va_list ap;
	int n;

	va_start(ap, fmt);
	n = parse_format(ap, fmt);
	va_end(ap);
	return (n);
}

// int main()
// {
// 	ft_printf("\n");
// 	ft_printf("%%\n");
// 	ft_printf("%d\n", 42);
// 	ft_printf("%d%d\n", 42, 41);
// 	ft_printf("%d%d%d\n", 42, 43, 44);
// 	ft_printf("%ld\n", 2147483647);
// 	ft_printf("%lld\n", 9223372036854775807);
// 	ft_printf("%x\n", 505);
// 	ft_printf("%X\n", 505);
// 	ft_printf("%p\n", &ft_printf);
// 	ft_printf("%20.15d\n", 54321);
// 	ft_printf("%-10d\n", 3);
// 	ft_printf("% d\n", 3);
// 	ft_printf("%+d\n", 3);
// 	ft_printf("%010d\n", 1);
// 	ft_printf("%hhd\n", 0);
// 	ft_printf("%jd\n", 9223372036854775807);
// 	ft_printf("%zd\n", 4294967295);
// 	ft_printf("%\n");
// 	ft_printf("%U\n", 4294967295);
// 	ft_printf("%u\n", 4294967295);
// 	ft_printf("%o\n", 40);
// 	ft_printf("%%#08x\n", 42);
// 	ft_printf("%x\n", 1000);
// 	ft_printf("%#X\n", 1000);
// 	ft_printf("%s\n", NULL);
// 	ft_printf("%S\n", L"ݗݜशব");
// 	ft_printf("%s%s\n", "test", "test");
// 	ft_printf("%s%s%s\n", "test", "test", "test");
// 	ft_printf("%C\n", 15000);
// 	printf("\n--------------------------\n");
// 	printf("\n");
// 	printf("%%\n");
// 	printf("%d\n", 42);
// 	printf("%d%d\n", 42, 41);
// 	printf("%d%d%d\n", 42, 43, 44);
// 	printf("%ld\n", 2147483647);
// 	printf("%lld\n", 9223372036854775807);
// 	printf("%x\n", 505);
// 	printf("%X\n", 505);
// 	printf("%p\n", &printf);
// 	printf("%20.15d\n", 54321);
// 	printf("%-10d\n", 3);
// 	printf("% d\n", 3);
// 	printf("%+d\n", 3);
// 	printf("%010d\n", 1);
// 	printf("%hhd\n", 0);
// 	printf("%jd\n", 9223372036854775807);
// 	printf("%zd\n", 4294967295);
// 	printf("%\n");
// 	printf("%U\n", 4294967295);
// 	printf("%u\n", 4294967295);
// 	printf("%o\n", 40);
// 	printf("%%#08x\n", 42);
// 	printf("%x\n", 1000);
// 	printf("%#X\n", 1000);
// 	printf("%s\n", NULL);
// 	printf("%S\n", L"ݗݜशব");
// 	printf("%s%s\n", "test", "test");
// 	printf("%s%s%s\n", "test", "test", "test");
// 	printf("%C\n", 15000);
// return (0);
// }

// int main()
// {
// 	setlocale(LC_ALL, "en_US.UTF-8");
// 	//int strlen = 4;
// 	//int	x = L'ÁM-^L´';
// 	int n = ft_printf("%.p, %.0p", 0, 0);
// 	//ft_printf("@moulitest: %.10d", -42); 
// 	//ft_printf("{%05s}", "abc");
// 	//ft_printf("%-5.2s is a string", "this");
// 	//ft_printf("%zd", -9223372036854775808);
// 	//ft_printf("{%#.5x}", 1);
// 	//ft_printf("{%+03d}", 123456);
// 	//ft_printf("{%0.*d}", 5, 42);
// 	//ft_printf("%S\n", L"ݗݜशব");
// 	//ft_printf("%C, %15.5S", 0, L"米hып");
// 	//ft_printf("%15.4S", L"ÊM-M-^QÊM-^XØ‰∏M-ÂM-^O™ÁM-^L´„M-M-^B");
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
// 	n = printf("%.p, %.0p", 0, 0);
// 	//printf("DefPrintf: |%+011.8zd| %%!", (ssize_t)-567);
// 	printf("\n\t%d\t\n", n);
// 	printf("\n");
// 	//printf("%+07.5d", 1234);
// 	return (0);
// }

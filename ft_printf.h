/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 16:09:09 by akupriia          #+#    #+#             */
/*   Updated: 2017/12/30 16:09:10 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include "libft/libft.h"
#include <stdio.h>
#include <stdarg.h>

typedef struct	s_spec
{
	unsigned int 	space : 1;
	unsigned int	hash : 1;
	unsigned int	min : 1;
	unsigned int	plus : 1;
	unsigned int	nil : 1;
	unsigned int	dot : 1;
	unsigned int	asterisk1 : 1;
	unsigned int	asterisk2 : 1;
	unsigned int	width;
	unsigned int	prec;
	unsigned int	hh : 1;
	unsigned int	h : 1;
	unsigned int	l : 1;
	unsigned int	ll : 1;
	unsigned int	j : 1;
	unsigned int	z : 1;
}				t_spec;

#endif

// 0+# -width
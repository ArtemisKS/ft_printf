/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 18:37:46 by angavrel          #+#    #+#             */
/*   Updated: 2018/12/04 13:03:37 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

/*
** --------------------------- Librairies --------------------------------------
*/

# include "../libft/libft.h"
# include <stdarg.h>
# include <errno.h>
# define PF_BUF_SIZE	64
# define MAX(a, b)		b & ((a - b) >> 31) | a & (~(a - b) >> 31)
# define MIN(a, b)		a & ((a - b) >> 31) | b & (~(a - b) >> 31)

/*
** --------------------------- Masks Definition --------------------------------
*/

# define HASH_FL		(1 << 0)
# define SP_FL			(1 << 1)
# define PL_FL 			(1 << 2)
# define MIN_FL			(1 << 3)
# define NIL_FL			(1 << 4)
# define WCARD_FL		(1 << 5)
# define UPPERC_FL		(1 << 6)
# define SH_FL			(1 << 7)
# define SH_FL2			(1 << 8)
# define L_FL			(1 << 9)
# define L_FL2			(1 << 10)
# define IMAX_FL		(1 << 11)
# define SIZET_FL		(1 << 12)
# define PREC_FL		(1 << 14)
# define POINT_FL		(1 << 15)

/*
** --------------------------- ft_printf variables -----------------------------
** A) Printf writes the output and then returns the len (int)
** B) f stands for flag, defined above and extensively described in parsing.c
** C) min_length (digit after %) and precision (. after %) ~ parsing.c
** D) padding is the resulting from C and the output length.
** E) printed is the temporary len of chars to be send to the buffer
** F) fd is the file descriptor. 1 for ft_printf and can be any with ft_dprintf
** G) buffer_index and buff are related to the buffer function ~ buffer.c
** H) the variadic list (va_list ap) and the format are stored in the structure
** I) c is a temp char (as unsigned int) in order to have a single declaration
*/

typedef struct	s_global
{
	size_t		buffer_index;
	unsigned	c;
	int			len;
	int			min_length;
	int			precision;
	int			padding;
	int			printed;
	int			fd;
	int			n;
	int			i;
	short		f;
	char		buff[PF_BUF_SIZE];
	va_list		ap;
	char		*format;
}				t_global;

/*
** --------------------------- ft_printf main functions ------------------------
*/

int				ft_printf(const char *format, ...);
int				ft_dprintf(int fd, const char *format, ...);
char			*ft_sprintf(const char *format, ...);
void			parse_optionals(t_global *p);
void			cs_not_found(t_global *p);

/*
** --------------------------- number related functions ------------------------
** %d %D %i %f %F %b %B %o %O %u %U %h %H %a %A
*/

void			pf_putnb(t_global *p);
void			pf_putnb_base(int base, t_global *p);
void			itoa_printf(intmax_t d, t_global *p, int len);
void			itoa_base_printf(uintmax_t d, int b, t_global *p);
void			pf_putdouble(t_global *p, int n);

/*
** --------------------------- number related functions ------------------------
**  %s %S %c %C
*/

void			pf_putstr(t_global *p);
void			pf_putwstr(t_global *p);
void			pf_character(t_global *p, unsigned c);
void			pf_puterror(char *s, t_global *p);

/*
** --------------------------- miscellaneous functions -------------------------
*/

void			buffer(t_global *p, void *new, size_t size);
void			padding(t_global *p, int n);
void			print_pointer_address(t_global *p);

/*
** --------------------------- colors related defines --------------------------
*/

# define PF_RED			"\033[31m"
# define PF_GREEN		"\033[32m"
# define PF_YELLOW		"\033[33m"
# define PF_BLUE		"\033[34m"
# define PF_PURPLE		"\033[35m"
# define PF_CYAN		"\033[36m"
# define PF_EOC			"\033[36m"

#endif

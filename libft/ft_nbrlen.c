/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 20:13:33 by akupriia          #+#    #+#             */
/*   Updated: 2017/11/10 20:13:34 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_nbrlen(long long int n)
{
	int	size;

	size = 0;
	if (n < 0)
		size++;
	else if (n == 0)
		return (1);
	while (n)
	{
		n /= 10;
		size++;
	}
	return (size);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akupriia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/30 15:54:06 by akupriia          #+#    #+#             */
/*   Updated: 2017/12/30 15:54:07 by akupriia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#define BLURB "Authentic imitation!"

int main()
{
	const double RENT = 3852.99;
	int n = 1;
	printf("%d: *%8f*\n",n++, RENT);
	printf("%d: *%e*\n",n++, RENT);
	printf("%d: *%4.2f*\n",n++, RENT);
	printf("%d: *%3.1f*\n",n++, RENT);
	printf("%d: *%10.3f*\n",n++, RENT);
	printf("%d: *%10.3E*\n",n++, RENT);
	printf("%d: *%+4.2f*\n",n++, RENT);

	printf("%d: %x %X %#x\n",n++, 31, 31, 31);
	printf("%d: **%d**% d% d **\n",n++, 42, 42, -42);
	printf("%d: **%5d**%5.3d**%05d**%05.3d**\n",n++, 6, 6, 6, 6);
	printf("\n");

	printf("%d: [%2s]\n",n++, BLURB);
	printf("%d: [%24s]\n",n++, BLURB);
	printf("%d: [%24.5s]\n",n++, BLURB);
	printf("%d: [%-24.5s]\n",n++, BLURB);

	return 0;
}
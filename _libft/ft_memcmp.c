/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 13:11:33 by mogawa            #+#    #+#             */
/*   Updated: 2023/01/20 09:16:40 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// compares byte string s1 against byte string s2.
// return 0 = identical else return diff of c1 & c2
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*p1;
	const unsigned char	*p2;

	p1 = (const unsigned char *) s1;
	p2 = (const unsigned char *) s2;
	if (n == 0)
		return (0);
	while (n > 0)
	{
		if (*p1 != *p2)
		{
			return ((int)(*p1 - *p2));
		}
		p1++;
		p2++;
		n--;
	}
	return (0);
}

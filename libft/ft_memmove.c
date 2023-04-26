/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 11:12:40 by mogawa            #+#    #+#             */
/*   Updated: 2023/01/20 17:39:48 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// copies len bytes from string src to string dst and returns value of dest.
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*pdest;
	const unsigned char	*psrc;
	size_t				i;

	if (len == 0)
		return (dst);
	pdest = (unsigned char *) dst;
	psrc = (const unsigned char *) src;
	i = len;
	if (pdest > psrc)
	{
		while (0 < i)
		{
			pdest[i - 1] = psrc[i - 1];
			i--;
		}	
	}
	else
	{
		ft_memcpy(pdest, psrc, len);
	}
	return (dst);
}

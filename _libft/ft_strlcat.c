/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 13:38:07 by mogawa            #+#    #+#             */
/*   Updated: 2023/01/20 18:07:33 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// strlcat() appends string src to the end of dst. It will append at most
// dstsize - strlen(dst) - 1 characters.  It will then NUL-terminate, unless
// dstsize is 0 or the original dst string was longer than dstsize
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	char		*dptr;
	const char	*sptr;
	size_t		cpy_len;
	size_t		dlen;

	dptr = dst;
	sptr = src;
	cpy_len = dstsize;
	while (cpy_len-- != 0 && *dptr)
		dptr++;
	dlen = dptr - dst;
	cpy_len = dstsize - dlen;
	if (cpy_len == 0)
		return (dlen + ft_strlen(sptr));
	while (*sptr)
	{
		if (cpy_len > 1)
		{
			*dptr++ = *sptr;
			cpy_len--;
		}
		sptr++;
	}
	*dptr = '\0';
	return (dlen + (sptr - src));
}

// 1. dptr move to dstsize or end of dst (whichever smaller)
// 2. dlen = length btw dst and dptr
// 3. cpy_len = dstsize (user input) - dlen (min dstsize)
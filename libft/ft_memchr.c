/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 19:12:52 by mogawa            #+#    #+#             */
/*   Updated: 2023/01/20 17:35:22 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//locates the first occurrence of c(in unsigned char) in string s.
void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*str;
	unsigned char		chr;

	str = (const unsigned char *) s;
	chr = (unsigned char) c;
	while (n > 0)
	{
		if (*str == chr)
			return ((void *)str);
		str++;
		n--;
	}
	return (NULL);
}

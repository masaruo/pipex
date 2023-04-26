/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 10:28:10 by mogawa            #+#    #+#             */
/*   Updated: 2023/01/20 09:11:38 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//memset() writes len bytes of value c to the string b.
void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*str;
	size_t			n;

	str = (unsigned char *) b;
	n = 0;
	while (n < len)
	{
		str[n] = (unsigned char) c;
		n++;
	}
	return ((void *) str);
}

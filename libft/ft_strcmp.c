/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 07:52:54 by mogawa            #+#    #+#             */
/*   Updated: 2023/04/25 12:41:23 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// compare strings s1 and s2 with NOT more than n chars.
// l28 check empty strings & l38 check \0 as well.
int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	str1 = (unsigned char *) s1;
	str2 = (unsigned char *) s2;
	i = 0;
	while (1)
	{
		if (str1[i] != str2[i] || !str1[i] || !str2[i])
			return ((int)(str1[i] - str2[i]));
		i++;
	}
	return (0);
}

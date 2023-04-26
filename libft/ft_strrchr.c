/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 07:20:11 by mogawa            #+#    #+#             */
/*   Updated: 2023/01/20 18:17:28 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// locates the last occurrence of c (converted to a char) 
// in the string pointed to by s.
char	*ft_strrchr(const char *s, int c)
{
	const char	*str;
	char		chr;

	chr = (char) c;
	str = (const char *) s;
	while (*str)
		str++;
	while (1)
	{
		if (*str == chr)
			return ((char *)str);
		if (str == s)
			break ;
		str--;
	}
	return (NULL);
}

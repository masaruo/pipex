/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 07:13:17 by mogawa            #+#    #+#             */
/*   Updated: 2023/01/20 17:46:40 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// locate the first occurrence of 'c' in the string 's'
char	*ft_strchr(const char *s, int c)
{
	char		chr;
	char		*str;

	chr = (char) c;
	str = (char *) s;
	while (1)
	{
		if (*str == chr)
			return (str);
		if (*str == '\0')
			break ;
		str++;
	}
	return (NULL);
}

// use while(1) infinite loop to check when *str == '\0' as well
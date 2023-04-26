/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:30:34 by mogawa            #+#    #+#             */
/*   Updated: 2023/01/20 17:53:38 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// return a new string by concatinating s1 & s2
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		len;
	char		*res;
	char		*res_start;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1);
	len += ft_strlen(s2);
	res = malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (NULL);
	res_start = res;
	while (*s1)
		*res++ = *s1++;
	while (*s2)
		*res++ = *s2++;
	*res = '\0';
	return (res_start);
}

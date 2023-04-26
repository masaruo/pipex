/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:12:06 by mogawa            #+#    #+#             */
/*   Updated: 2023/01/20 17:52:04 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// applies func 'f' to each char of the string 's'.
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	n;

	if (!s || !f)
		return ;
	n = 0;
	while (s[n])
	{
		f(n, &s[n]);
		n++;
	}
}

// n = unsigned int as func(1st argv == unsigned int)
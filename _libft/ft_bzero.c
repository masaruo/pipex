/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 10:38:09 by mogawa            #+#    #+#             */
/*   Updated: 2023/01/20 17:17:19 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// write n zeroed bytes to the string s.
// if n is zero, bzero() does nothing.
void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

// actually bzero should use memset.
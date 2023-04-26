/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:50:40 by mogawa            #+#    #+#             */
/*   Updated: 2023/01/24 06:47:10 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(const char c)
{
	if (c == ' ' || c == '\f' || c == '\n' || c == '\r'
		|| c == '\t' || c == '\v')
		return (1);
	else
		return (0);
}

static const char	*ft_prefix(const char *s, int *is_minus)
{
	while (ft_isspace(*s))
		s++;
	if (*s == '-')
		*is_minus = -1;
	if (*s == '-' || *s == '+')
		s++;
	return (s);
}

// The atoi() function converts the initial portion of 
// the string pointed to by str to int representation.
int	ft_atoi(const char *str)
{
	int			is_minus;
	long		num;
	const char	*s;

	is_minus = 0;
	s = ft_prefix(str, &is_minus);
	num = 0;
	while (ft_isdigit(*s) && *s)
	{
		if (!is_minus && num > LONG_MAX / 10)
			return ((int)LONG_MAX);
		if (is_minus && num > LONG_MAX / 10)
			return ((int)LONG_MIN);
		num = num * 10;
		if (!is_minus && num > LONG_MAX - (*s - '0'))
			return ((int)LONG_MAX);
		if (is_minus && num - 1 > LONG_MAX - (*s - '0'))
			return ((int)LONG_MIN);
		num = num + (*s - '0');
		s++;
	}
	if (is_minus)
		return ((int)(num * -1));
	else
		return ((int)num);
}

// how to tackle LONGMIN 
// regarding num * 10
// num*10 > LMAX+1 => num>LMAX / 10 + 1 / 10 => num - (1/10) > LMAX / 10
// -----
// regarding num + (*s - '0')
// num + (*s - '0') > LONG MAX + 1
// num > LMAX + 1 - (*s - '0')
// num - 1 > LMAX - (*s - '0')
// int main(void)
// {
// // 	// char n[] = "9223372036854775806";// LONGMAX - 1
// 	// char n[] = "-9223372036854775807";// LONGMIN + 1
// 	char n[] = "9223372036854775808";// LONGMAX + 1
// 	// char n[] = "-9223372036854775809";// LONGMIN - 1
// 	int res = ft_atoi(n);
// 	printf("my => %d\n", res);
// 	printf("pc => %d\n", atoi(n));
// 	return 1;
// }
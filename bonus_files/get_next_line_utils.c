/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:46:57 by mogawa            #+#    #+#             */
/*   Updated: 2023/02/15 23:58:41 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// check if lf is in string. if yes, return index, else return 0;
size_t	ft_lf_loc(char const *s)
{
	size_t	n;

	if (s == NULL)
		return (0);
	n = 0;
	while (1)
	{	
		if (s[n] == '\0')
			break ;
		if (s[n] == LF)
		{
			n++;
			return (n);
		}
		n++;
	}
	return (0);
}

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

/*
if output has an error then outlook == NULL which will be returned.
if *saved has an error then back to GNL and if(saved == NULL) check.
*/
char	*ft_output(char **saved, size_t lf_loc)
{
	char	*output;
	char	*tmp;

	output = ft_strndup(*saved, lf_loc);
	tmp = *saved;
	*saved = ft_strndup((*saved) + lf_loc, ft_strlen((*saved) + lf_loc));
	ft_free_null(tmp);
	return (output);
}

char	*ft_read_finish(char **saved, ssize_t flg)
{
	char	*tmp;

	if (flg == READ_ERR || **saved == '\0')
	{
		free(*saved);
		*saved = NULL;
	}
	else if (flg == READ_EOF)
	{
		tmp = *saved;
		*saved = NULL;
		return (tmp);
	}
	return (NULL);
}

/*
strjoin error => saved == NULL then if (saved == NULL) check.
*/
void	ft_read_success(char **saved, char *buf, ssize_t n_read)
{
	char	*tmp;

	buf[n_read] = '\0';
	tmp = *saved;
	*saved = ft_strjoin(*saved, buf);
	ft_free_null(tmp);
}

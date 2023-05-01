/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 21:50:28 by mogawa            #+#    #+#             */
/*   Updated: 2023/02/15 23:50:13 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char const *s)
{
	size_t	n;

	n = 0;
	while (s[n])
	{
		n++;
	}
	return (n);
}

void	ft_free_null(char *s)
{
	free(s);
	s = NULL;
}

char	*ft_strndup(char *s, size_t len)
{
	char	*res;
	size_t	n;

	res = malloc(sizeof(char) * (len + SIZE_NULLCHAR));
	if (res == NULL)
		return (NULL);
	n = 0;
	while (n < len)
	{
		res[n] = s[n];
		n++;
	}
	res[n] = '\0';
	return (res);
}

/*
!標準入力またはファイルから読み込んだSTRINGについて、改行があれば、そこまでを文字列としてリターン
*/
char	*get_next_line(int fd)
{
	char		buf[BUFFER_SIZE + (size_t)1];
	static char	*saved;
	size_t		lf_loc;
	ssize_t		n_read;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0))
		return (NULL);
	if (saved == NULL)
		saved = ft_strndup("", 0);
	while (1)
	{
		if (saved == NULL)
			return (NULL);
		lf_loc = ft_lf_loc(saved);
		if (lf_loc)
			return (ft_output(&saved, lf_loc));
		else if (!lf_loc)
		{
			n_read = read(fd, buf, BUFFER_SIZE);
			if (n_read >= READ_SUCCESS)
				ft_read_success(&saved, buf, n_read);
			else
				return (ft_read_finish(&saved, n_read));
		}
	}
}

/*
! ssize_t	read(int fildes, void *buf, size_t nbyte)
read 'nbytes' of descripter 'fildes' into 'buf'.
return is number actually read / 0 if EOF
-1 is error and set errorno to indicate error.
read will fail if the nbyte > INT_MAX and not attempt partial read.
---
upper limit for fd = ulimit -n (check)
*/
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 23:38:21 by mogawa            #+#    #+#             */
/*   Updated: 2023/05/01 19:54:58 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex_bonus.h"
#include "get_next_line.h"

void	ft_parent_proc(int pfd[], int *prev)
{
	close(pfd[WRITE]);
	close(*prev);
	*prev = dup(pfd[READ]);
	close(pfd[READ]);
}

void	ft_error(char *msg, bool to_exit)
{
	perror(msg);
	if (to_exit)
		exit(-1);
}

int	xdup2(int oldfd, int newfd, bool to_kill)
{
	int	res;

	res = 0;
	res = dup2(oldfd, newfd);
	close(oldfd);
	if (res == -1)
	{
		if (to_kill)
			ft_error("PIPEX", true);
		else
			ft_error("PIPEX", false);
	}
	return (res);
}

// int	ft_strcmp(const char *s1, const char *s2)
// {
// 	unsigned char	*str1;
// 	unsigned char	*str2;
// 	size_t			i;

// 	str1 = (unsigned char *) s1;
// 	str2 = (unsigned char *) s2;
// 	i = 0;
// 	while (1)
// 	{
// 		if (str1[i] != str2[i] || !str1[i] || !str2[i])
// 			return ((int)(str1[i] - str2[i]));
// 		i++;
// 	}
// 	return (0);
// }

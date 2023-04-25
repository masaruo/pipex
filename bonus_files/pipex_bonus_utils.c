/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 23:38:21 by mogawa            #+#    #+#             */
/*   Updated: 2023/04/25 16:20:22 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex_bonus.h"
#include "get_next_line.h"

void	ft_error(char *msg, bool to_exit)
{
	perror(msg);
	if (to_exit)
		exit(-1);
}

int	xdup2(int oldfd, int newfd)
{
	int	res;

	res = 0;
	res = dup2(oldfd, newfd);
	close(oldfd);
	if (res == -1)
	{
		ft_error("PIPEX", true);
	}
	return (res);
}

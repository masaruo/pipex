/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 23:38:21 by mogawa            #+#    #+#             */
/*   Updated: 2023/05/02 19:02:31 by mogawa           ###   ########.fr       */
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
		exit(1);
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

int	ft_get_hdoc(char *end)
{
	int		fd;
	char	*tmp;

	fd = open("tmpfile", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		ft_error("failed to create tempfile for here_doc", false);
	while (1)
	{
		ft_putstr_fd("here_doc:", STDOUT_FILENO);
		tmp = get_next_line(STDIN_FILENO);
		if (ft_strncmp(end, ft_strtrim(tmp, "\n"), ft_strlen(end)) == 0)
		{
			free(tmp);
			break ;
		}
		ft_putstr_fd(tmp, fd);
		free(tmp);
	}
	return (open("tmpfile", O_RDONLY));
}

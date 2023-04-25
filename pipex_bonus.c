/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 17:24:05 by mogawa            #+#    #+#             */
/*   Updated: 2023/04/25 15:59:46 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex_bonus.h"
#include "get_next_line.h"

static char	*ft_get_path(char *cmd)
{
	int		res;
	char	*cmdpath;

	cmdpath = ft_strjoin("/bin/", cmd);
	res = access(cmdpath, F_OK);
	if (res == 0)
		return (cmdpath);
	else
		return (ft_strjoin("/usr/bin/", cmd));
}

static void	ft_error(char *msg, bool to_exit)
{
	perror(msg);
	if (to_exit)
		exit(-1);
}

static int	xdup2(int oldfd, int newfd)
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

static void	ft_loop_argv(int fd, char *cmd, int *prev, int pfd[])
{
	extern char	**environ;
	pid_t		pid;

	pid = fork();
	if (pid == 0)
	{
		if (fd == -1)
			ft_error(cmd, true);
		xdup2(fd, STDIN_FILENO);
		if (*prev != STDIN_FILENO)
			xdup2(*prev, STDIN_FILENO);
		xdup2(pfd[WRITE], STDOUT_FILENO);
		execve(ft_get_path(ft_split(cmd, ' ')[0]), ft_split(cmd, ' '), environ);
		ft_error(cmd, true);
	}
	else if (pid > 0)
	{
		close(*prev);
		close(pfd[WRITE]);
		*prev = pfd[READ];
		wait(NULL);
	}
	else
		ft_error(cmd, true);
}

static void	ft_outfile(int *prev_pipe, char *cmd, char *outfile)
{
	int			fd_output;
	extern char	**environ;
	char		**argv;
	pid_t		pid;

	if (*prev_pipe != STDIN_FILENO)
		xdup2(*prev_pipe, STDIN_FILENO);
	fd_output = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd_output == -1)
		ft_error(cmd, true);
	xdup2(fd_output, STDOUT_FILENO);
	pid = fork();
	if (pid == 0)
	{
		argv = ft_split(cmd, ' ');
		execve(ft_get_path(argv[0]), argv, environ);
		ft_error(cmd, true);
	}
	else if (pid > 0)
		wait(NULL);
	else
		ft_error(cmd, true);
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
		if (ft_strcmp(end, ft_strtrim(tmp, "\n")) == 0)
		{
			free(tmp);
			break ;
		}
		ft_putstr_fd(tmp, fd);
		free(tmp);
	}
	return (open("tmpfile", O_RDONLY));
}

int	main(int argc, char **argv)
{
	int		n;
	int		pfd[2];
	int		prev_pipe;
	int		fd_input;

	if (argc < 5)
		ft_error("invalid number of argvs", false);
	else
	{
		n = 2;
		if (ft_strcmp(argv[1], "here_doc") == 0)
		{
			fd_input = ft_get_hdoc(argv[2]);
			n = 3;
		}
		else
			fd_input = open(argv[1], O_RDONLY);
		prev_pipe = STDIN_FILENO;
		while (n < argc - 2)
		{
			pipe(pfd);
			ft_loop_argv(fd_input, argv[n], &prev_pipe, pfd);
			n++;
		}
		ft_outfile(&prev_pipe, argv[argc - 2], argv[argc - 1]);
	}
	return (0);
}

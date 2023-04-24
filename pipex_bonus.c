/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 17:24:05 by mogawa            #+#    #+#             */
/*   Updated: 2023/04/24 23:45:46 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex_bonus.h"

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

static void	ft_loop_argv(int fd, char *cmd, int *prev, int pfd[], int n)
{
	extern char	**environ;
	pid_t		pid;

	pid = fork();
	if (pid == 0)
	{
		if (fd == -1)
			ft_error(cmd, true);
		if (n == 2)
			xdup2(fd, STDIN_FILENO);
		else if (*prev != STDIN_FILENO)
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
	}
	else
		ft_error(cmd, true);
}

static void	ft_output(int *prev_pipe, char *cmd, char *outfile, bool is_hdoc)
{
	int			fd_output;
	extern char	**environ;
	char		**argv;
	pid_t		pid;

	if (*prev_pipe != STDIN_FILENO)
		xdup2(*prev_pipe, STDIN_FILENO);
	if (is_hdoc)
		fd_output = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else
		fd_output = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0777);
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

int	main(int argc, char **argv)
{
	int		n;
	int		pfd[2];
	int		prev_pipe;
	int		fd_input;
	bool	is_hdoc;

	is_hdoc = false;
	if (argc < 5)
		ft_error("invalid number of argvs", false);
	else
	{
		if (argv[1] == "here_doc")
			is_hdoc = true;
		n = 2;
		prev_pipe = STDIN_FILENO;
		fd_input = open(argv[1], O_RDONLY);
		while (n < argc - 2)
		{
			pipe(pfd);
			ft_loop_argv(fd_input, argv[n], &prev_pipe, pfd, n);
			n++;
		}
		ft_output(&prev_pipe, argv[argc - 2], argv[argc - 1], is_hdoc);
	}
	return (0);
}

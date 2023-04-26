/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 17:24:05 by mogawa            #+#    #+#             */
/*   Updated: 2023/04/26 11:37:53 by mogawa           ###   ########.fr       */
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

static void	ft_loop_argv(int fd, char *cmd, int *prev, int cnt)
{
	extern char	**environ;
	int			pfd[2];
	pid_t		pid;

	if (pipe(pfd) == -1)
		ft_error("error in multiple pipe", false);
	if (fd == -1)
		ft_error(cmd, false);
	pid = fork();
	if (pid == 0)
	{
		close(pfd[READ]);
		if (cnt == 0)
			xdup2(fd, STDIN_FILENO, true);
		else if (*prev != STDIN_FILENO)
			xdup2(*prev, STDIN_FILENO, true);
		xdup2(pfd[WRITE], STDOUT_FILENO, true);
		execve(ft_get_path(ft_split(cmd, ' ')[0]), ft_split(cmd, ' '), environ);
		ft_error(cmd, false);
	}
	else if (pid > 0)
		ft_parent_proc(pfd, prev);
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
		xdup2(*prev_pipe, STDIN_FILENO, false);
	fd_output = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd_output == -1)
		ft_error(cmd, true);
	xdup2(fd_output, STDOUT_FILENO, false);
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
		ft_error(cmd, false);
}

static int	ft_get_hdoc(char *end)
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
	int		prev_pipe;
	int		fd_input;
	int		cnt;

	if (argc < 5)
		ft_error("invalid number of argvs", false);
	else
	{
		n = 2;
		if (ft_strcmp(argv[1], "here_doc") == 0)
			fd_input = ft_get_hdoc(argv[n++]);
		else
			fd_input = open(argv[1], O_RDONLY);
		prev_pipe = STDIN_FILENO;
		cnt = 0;
		while (n < argc - 2)
			ft_loop_argv(fd_input, argv[n++], &prev_pipe, cnt++);
		ft_outfile(&prev_pipe, argv[argc - 2], argv[argc - 1]);
		while (cnt-- > 1)
			wait(NULL);
		if (access("tmpfile", F_OK) == 0)
			unlink("tmpfile");
	}
	return (0);
}

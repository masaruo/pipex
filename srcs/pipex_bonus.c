/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 17:24:05 by mogawa            #+#    #+#             */
/*   Updated: 2023/05/02 16:23:45 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex_bonus.h"
#include "get_next_line.h"

static char	**ft_get_env(void)
{
	extern char	**environ;
	char		*envpath;
	char		**env;
	int			i;

	i = 0;
	while (environ[i])
	{
		envpath = environ[i];
		if (ft_strncmp(environ[i], "PATH", 4) == 0)
			break ;
		i++;
	}
	env = ft_split(ft_strchr(envpath, '=') + 1, ':');
	return (env);
}

static char	*ft_get_path(char *cmd)
{
	char		**env;
	char		*cmdpath;
	int			i;

	if (!cmd || !*cmd)
		ft_error("empty command", true);
	if (cmd[0] == '.')
		ft_error("command error", true);
	if (cmd[0] == '/')
		return (cmd);
	env = ft_get_env();
	i = 0;
	while (env[i])
	{
		cmd = ft_strjoin("/", cmd);
		cmdpath = ft_strjoin(env[i], cmd);
		if (access(cmdpath, X_OK) == 0)
			break ;
		i++;
	}
	free(env);
	return (cmdpath);
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
		ft_error(cmd, true);
	}
	else if (pid > 0)
		ft_parent_proc(pfd, prev);
	else
		ft_error("fork", true);
}

static void	ft_outfile(int *prev_pipe, char *cmd, char *outfile, char *av1)
{
	int			fd_output;
	extern char	**environ;
	char		**argv;
	pid_t		pid;

	if (*prev_pipe != STDIN_FILENO)
		xdup2(*prev_pipe, STDIN_FILENO, false);
	if (ft_strncmp(av1, "here_doc", ft_strlen("here_doc")) == 0)
		fd_output = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
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
	else if (pid < 0)
		ft_error(cmd, false);
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
		if (ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc")) == 0)
			fd_input = ft_get_hdoc(argv[n++]);
		else
			fd_input = open(argv[1], O_RDONLY);
		prev_pipe = STDIN_FILENO;
		cnt = 0;
		while (n < argc - 2)
			ft_loop_argv(fd_input, argv[n++], &prev_pipe, cnt++);
		ft_outfile(&prev_pipe, argv[argc - 2], argv[argc - 1], argv[1]);
		while (cnt-- > 0)
			wait(NULL);
		unlink("tmpfile");
	}
	return (0);
}

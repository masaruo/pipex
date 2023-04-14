/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 17:24:05 by mogawa            #+#    #+#             */
/*   Updated: 2023/04/14 22:56:00 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

// https://www.geeksforgeeks.org/exec-family-of-functions-in-c/

char	*ft_get_path(char *cmd)
{
	int		res;
	char	*cmdpath;
	char	*path;

	cmdpath = ft_strjoin("/bin/", cmd);
	res = access(cmdpath, F_OK);
	if (res == 0)
		return (cmdpath);
	else
		return (ft_strjoin("/usr/bin/", cmd));
}

void	ft_exec_cmd(char *cmd)
{
	extern char	**environ;
	char		**argv;

	argv = ft_split(cmd, ' ');
	execve(ft_get_path(argv[0]), argv, environ);
	// error handle
	perror("execve");
	exit(1);
}

int	ft_open(const char *path, int flags, int mode)
{
	int	fd;

	if (!mode)
		fd = open(path, flags);
	else
		fd = open(path, flags, mode);
	return (fd);
}

void	ft_pipex(char *infile, char *cmd1, char *cmd2, char *outfile)
{
	pid_t		pid;
	size_t		status;
	char 		**argv;
	int			fd_infile;
	int			fd_outfile;
	int			n;
	int			n_pipe;
	int			fds[2];

	fd_infile = ft_open(infile, O_RDONLY, false);
	fd_outfile = ft_open(outfile, O_WRONLY, O_CREAT);
	n = dup2(fd_infile, STDIN_FILENO);
	ft_exec_cmd(cmd1);
	n_pipe = pipe(fds);
	pid = fork();
	if (pid < 0)
	{
		// todo error
	}
	if (pid == 0)
	{
	close(fds[1]);
	n = dup2(STDOUT_FILENO, fd_outfile);
	ft_exec_cmd(cmd2);
	//! write? get_next_line?
	close(fd_outfile);
	}
	else
	{
		printf("parent process\n");
		close(fds[0]);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			
		}
	}
}

int	main(int argc, char **argv)
{
	size_t	i;

	if (argc < 5)
	{
		// todo error
	}
	else
	{
		ft_pipex(argv[1], argv[2], argv[3], argv[4]);
	}
	return (0);
}
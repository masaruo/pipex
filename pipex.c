/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 17:24:05 by mogawa            #+#    #+#             */
/*   Updated: 2023/04/18 18:00:07 by mogawa           ###   ########.fr       */
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

void	ft_exec_cmd(char *cmd1, char *cmd2, int fd_out)
{
	pid_t		pid;
	int			status;
	extern char	**environ;
	char		**argv;
	int			pipe_fd[2];

	pipe(pipe_fd);
	pid = fork();
	if (pid < 0)
	{
		//todo error handle
		exit(1);
	}
	if (pid == 0)
	{
		printf("child!\n");
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		argv = ft_split(cmd1, ' ');
		execve(ft_get_path(argv[0]), argv, environ);
		perror(argv[1]);
		exit(99);
	}
	else
	{
		// printf("%s", cmd2);
		close(pipe_fd[1]);
		wait(&status);
		printf("parent!\n");
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
		argv = ft_split(cmd2, ' ');
		execve(ft_get_path(argv[0]), argv, environ);
		perror(argv[1]);
		exit(0);
	}
}

void	ft_pipex(char *infile, char *cmd1, char *cmd2, char *outfile)
{
	int	fd_in;
	int	fd_out;

	fd_in = open(infile, O_RDONLY);
	// fd_out = open(outfile, O_RDONLY | O_CREAT, S_IRWXU);// mode - unmask to get persmission right
	fd_out = open(outfile, O_RDWR);// mode - unmask to get persmission right
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	ft_exec_cmd(cmd1, cmd2, fd_out);
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
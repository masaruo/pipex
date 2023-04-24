/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 17:24:05 by mogawa            #+#    #+#             */
/*   Updated: 2023/04/24 20:27:51 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

char	*ft_get_path(char *cmd)
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

static void	ft_error(char *msg, bool do_exit)
{
	perror(msg);
	if (do_exit == true)
		exit(-1);
}

void	ft_loop_argv(char *cmd, int	*prev_pipe, int pfd[], int n)
{
	char		**argv;
	extern char	**environ;
	pid_t		pid;
	int			fd_input;

	pid = fork();
	if (pid == 0)
	{
		if (n == 2)
		{
			fd_input = open(cmd, O_RDONLY);
			if(fd_input == -1)
				ft_error(cmd, true);
			else
			{
				dup2(fd_input, STDIN_FILENO);
				close(fd_input);
			}
		}
		else if (*prev_pipe != STDIN_FILENO)
		{
			dup2(*prev_pipe, STDIN_FILENO);
			close(*prev_pipe);
		}
		dup2(pfd[WRITE], STDOUT_FILENO);
		close(pfd[WRITE]);
		argv = ft_split(cmd, ' ');
		execve(ft_get_path(argv[0]), argv, environ);
		perror("execve failed");
		exit(1);	
	}
	else if (pid > 0)
	{
		close(*prev_pipe);
		close(pfd[WRITE]);
		*prev_pipe = pfd[READ];
		wait(NULL);
	}
	else
	{
	// todo fork error
	}
}

void	ft_output(int *prev_pipe, char *cmd, char *outfile)
{
	int			fd_output;
	char		**argv;
	extern char	**environ;

	if (*prev_pipe != STDIN_FILENO)
	{
		dup2(*prev_pipe, STDIN_FILENO);
		close(*prev_pipe);
	}
	fd_output = open(outfile, O_WRONLY | O_CREAT, 0777);
	// todo open error
	dup2(fd_output, STDOUT_FILENO);
	close(fd_output);
	if (fork() == 0)//! fork error
	{
		argv = ft_split(cmd, ' ');
		execve(ft_get_path(argv[0]), argv, environ);
		perror("last execve fail");
		exit(1);
	}
	wait(NULL);
}

int	main(int argc, char **argv)
{
	int		n;
	int		pfd[2];
	int		prev_pipe;

	if (argc < 5)
	{
		// todo error
	}
	else
	{
		n = 2;
		prev_pipe = STDIN_FILENO;
		while (n < argc - 2)
		{
			pipe(pfd);
			ft_loop_argv(argv[n], &prev_pipe, pfd, n);
			n++;
		}
		ft_output(&prev_pipe, argv[argc - 2], argv[argc - 1]);
	}
	return (0);
}

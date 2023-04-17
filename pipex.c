/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 17:24:05 by mogawa            #+#    #+#             */
/*   Updated: 2023/04/15 20:19:57 by mogawa           ###   ########.fr       */
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

// void	ft_exec_cmd(char *cmd1, char *cmd2)
// {
// 	pid_t		pid;
// 	size_t		status;
// 	extern char	**environ;
// 	char		**argv;

// 	pid = fork();
// 	if (pid < 0)
// 	{
// 		//! error handle
// 		exit(1);
// 	}
// 	if (pid == 0)
// 	{
// 		argv = ft_split(cmd1, ' ');
// 		execve(ft_get_path(argv[0]), argv, environ);
// 		perror(argv[1]);
// 		exit(99);
// 	}
// 	else
// 	{
// 		argv = ft_split(cmd2, ' ');
		
// 	}
// }

void	ft_pipex(char *infile, char *cmd1, char *cmd2, char *outfile)
{
	char 		**argv;
	int			fd_infile;
	int			fd_outfile;
	int			n;
	int			n_pipe;
	int			p_fds[2];

	fd_infile = open(infile, O_RDONLY);
	fd_outfile = open(outfile, O_WRONLY | O_CREAT | O_TRUNC);// mode - unmask to get persmission right
	n = dup2(fd_infile, STDIN_FILENO);
	ft_exec_cmd(cmd1);
	// pipe(p_fds);
	//パイプ
	// パイプの後半
	// ft_exec_cmd(cmd2);
	// n = dup2(STDOUT_FILENO, fd_outfile);
	close(fds[1]);
	close(fd_outfile);
	close(fds[0]);
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
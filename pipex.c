/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 17:24:05 by mogawa            #+#    #+#             */
/*   Updated: 2023/04/26 17:43:32 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

static char	*ft_get_path(char *cmd)
{
	int		res_bin;
	int		res_usr;
	char	*cmdpath_bin;
	char	*cmdpath_usr;

	cmdpath_bin = ft_strjoin("/bin/", cmd);
	res_bin = access(cmdpath_bin, F_OK);
	cmdpath_usr = ft_strjoin("/usr/bin/", cmd);
	res_usr = access(cmdpath_usr, F_OK);
	if (res_usr == 0)
		return (cmdpath_usr);
	else if (res_bin == 0)
		return (cmdpath_bin);
	else
	{
		ft_error("command not found", true);
		return (cmd);
	}
}

static void	ft_error(char *msg, bool do_exit)
{
	perror(msg);
	if (do_exit == true)
		exit(-1);
}

static void	ft_input(char *infile, char *cmd, int pfd[])
{
	int			fd_infile;
	char		**argv;
	extern char	**environ;

	close(pfd[READ]);
	fd_infile = open(infile, O_RDONLY);
	if (fd_infile == -1)
		ft_error(infile, true);
	if (dup2(fd_infile, STDIN_FILENO) == -1)
		ft_error(infile, true);
	close(fd_infile);
	if (dup2(pfd[WRITE], STDOUT_FILENO) == -1)
		ft_error(infile, true);
	close(pfd[WRITE]);
	argv = ft_split(cmd, ' ');
	execve(ft_get_path(argv[0]), argv, environ);
	ft_error(argv[0], true);
}

static void	ft_output(char *outfile, char *cmd, int pfd[])
{
	int			fd_outfile;
	char		**argv;
	extern char	**environ;

	close(pfd[WRITE]);
	fd_outfile = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd_outfile == -1)
		ft_error(outfile, false);
	if (dup2(pfd[READ], STDIN_FILENO) == -1)
		ft_error(outfile, false);
	close(pfd[READ]);
	if (dup2(fd_outfile, STDOUT_FILENO) == -1)
		ft_error(outfile, false);
	close(fd_outfile);
	argv = ft_split(cmd, ' ');
	execve(ft_get_path(argv[0]), argv, environ);
	ft_error(argv[0], false);
}

int	main(int argc, char **argv)
{
	int		pfd[2];
	pid_t	pid;

	if (argc == 5)
	{
		if (pipe(pfd) == 0)
		{
			pid = fork();
			if (pid == 0)
			{
				ft_input(argv[1], argv[2], pfd);
			}
			else if (pid > 0)
			{
				ft_output(argv[4], argv[3], pfd);
				wait(NULL);
			}
			else
				ft_error("FORKING FAILED", false);
		}
		else
			ft_error("PIPING FAILED", false);
	}
	return (0);
}

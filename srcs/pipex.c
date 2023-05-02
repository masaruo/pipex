/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 17:24:05 by mogawa            #+#    #+#             */
/*   Updated: 2023/05/02 13:53:56 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

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
	extern char	**environ;
	char		**env;
	char		*cmdpath;
	int			i;

	if (cmd[0] == '/' || cmd[0] == '.' || !cmd || !*cmd)
	{
		ft_error("command error", false);
		return ("dakjflsdjfladsjfl;asjdflkasdjflk;asj");
	}
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
				ft_input(argv[1], argv[2], pfd);
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
	else
		ft_error("Invalid number of arguments", true);
	return (0);
}

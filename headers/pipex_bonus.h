/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 17:24:11 by mogawa            #+#    #+#             */
/*   Updated: 2023/04/26 10:06:29 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# define WRITE 1
# define READ 0

# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stddef.h>

void	ft_error(char *msg, bool to_exit);
int		xdup2(int oldfd, int newfd, bool to_kill);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_parent_proc(int pfd[], int *prev);

#endif
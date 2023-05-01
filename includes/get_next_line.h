/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 10:51:29 by mogawa            #+#    #+#             */
/*   Updated: 2023/02/15 23:59:20 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

# define READ_EOF 0
# define READ_ERR -1
# define READ_SUCCESS 1
# define SIZE_NULLCHAR 1
# define LF '\n'

char	*get_next_line(int fd);
char	*ft_output(char **saved, size_t lf_loc);
size_t	ft_strlen(char const *s);
size_t	ft_lf_loc(char const *s);
char	*ft_strndup(char *s, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_free_null(char *s);
char	*ft_read_finish(char **saved, ssize_t flg);
void	ft_read_success(char **saved, char *buf, ssize_t n_read);

#endif

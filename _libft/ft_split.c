/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:18:48 by mogawa            #+#    #+#             */
/*   Updated: 2023/01/23 16:44:01 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// free all childs strs first then free parent arr.
static void	ft_free_all(char **arr)
{
	char	**tmp;

	tmp = arr;
	while (*arr != NULL)
	{
		free(*arr);
		arr++;
	}
	free(tmp);
}

static size_t	ft_cntchar(const char *s, char c)
{
	size_t		n;

	n = 0;
	while (1)
	{
		if (*s != c && *s)
		{
			n++;
			while (*s != c && *s)
				s++;
		}
		if (*s == '\0')
			break ;
		s++;
	}
	return (n);
}

static char	*ft_strndup(const char *s1, size_t len)
{
	char		*res;
	size_t		n;

	res = malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (NULL);
	n = 0;
	while (s1[n] && n < len)
	{
		res[n] = s1[n];
		n++;
	}
	res[n] = '\0';
	return (res);
}

// return 0 for malloc error else number 'cnt'.
// cal how many cnt and exe strndup to add child arrs to parent arr 'res'
static size_t	ft_putstr_arr(char **res, char const *str, size_t *n, char c)
{
	size_t	cnt;

	cnt = 0;
	while (str[cnt] && str[cnt] != c)
		cnt++;
	if (cnt > 0)
	{
		res[*n] = ft_strndup(str, cnt);
		if (res[*n] == NULL)
		{
			ft_free_all(res);
			return (0);
		}
		*n = *n + 1;
	}
	if (cnt == 0)
		return (1);
	else
		return (cnt);
}

//array of strings obtained by splitting 's' by delimiter 'c'
char	**ft_split(char const *s, char c)
{
	char		**res;
	char const	*str;
	size_t		nbr_c;
	size_t		n;
	size_t		cnt;

	if (!s)
		return (NULL);
	str = s;
	nbr_c = ft_cntchar(s, c);
	res = malloc(sizeof(char *) * (nbr_c + 1));
	if (res == NULL)
		return (NULL);
	res[nbr_c] = NULL;
	n = 0;
	while (*str)
	{
		cnt = ft_putstr_arr(res, str, &n, c);
		if (cnt == 0)
			return (NULL);
		str = str + cnt;
	}
	return (res);
}

// int    main(void)
// {
//     char    **str;
//     char     **tmp;
//     // char    input[] = "      split       this for   me  !       ";
//     char    input[] = "      split       this for   me  !       ";
//     str = ft_split(input, ' ');
//     tmp = str;
//     size_t i;
//     i =0;
//     while (str[i])
//     {
//         printf("%s\n", str[i]);
//         i++;
//     }
//     // ft_free_all(tmp);
//     free(tmp);
//     // check();
//     // system("leaks -q a.out");
//     return (1);
// }
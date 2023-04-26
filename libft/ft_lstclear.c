/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 09:22:38 by mogawa            #+#    #+#             */
/*   Updated: 2023/01/20 16:08:35 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// del then free the elem incl all childs and ptr to the list to NULL
void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*crnt;
	t_list	*prev;

	if (!lst || !*lst || !del)
		return ;
	crnt = *lst;
	while (crnt != NULL)
	{	
		prev = crnt;
		crnt = crnt->next;
		ft_lstdelone(prev, del);
	}
	*lst = NULL;
}

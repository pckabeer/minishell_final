/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpanikka <kpanikka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 14:17:04 by kpanikka          #+#    #+#             */
/*   Updated: 2022/03/08 08:28:24 by kpanikka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*n_lst;

	while (*lst)
	{
		del((*lst)->content);
		n_lst = *lst;
		*lst = n_lst -> next;
		free(n_lst);
	}
}

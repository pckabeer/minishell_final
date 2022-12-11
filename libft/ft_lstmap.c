/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpanikka <kpanikka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 22:55:04 by kpanikka          #+#    #+#             */
/*   Updated: 2022/09/19 18:24:45 by kpanikka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*lst_ptr;

	if (!lst)
		return (NULL);
	new_lst = ft_lstnew(f(lst->content));
	if (!new_lst)
		return (NULL);
	lst_ptr = new_lst;
	lst = lst->next;
	while (lst)
	{
		lst_ptr->next = ft_lstnew(f(lst->content));
		if (!lst_ptr->next)
		{
			ft_lstclear(&new_lst, del);
			return (new_lst);
		}
		lst_ptr = lst_ptr->next;
		lst = lst->next;
	}
	return (new_lst);
}

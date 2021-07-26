/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarthus <dkarthus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 16:01:04 by dkarthus          #+#    #+#             */
/*   Updated: 2020/12/02 20:03:43 by dkarthus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ptr;
	t_list	*ptr2;
	t_list	*in;

	ptr = lst;
	if (!lst || !f)
		return (NULL);
	in = ft_lstnew(f(ptr->content));
	if (!in)
		return (NULL);
	ptr = ptr->next;
	ptr2 = in;
	while (ptr)
	{
		ptr2->next = ft_lstnew(f(ptr->content));
		if (!ptr2->next)
		{
			ft_lstclear(&in, del);
			return (NULL);
		}
		ptr = ptr->next;
		ptr2 = ptr2->next;
	}
	return (in);
}

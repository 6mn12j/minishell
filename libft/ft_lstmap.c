/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 22:43:21 by minjupar          #+#    #+#             */
/*   Updated: 2021/05/12 10:40:10 by minjupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*temp;
	t_list	*curr;

	temp = 0;
	if (!lst || !f)
		return (0);
	while (lst)
	{
		if (!(curr = ft_lstnew(f(lst->content))))
		{
			ft_lstclear(&temp, del);
			return (0);
		}
		ft_lstadd_back(&temp, curr);
		lst = lst->next;
	}
	return (temp);
}

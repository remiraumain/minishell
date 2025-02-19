/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 09:41:49 by rraumain          #+#    #+#             */
/*   Updated: 2024/10/30 11:20:07 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Delete and free the given node and every successor of that node.
 * 
 * Deletes and frees the given node and every successor of that node, using the 
 * function `del` and free(3). Finally, the pointer to the list must be set to 
 * `NULL`.
 * 
 * @param lst The address of a pointer to a node.
 * @param del The address of the function used to delete the content of the 
 * node.
 */
void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*next;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		next = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = next;
	}
	lst = NULL;
	free(lst);
}

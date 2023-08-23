/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 19:10:28 by mgranero          #+#    #+#             */
/*   Updated: 2023/06/23 15:40:39 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Takes as a parameter a node and frees the memory of the node’s content using
the function ’del’ given as a parameter and free the node. The memory of 
’next’ must not be freed.

Parameters:
lst: The node to free.
del: The address of the function used to delete the content.

Returns:
None

*/

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	del(lst->str);
	free(lst);
}

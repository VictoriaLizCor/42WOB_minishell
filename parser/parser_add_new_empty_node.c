/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_add_new_empty_node.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranero <mgranero@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 14:49:53 by mgranero          #+#    #+#             */
/*   Updated: 2023/07/09 15:16:45 by mgranero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 * @brief adds an empty list element the end of the list
 *
 * @param lex
 * @param p
 * @return int
 */
int	add_new_empty_node(t_parser *p)
{
	t_pipex	*list_new;

	list_new = (t_pipex *)ft_calloc(1, sizeof(t_pipex));
	if (list_new == NULL)
	{
		ft_putstr_fd("Error: calloc in add_list_node\n", STDERR_FILENO);
		return (-1);
	}
	if (p->list_exec == NULL)
		list_new->next = NULL;
	else
	{
		list_new->next = p->list_exec;
		p->list_exec->previous = list_new;
	}
	p->count_cmd = p->count_cmd + 1;
	p->list_exec = list_new;
	p->list_exec->idx = p->count_cmd - 1;
	return (0);
}

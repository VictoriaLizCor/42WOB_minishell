/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_builtin_integration.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 17:11:32 by mgranero          #+#    #+#             */
/*   Updated: 2023/08/11 14:09:06 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pipex_builtin_integration(t_pipex *node)
{
	if (env_var_extension(node) == 1)
		ft_error(node->cmd.exe[0], "variable expansion error", 1);
	if (search_builtin(node) == 1)
	{
		*(node->head->ptr_env_heap) = *(node->ptr_env_heap);
		node->head->last_stat = node->last_stat;
		return (node->last_stat);
	}
	return (-1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranero <mgranero@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 14:55:22 by mgranero          #+#    #+#             */
/*   Updated: 2023/08/04 17:18:15 by mgranero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	free_cmd_exe(t_pipex *ptr);

/**
 * @brief function to free pipex list and all its intern allocated elements
 *
 * @param l_pipex
 */
void	free_list_pipex(t_pipex *l_pipex)
{
	t_pipex	*ptr;
	t_pipex	*ptr_next;

	if (l_pipex == NULL)
		return ;
	ptr = l_pipex;
	while (ptr != NULL)
	{
		ptr_next = ptr->next ;
		if (ptr->cmd.exe != NULL)
			free_cmd_exe(ptr);
		if (ptr->cmd.token_kind != NULL)
			free(ptr->cmd.token_kind);
		if (ptr->file[0].name != NULL)
			free(ptr->file[0].name);
		if (ptr->file[1].name != NULL)
			free(ptr->file[1].name);
		if (ptr->ptr_env_heap != NULL)
			free(ptr->ptr_env_heap);
		free(ptr);
		ptr = ptr_next;
	}
}

/**
 * @brief support function from free_list_pipex by freeing cmd_exe
 *  allocated memory
 *
 * @param ptr
 */
static void	free_cmd_exe(t_pipex *ptr)
{
	int		i;

	i = 0;
	while (ptr->cmd.exe[i] != NULL )
	{
		free(ptr->cmd.exe[i]);
		i++;
	}
	free(ptr->cmd.exe);
}

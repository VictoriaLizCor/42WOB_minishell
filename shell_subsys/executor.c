/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranero <mgranero@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 16:15:45 by mgranero          #+#    #+#             */
/*   Updated: 2023/08/15 20:35:40 by mgranero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_subsys.h"

// static int		get_return_status(t_pipex *l_pipex);
// static int		search_builtin(t_pipex	*ptr);
static int		search_builtin_part2(t_pipex *ptr);
// void		update_nodes_env(t_pipex *l_pipex, t_env *new_env);

/**
 * @brief function for testing, loops through list and
 *  execute built ins
 *
 * @param l_pipex
 * @return t_pipex*
//  */
void	executor(t_pipex *l_pipex)

{
	t_pipex	*ptr;

	ptr = l_pipex;
	while (ptr != NULL)
	{
		if (ptr->cmd.exe == NULL)
			ptr = ptr->next;
		else
		{
			ptr->last_stat = l_pipex->last_stat ;
			if (env_var_extension(ptr) == 1 || search_builtin(ptr) == -1)
				return ;
			l_pipex->last_stat = ptr->last_stat;
			update_nodes_env(l_pipex, *(ptr->ptr_env_heap));
			if (get_return_status(ptr) == 1)
				break ;
			ptr = ptr->next;
		}
	}
}

void	update_nodes_env(t_pipex *l_pipex, t_env *new_env)
{
	t_pipex	*node;

	node = l_pipex;
	while (node != NULL)
	{
		if (*(node->ptr_env_heap) != new_env)
			*(node->ptr_env_heap) = new_env;
		node = node-> next;
	}
}

/**
 * @brief search the sent command in the built ins.
 *
 * @param ptr current list
 * @return int return 1 if there was match to one of the built-ins
 *  or 0 otherwise
 */
int	search_builtin(t_pipex *ptr)
{
	if (ptr == NULL || ptr->cmd.exe == NULL)
		return (1);
	if (str_compare(ptr->cmd.exe[0], "echo") == 0)
		ptr->last_stat = ft_echo(&(ptr->cmd));
	else if (str_compare(ptr->cmd.exe[0], "pwd") == 0)
		ptr->last_stat = ft_pwd(STDOUT_FILENO);
	else if (str_compare(ptr->cmd.exe[0], "env") == 0)
		ptr->last_stat = ft_env(*(ptr->ptr_env_heap), 1);
	else if (str_compare(ptr->cmd.exe[0], "export") == 0)
		ptr->last_stat = ft_export(ptr);
	else if (str_compare(ptr->cmd.exe[0], "exit") == 0)
		ptr->last_stat = 0;
	else
		return (search_builtin_part2(ptr));
	return (1);
}

static int	search_builtin_part2(t_pipex *ptr)
{
	if (str_compare(ptr->cmd.exe[0], "cd") == 0)
		ptr->last_stat = ft_cd(ptr->cmd.exe[1], ptr->ptr_env_heap);
	else if (str_compare(ptr->cmd.exe[0], "unset") == 0)
		ptr->last_stat = ft_unset(ptr);
	else
		return (-1);
	return (1);
}

int	get_return_status(t_pipex *l_pipex)
{
	if (l_pipex->last_stat == 1)
	{
		if (DEBUG_SUB == 1)
			printf("%sStatus return: 1 - %s%s\n",
				CBLU, l_pipex->cmd.exe[0], CWHT);
		return (1);
	}
	if (DEBUG_SUB == 1)
		printf("%sStatus return: 0 - %s%s\n", CBLU,
			l_pipex->cmd.exe[0], CWHT);
	return (0);
}

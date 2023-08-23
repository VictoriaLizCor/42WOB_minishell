/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranero <mgranero@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 09:59:02 by lilizarr          #+#    #+#             */
/*   Updated: 2023/08/17 16:16:27 by mgranero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// fprintf(stderr, "%s -> returning with status %d\n******-----***\n",
// CGRN, ptr->last_stat);
int	one_command_pipex_builtin_integration(t_pipex *node)
{
	t_pipex	*ptr;

	if (node->head->idx == 1 && node->idx == 1)
	{
		ptr = node->next;
		if (pipex_builtin_integration(ptr) != -1)
		{
			return (-1);
		}
	}
	return (0);
}

void	head_execution(t_pipex *node)
{
	if (node == node->head && node->cmd.status == 0)
	{
		ft_memset(&g_sig, -1, sizeof(g_sig));
		print_list(node, 0);
		depurate_list(node->next);
		print_list(node, 0);
		node->cmd.status = -1;
		if (pipe(node->pipex) < 0)
			ft_error("Failed to create pipe", NULL, 1);
		redirect(NULL, NULL, STDIN_FILENO, node->pipex[0]);
		redirect(NULL, NULL, STDOUT_FILENO, node->pipex[1]);
		handling_files(openfile, node->next);
	}
}

void	create_child(t_pipex *node)
{
	t_pipex	*list;

	list = node;
	head_execution(node);
	if (list->previous)
	{
		if (pipe(list->pipex) < 0)
			ft_error("Failed to create pipe", NULL, 1);
	}
	list->child_pid = fork();
	if (list->child_pid == -1)
		ft_error("Fork failed", NULL, 1);
}

void	setup_signals(t_pipex *node)
{
	g_sig.child_pid = node->child_pid;
	if (node == node->head)
		g_sig.idx = 0;
	else
		g_sig.idx = node->idx + 1;
	if (node->next->file[0].name && node->next->file[0].fd == 0)
		ft_setup_sighandler_parent();
}

void	run_fork(t_pipex **node)
{
	if (one_command_pipex_builtin_integration(*node) == -1)
		return ;
	if ((*node)->next)
		create_child(*node);
	else
		execute_last_node(*node);
	if ((*node)->child_pid == 0)
	{
		ft_setup_sighandler_non_interact();
		run_fork(&(*node)->next);
	}
	else
	{
		setup_signals(*node);
		wait_for_child(*node);
		ft_setup_sighandler_non_interact();
		if ((*node) != (*node)->head && (*node)->next->cmd.status > -1)
			execute_node_with_child(*node);
	}
}

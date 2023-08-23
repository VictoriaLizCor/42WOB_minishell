/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranero <mgranero@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 10:28:05 by lilizarr          #+#    #+#             */
/*   Updated: 2023/08/14 20:24:31 by mgranero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// fprintf(stderr, "gpid : %d | child_pid: %d\n", getpid(),
// node->previous->child_pid);
// g_child_pid[0] = node->previous->child_pid;
void	execute_last_node(t_pipex *node)
{
	if (node->previous == NULL)
	{
		ft_putstr_fd("Warning! impossible Error happening\n", 2);
		close_fds(node->previous, node);
		exit (1);
	}
	pipex_status(node->previous);
	if (node->previous->pipex_status[0] != -1)
		redirect(node->previous, node->previous, 1, STDOUT_FILENO);
	if (node->f_inout != -1)
		redirect_file(node->previous, node);
	close_fds(node->previous, node);
	cmd(node);
	exit(0);
}

// fprintf(stderr, "\nstatus: %d \n", node->next->cmd.status);
void	wait_for_child(t_pipex *node)
{
	waitpid(-1, &node->next->cmd.status, WUNTRACED);
	if (node->next->cmd.status != 0)
		redirect(node->previous, node->head, 1, STDIN_FILENO);
	if (node == node->head)
	{
		status_close(node);
		handling_files(close_files, node);
		node->last_stat = node->next->cmd.status;
	}
}

// fprintf(stderr, "gpid : %d | child_pid: %d\n", getpid(), node->child_pid);
void	execute_node_with_child(t_pipex *node)
{
	redirect(node->previous, node, 0, STDIN_FILENO);
	if (node->idx != node->head->idx - 1 && node->f_inout == -1)
	{
		redirect(node->previous, node->previous, 1, STDOUT_FILENO);
		close_fds(node->previous, node);
	}
	else if (node->idx != node->head->idx - 1 && node->f_inout != -1)
	{
		redirect(node->previous, node->previous, 1, STDOUT_FILENO);
		redirect_file(node->previous, node);
		close_fds(node->previous, node);
	}
	else if (node->idx == node->head->idx - 1 && node->f_inout != -1)
	{
		redirect_file(node->previous, node);
		close_fds(node, node);
	}
	else
		close_fds(node, node);
	cmd(node);
	exit(0);
}

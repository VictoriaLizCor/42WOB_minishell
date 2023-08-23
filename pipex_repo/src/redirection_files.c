/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_files.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 17:09:10 by lilizarr          #+#    #+#             */
/*   Updated: 2023/08/14 16:26:05 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// fprintf(stderr, "DUP\t old: [%d] | new: [%d]\n", current->pipex[idx], to_fd);
// fprintf(stderr, "DUP\told: [%d] | new: [%d]\n", idx, to_fd);
void	redirect(t_pipex *parent, t_pipex *current, int idx, int to_fd)
{
	if (parent && parent->next->file[0].fd != 0)
		status_close(parent->head);
	if (current != NULL)
	{
		pipex_status(current);
		if (current->pipex_status[idx] != -1 && to_fd != -1)
		{
			if (dup2(current->pipex[idx], to_fd) != -1)
				ft_close(parent);
			else
				ft_error(strerror(errno), "Dup failed", 1);
		}
	}
	else
	{
		if (idx != -1 && to_fd != -1)
		{
			if (dup2(idx, to_fd) != -1)
				ft_close(parent);
			else
				ft_error(strerror(errno), "Dup failed", 1);
		}
	}
}

static void	cmd_here_doc(t_pipex *pipe_node, t_pipex *node_file)
{
	t_pipex	h_doc;

	if (pipe(h_doc.pipex) < 0)
		ft_error("Failed to create pipe", NULL, 1);
	if (ft_setup_sighandler_heredoc() == -1)
		fprintf(stderr, "error to setup ft_setup_sighandler_heredoc\n");
	h_doc.ptr_env_heap = node_file->ptr_env_heap;
	h_doc.head = node_file->head;
	h_doc.cmd.exe = (char **)ft_calloc(sizeof(char *), 3);
	h_doc.cmd.exe[0] = ft_strdup("<<");
	h_doc.cmd.exe[1] = ft_strdup(node_file->file[0].name);
	node_file->last_stat = ft_heredoc(&h_doc);
	ft_close_msg(h_doc.pipex[1]);
	node_file->head->last_stat = node_file->last_stat;
	redirect(NULL, &h_doc, 0, STDIN_FILENO);
	ft_close_msg(h_doc.pipex[0]);
	if (node_file->file[1].name)
		redirect(NULL, NULL, node_file->file[1].fd, STDOUT_FILENO);
	else if (pipe_node->pipex_status[0] != -1)
		redirect(NULL, NULL, pipe_node->pipex[1], STDOUT_FILENO);
	ft_free(h_doc.cmd.exe);
	if (node_file->last_stat > 0)
		exit(1);
}

void	redirect_file(t_pipex *pipe_node, t_pipex *node_file)
{
	if (node_file->file[0].name && node_file->file[0].fd == 0)
	{
		redirect(NULL, pipe_node->head, 0, STDIN_FILENO);
		redirect(NULL, pipe_node->head, 1, STDOUT_FILENO);
		status_close(pipe_node->head);
		cmd_here_doc(pipe_node, node_file);
		return ;
	}
	else if (node_file->file[0].name)
	{
		if (node_file->file[0].fd < 0)
			ft_error(node_file->file[0].name, node_file->cmd.error_str, 1);
		else
			redirect(NULL, NULL, node_file->file[0].fd, STDIN_FILENO);
	}
	if (node_file->file[1].name)
	{
		if (node_file->file[1].fd < 0)
			ft_error(node_file->file[1].name, strerror(errno), 1);
		else
			redirect(NULL, NULL, node_file->file[1].fd, STDOUT_FILENO);
	}
}

void	openfile(t_pipex *node)
{
	if (node->file[0].name && node->file[0].fd == -1)
	{
		node->file[0].fd = open(node->file[0].name, \
		node->file[0].oflag, 0644);
		if (node->file[0].fd < 0)
			node->cmd.error_str = strerror(errno);
	}
	if (node->file[1].name && node->file[1].fd == -1)
	{
		node->file[1].fd = open(node->file[1].name, \
		node->file[1].oflag, 0644);
		if (node->file[1].fd < 0)
			return ;
	}
}

void	handling_files(void (*fun)(t_pipex *), t_pipex *ptr)
{
	t_pipex	*last;

	last = last_node(ptr);
	while (last->previous)
	{
		if (last->f_inout > -1)
			fun(last);
		last = last->previous;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_files_helper.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 17:09:10 by lilizarr          #+#    #+#             */
/*   Updated: 2023/08/09 10:44:56 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	fill_t_file(t_pipex *list, int (*in_out)[3], t_file (*file)[2])
{
	t_pipex	*node;

	node = list;
	node->cmd.exe = ft_free(node->cmd.exe);
	if ((*file)[0].name)
	{
		node->file[0].oflag = (*file)[0].oflag;
		node->file[0].fd = (*file)[0].fd;
		if (node->file[0].name)
			free((node->file[0].name));
		node->file[0].name = ft_strdup((*file)[0].name);
		free((*file)[0].name);
	}
	if ((*file)[1].name)
	{
		node->file[1].oflag = (*file)[1].oflag;
		node->file[1].fd = (*file)[1].fd;
		if (node->file[1].name)
			free((node->file[1].name));
		node->file[1].name = ft_strdup((*file)[1].name);
		free((*file)[1].name);
	}
	node->f_inout = (*in_out)[2];
}

t_pipex	*ispipe_command(t_pipex *node)
{
	t_pipex	*p_cmd;

	p_cmd = node;
	while (p_cmd->next && !p_cmd->is_pipe)
	{
		p_cmd = p_cmd->next;
	}
	return (p_cmd);
}

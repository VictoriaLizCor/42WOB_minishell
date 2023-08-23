/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 14:31:14 by lilizarr          #+#    #+#             */
/*   Updated: 2023/08/17 13:19:53 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

static void	update_idx(t_pipex *node)
{
	int		i;

	i = 0;
	while (node)
	{
		node->idx = i;
		node = node->previous;
		i++;
	}
}

static void	restart_values(int (*in_out)[3], t_file (*file)[2])
{
	ft_bzero(*in_out, sizeof(int) * 2);
	(*in_out)[2] = -1;
	ft_bzero(*file, sizeof(t_file) * 2);
	(*file)[0].fd = -1;
	(*file)[1].fd = -1;
	(*file)[0].oflag = -1;
	(*file)[1].oflag = -1;
}

static void	find_files(t_pipex *node, int (*in_out)[3], t_file (*file)[2])
{
	if (node->f_inout == 1 && (*in_out)[1] == 0)
		(*in_out)[1] = 1;
	else if (node->f_inout == 0 && (*in_out)[0] == 0)
		(*in_out)[0] = 1;
	if ((*file)[node->f_inout].name)
		free((void *)file[node->f_inout]->name);
	(*file)[node->f_inout].name = ft_strdup(node->file[node->f_inout].name);
	(*file)[node->f_inout].oflag = node->file[node->f_inout].oflag;
	(*file)[node->f_inout].fd = node->file[node->f_inout].fd;
	if ((*in_out)[0] && (*in_out)[1])
		(*in_out)[2] = 2;
	else if ((*in_out)[0] && !(*in_out)[1])
		(*in_out)[2] = 0;
	else if (!(*in_out)[0] && (*in_out)[1])
		(*in_out)[2] = 1;
}

static void	info_node(t_pipex *p_cmd, t_pipex *end, t_pipex *nl, char **s_cmd)
{
	t_file	tmp_file[2];
	int		in_out[3];
	int		i;

	restart_values(&in_out, &tmp_file);
	while (p_cmd != end->previous)
	{
		if (p_cmd->f_inout == -1)
			fill_cmd(p_cmd, s_cmd);
		else if (p_cmd->f_inout > -1)
			find_files(p_cmd, &in_out, &tmp_file);
		p_cmd = p_cmd->previous;
	}
	fill_t_file(nl, &in_out, &tmp_file);
	if (*s_cmd)
	{
		nl->cmd.exe = ft_split(*s_cmd, '`');
		free(*s_cmd);
		i = 0;
		while (nl->cmd.exe[++i])
		{
			if (*nl->cmd.exe[i] == ' ')
				*nl->cmd.exe[i] = '\0';
		}
	}
}

void	depurate_list(t_pipex *node)
{
	t_pipex	*pipe;
	t_pipex	*list;
	char	*s_cmd;

	list = node;
	while (node)
	{
		s_cmd = NULL;
		pipe = ispipe_command(node);
		info_node(pipe, node, list, &s_cmd);
		list = list->next;
		node = pipe->next;
	}
	if (list)
	{
		pipe = list->previous;
		pipe->next = NULL;
		free_list_pipex(list);
	}
	update_idx(pipe);
}

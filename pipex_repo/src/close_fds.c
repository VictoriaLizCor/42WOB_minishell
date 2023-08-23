/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 13:01:23 by lilizarr          #+#    #+#             */
/*   Updated: 2023/08/14 14:50:02 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
**	@brief
**	close file descriptor and shows error message in case of failure
**	@param fd file descriptor to be close
*/
void	ft_close_msg(int fd)
{
	char	*str_fd;
	int		value_close;

	value_close = close(fd);
	if (value_close < 0)
	{
		str_fd = ft_itoa(fd);
		ft_error(strerror(errno), str_fd, 1);
		free(str_fd);
	}
}
// fprintf(stderr, "\t\t\t***closing_fd [%d]\n", fd);

/**
**	@brief
**	Check for node->file[0] && node->file[1] file descriptor status linked
**	to function open(), and in case of fstat returns 0 and , closes the FD. 
**	@param node t_pipex struct
*/
void	close_files(t_pipex *node)
{
	struct stat	buff;
	int			fd_stat;

	fd_stat = fstat(node->file[0].fd, &buff);
	if (fd_stat == 0 && node->file[0].fd > STDERR_FILENO)
		ft_close_msg(node->file[0].fd);
	fd_stat = fstat(node->file[1].fd, &buff);
	if (fd_stat == 0 && node->file[1].fd > STDERR_FILENO)
		ft_close_msg(node->file[1].fd);
}

/**
**	@brief
**	
**	
**	@param node current t_pipex struct with the process pipe variable 
**	@param file_node t_pipex struct with the file variable 
*/
void	close_fds(t_pipex *node, t_pipex *file_node)
{
	pipex_status(node);
	if (node->pipex_status[0] > -1)
		ft_close_msg(node->pipex[0]);
	handling_files(close_files, file_node);
	if (node->pipex_status[1] > -1)
		ft_close_msg(node->pipex[1]);
}

void	status_close(t_pipex *node)
{
	pipex_status(node);
	if (node->pipex_status[0] == 0)
		ft_close_msg(node->pipex[0]);
	if (node->pipex_status[1] == 0)
		ft_close_msg(node->pipex[1]);
	pipex_status(node);
}

void	ft_close(t_pipex *parent)
{
	t_pipex		*last;

	if (!parent)
		return ;
	last = last_node(parent)->previous;
	if (last->previous == NULL || parent->previous == NULL)
		return ;
	while (last)
	{
		if (last == parent)
			last = last->previous;
		if (!last->previous)
			break ;
		status_close(last);
		last = last->previous;
	}
}

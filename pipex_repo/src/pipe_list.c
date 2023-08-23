/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:17:35 by lilizarr          #+#    #+#             */
/*   Updated: 2023/08/15 17:14:37 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	print_table(int num, t_pipex **head)
{
	if ((num % 2 == 1))
		fprintf(stderr, "P[%d][0]: [%d]\n", (*head)->idx, (*head)->pipex[0]);
	else if (num % 2 == 0)
	{
		fprintf(stderr, "P[%d][1]: [%d] \t %p ", (*head)->idx, \
		(*head)->pipex[1], head);
		if ((*head)->f_inout > -1 && (*head) != (*head)->head)
		{
			fprintf(stderr, " %s ", (*head)->file[0].name);
			fprintf(stderr, "\t[%d]", (*head)->file[0].fd);
			fprintf(stderr, " %s ", (*head)->file[1].name);
			fprintf(stderr, "\t[%d]", (*head)->file[1].fd);
		}
		fprintf(stderr, "\n");
		(*head) = (*head)->next;
	}
}

void	check_fd(int num, t_pipex *node)
{
	t_pipex		*head;
	int			fd_table_limit;
	struct stat	info;

	if (node)
	{
		head = node->head;
		fd_table_limit = head->idx * 4 + 2;
	}
	else
	{
		head = NULL;
		fd_table_limit = 5 * 2;
	}
	fprintf(stderr, "*** FD TABLE *** STATUS \t\t*** NODE\n");
	while (num <= fd_table_limit)
	{
		fprintf(stderr, "*** FD: %d \t %d \t\t", num, fstat(num, &info));
		if (num > 0 && head)
			print_table(num, &head);
		else
			fprintf(stderr, "\n");
		num++;
	}
	fprintf(stderr, "******************* \n");
}

static void	print_node_info_ext(t_pipex *node)
{
	fprintf(stderr, "FILE[0]: %s %p \t FD[%d] \t OFLAG{%d}\n", \
	node->file[0].name, node->file[0].name, node->file[0].fd, \
	node->file[0].oflag);
	fprintf(stderr, "FILE[1]	: %s %p\t FD[%d] \t OFLAG{%d}\n", \
	node->file[1].name, node->file[1].name, \
	node->file[1].fd, node->file[1].oflag);
	fprintf(stderr, "IN_OUT: [%d]\n", node->f_inout);
	if (node->cmd.token_kind)
		fprintf(stderr, "TOKEN: %s \n", get_token_char(node->cmd.token_kind));
	fprintf(stderr, "CMD: %p\n", node->cmd.exe);
	print_variable(node->cmd.exe, NULL);
	if (node->cmd.path)
		fprintf(stderr, "CMD->path: %s\n", node->cmd.path);
	else
		fprintf(stderr, "CMD->path: NULL\n");
}

void	print_node_info(t_pipex *node, int opt)
{
	fprintf(stderr, "{%d} NODE: %p\n", node->idx, node);
	fprintf(stderr, "child_pid: %d\n", node->child_pid);
	if (node->previous)
		fprintf(stderr, "*current_pid: %d\n", node->previous->child_pid);
	fprintf(stderr, "last_stat: %d\n", node->last_stat);
	fprintf(stderr, "node->cmd.status: %d\n", node->cmd.status);
	if (node->next)
		fprintf(stderr, "*next->cmd.status: %d\n", node->next->cmd.status);
	if (opt == 1)
		return ;
	fprintf(stderr, "current  |\t p_read[0]:\t [%d] | p_write[1]:\t [%d]\n", \
	node->pipex[0], node->pipex[1]);
	fprintf(stderr, "current  |\t status[0]:\t [%d] | status[1]:\t [%d]\n", \
	node->pipex_status[0], node->pipex_status[1]);
	if (node->previous)
	{
		fprintf(stderr, "previous |\t p_read[0]:\t [%d] | p_write[1]:\t [%d]\n", \
		node->previous->pipex[0], node->previous->pipex[1]);
		fprintf(stderr, "previous |\t status[0]:\t [%d] | status[1]:\t [%d]\n", \
		node->previous->pipex_status[0], node->previous->pipex_status[1]);
	}
	print_node_info_ext(node);
}

void	print_list(t_pipex *list, int opt)
{
	t_pipex	*p;

	p = list;
	if (DEBUG_PIPE == 0)
		return ;
	ft_printf("\n\n%s------------- List HEAD Address : %p\t \t\n", CRED, p);
	ft_printf("Idx ||\t status ||\t\t\tprevious\t||\tcurrent\t||\tnext\n");
	while (p)
	{
		ft_printf(" %d ||\t %d ||\t\t\t\t%p   ||\t%p   ||\t%p \n", \
		p->idx, p->cmd.status, p->previous, p, p->next);
		print_node_info(p, opt);
		p = p->next;
	}
	ft_printf("%s\n", CWHT);
}

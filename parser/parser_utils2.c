/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranero <mgranero@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 14:01:13 by mgranero          #+#    #+#             */
/*   Updated: 2023/08/03 17:15:39 by mgranero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	initialize_file_struct(t_parser *p)
{
	p->list_exec->f_inout = -1;
	p->list_exec->file[0].oflag = -1;
	p->list_exec->file[1].oflag = -1;
	p->list_exec->file[0].fd = -1;
	p->list_exec->file[1].fd = -1;
}

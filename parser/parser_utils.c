/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranero <mgranero@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 21:45:38 by mgranero          #+#    #+#             */
/*   Updated: 2023/07/14 13:57:47 by mgranero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	print_file(t_pipex *ptr);
static void	print_cmd(t_pipex *ptr);
static int	print_header_list(t_pipex *ptr);
static void	print_general_data(t_pipex *ptr);

/**
 * @brief debugging support function which prints list
 *
 * @param l_pipex
 */
void	print_pipex_list(t_pipex *l_pipex)
{
	t_pipex	*ptr;
	int		i;

	i = 0;
	printf("\n * * * * * Parsing Output t_pipex list * * * * *\n\n");
	if (l_pipex == NULL)
		printf("print_pipex_list: l_pipex = NULL\n");
	ptr = l_pipex;
	while (ptr != NULL)
	{
		if (i == 0)
			i += print_header_list(ptr);
		else
		{
			print_general_data(ptr);
			print_cmd(ptr);
			print_file(ptr);
			printf("%s* \n", CWHT);
		}
		printf("\n");
		ptr = ptr->next;
	}
	printf("%s\n * * * * * * * * * * * * * *\n\n", CWHT);
}

static void	print_general_data(t_pipex *ptr)
{
	printf("%sidx = %s%d, %scurrent:%s%p, %snext = %s%p, "
		"%sprevious %s%p\n%spaths "
		"= %s%s\n", CGRN, CBLU, ptr->idx, CGRN, CBLU, ptr, CGRN, CBLU,
		ptr->next, CGRN, CBLU, ptr->previous, CGRN, CBLU, ptr->paths);
}

/**
 * @brief prints header list data
 *
 * @param ptr
 */
static int	print_header_list(t_pipex *ptr)
{
	printf("%sidx = %s%d, %scurrent:%s%p, %snext = %s%p, "
		"%sprevious %s%p%s%s\n", CGRN, CBLU, ptr->idx,
		CGRN, CBLU, ptr, CGRN, CBLU, ptr->next, CGRN, CBLU,
		ptr->previous, CGRN, CBLU);
	printf("Header - Null List\n");
	return (1);
}

/**
 * @brief function used to print cmd struct data
 *
 * @param ptr
 */
static void	print_cmd(t_pipex *ptr)
{
	int		i;
	char	*cmd;

	i = 0;
	cmd = ptr->cmd.exe[i];
	printf("%scmd struct:\n%spath:%s%s\n%sexe:%s\n", CGRN,
		CGRN, CBLU, ptr->cmd.path, CGRN, CBLU);
	while (cmd != NULL)
	{
		if (i == 0)
			printf("%s   %d:%s%s\tis_pipe=%d\n",
				CGRN, i, CBLU, cmd, ptr->is_pipe);
		else
			printf("%s   %d:%s%s\n", CGRN, i, CBLU, cmd);
		i++;
		cmd = ptr->cmd.exe[i];
	}
	printf("%s   %d:%s%s\n", CGRN, i, CBLU, cmd);
}

/**
 * @brief function used to print File struct data
 *
 * @param ptr
 */
static void	print_file(t_pipex *ptr)
{
	if (ptr->f_inout > -1)
	{
		printf("%so_flags: %s%d\n", CGRN, CBLU, ptr->file[ptr->f_inout].oflag);
		printf("%sfilepath/delimiter: %s%s\n", CGRN,
			CBLU, ptr->file[ptr->f_inout].name);
	}
	else
	{
		printf("%so_flags: %s%d\n", CGRN, CBLU, -1);
		printf("%sfilepath/delimiter: %s%s\n", CGRN,
			CBLU, "(null)");
	}
	printf("%sf_in_out: %s%d\n", CGRN, CBLU, ptr->f_inout);
}

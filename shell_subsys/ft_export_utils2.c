/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 20:26:18 by mgranero          #+#    #+#             */
/*   Updated: 2023/08/16 16:30:49 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_subsys.h"

char	*print_err_null(char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	return (NULL);
}

int	print_err_ret1(char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	return (1);
}

char	*rescan_assign(char *value, t_pipex *l_pipex, t_Lexer lexer_tmp)
{
	t_pipex	*list_tmp;
	t_pipex	*ptr;

	list_tmp = parser(&lexer_tmp, *(l_pipex->ptr_env_heap), 1);
	free_lexer(&lexer_tmp);
	free(value);
	if (list_tmp == NULL)
		return (NULL);
	ptr = list_tmp->next;
	if (list_tmp != NULL)
	{
		ptr->head->last_stat = l_pipex->last_stat;
		ptr->last_stat = l_pipex->last_stat;
		if (env_var_extension(ptr) == 1)
			return (NULL);
	}
	value = join_new_value(ptr);
	free_list_pipex(list_tmp);
	return (value);
}

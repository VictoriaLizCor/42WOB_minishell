/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 17:09:10 by lilizarr          #+#    #+#             */
/*   Updated: 2023/08/15 13:50:35 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_pipex	*last_node(t_pipex *data)
{
	t_pipex	*last;

	last = data;
	while (last->next)
		last = last->next;
	return (last);
}

void	pipex_status(t_pipex *d)
{
	if (d)
	{
		d->pipex_status[0] = fstat(d->pipex[0], &d->info_pipex[0]);
		d->pipex_status[1] = fstat(d->pipex[1], &d->info_pipex[1]);
	}
}

char	*get_token_char(t_Token_kind *tok)
{
	if (*tok == TOKEN_LESS)
		return ("<\0");
	else if (*tok == TOKEN_DLESS)
		return ("<<\0");
	else if (*tok == TOKEN_GREAT)
		return (">\0");
	else if (*tok == TOKEN_DGREAT)
		return (">\0");
	else
		return (NULL);
}

void	printf_stderr(char *str1, char *str2, int exit_error)
{
	char	*num;
	int		c_str;

	ft_putstr_fd(str1, 2);
	if (str2)
		ft_putstr_fd(" : ", 2);
	ft_putstr_fd(str2, 2);
	ft_putstr_fd(" | ", 2);
	c_str = *str2;
	num = ft_itoa(c_str);
	ft_putendl_fd(num, 2);
	free(num);
	if (exit_error >= 0)
		exit(exit_error);
}

void	print_variable(char **variable, char *msg)
{
	int		i;
	char	*num;

	if (variable != NULL)
	{
		i = 0;
		while (variable[i])
		{
			num = ft_itoa(i);
			fprintf(stderr, "%p ", variable[i]);
			ft_putstr_fd(num, 2);
			ft_putstr_fd(" |", 2);
			printf_stderr(msg, variable[i], -1);
			free(num);
			i++;
		}
	}
	else
		ft_putendl_fd("\t\t*NULL", 2);
	ft_putendl_fd("-------------------------------------", 2);
}

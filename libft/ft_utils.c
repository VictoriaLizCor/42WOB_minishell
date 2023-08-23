/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:29:47 by lilizarr          #+#    #+#             */
/*   Updated: 2023/08/16 11:53:00 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_free(char **str)
{
	int		i;

	i = 0;
	while (str[i] != 0)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

void	ft_error(char *str1, char *str2, int exit_error)
{
	if (exit_error > 0)
		ft_putstr_fd("\033[1;31mError: ", 2);
	if (str1)
		ft_putstr_fd(str1, 2);
	if (str2)
		ft_putstr_fd(" : ", 2);
	ft_putstr_fd(str2, 2);
	ft_putendl_fd("\033[0m", 2);
	if (exit_error >= 0)
		exit(exit_error);
}

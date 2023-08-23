/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranero <mgranero@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 21:23:10 by mgranero          #+#    #+#             */
/*   Updated: 2023/07/13 17:43:27 by mgranero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_subsys.h"

/**
 * @brief function prints every entry in local environment
 *  env_heap array in format key:value
 *
 * @param env_heap local environment allocated by setup_environment
 */
int	ft_env(t_env *env_heap, int fd)
{
	int	i;

	i = 0;
	if (env_heap == NULL)
		ft_putstr_fd("Error: ft_env, env_heap passed is NULL", STDERR_FILENO);
	while (env_heap[i].key != NULL)
	{
		ft_putstr_fd(env_heap[i].key, fd);
		ft_putchar_fd('=', fd);
		if (env_heap[i].value != NULL)
			ft_putstr_fd(env_heap[i].value, fd);
		ft_putchar_fd('\n', fd);
		i++;
	}
	return (0);
}

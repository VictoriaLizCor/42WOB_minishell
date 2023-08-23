/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranero <mgranero@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 20:49:22 by mgranero          #+#    #+#             */
/*   Updated: 2023/07/23 09:24:55 by mgranero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_subsys.h"

static t_env	*remove_key(t_env *env_heap, char *key);
static void		free_match_key_value(t_env *env_heap, int j);
static void		loop_keys_search_match(int size_env_heap, char *key,
					t_env *new_env, t_env *env_heap);

int	ft_unset(t_pipex *l_pipex)
{
	int		i;

	if (*(l_pipex->ptr_env_heap) == NULL)
	{
		ft_putstr_fd("Error: ft_unset, env_heap passed is NULL", STDERR_FILENO);
		return (1);
	}
	i = 1;
	while (l_pipex->cmd.exe[i] != NULL)
	{
		if (i == 1 && l_pipex->cmd.exe[i] == NULL)
			return (1);
		if (ft_unset_basic(l_pipex->cmd.exe[i], l_pipex->ptr_env_heap) == 1)
			return (1);
		i++;
	}
	return (0);
}

int	ft_unset_basic(char *key, t_env **ptr_env_heap)
{
	t_env	*new_env;

	if (get_env_key_value(key, *(ptr_env_heap)) != NULL)
	{
		new_env = remove_key(*(ptr_env_heap), key);
		if (new_env == NULL)
			return (1);
		*(ptr_env_heap) = new_env;
	}
	return (0);
}

static t_env	*remove_key(t_env *env_heap, char *key)
{
	t_env	*new_env;
	int		size_env_heap;

	size_env_heap = getenvheap_size(env_heap);
	new_env = (t_env *)ft_calloc(size_env_heap, sizeof(t_env));
	if (new_env == NULL)
		return (print_err_ret_0("Error: ft_calloc in ft_unset\n"));
	loop_keys_search_match(size_env_heap, key, new_env, env_heap);
	free(env_heap);
	return (new_env);
}

/**
 * @brief copies all the keys and values from env_heap except the
 *  key we want to unset. This key and its matching value are than
 *  freed.
 *
 * @param size_env_heap number of keys in env_heap
 * @param key key to be unsetted
 * @param new_env pointer to new environment without removed key
 * @param env_heap pointer to old environment with key to be removed
 */
static void	loop_keys_search_match(int size_env_heap, char *key,
				t_env *new_env, t_env *env_heap)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < size_env_heap)
	{
		if (str_compare(env_heap[j].key, key) == 0)
		{
			free_match_key_value(env_heap, j);
			j++;
		}
		if (env_heap[j].key != NULL)
		{
			new_env[i].key = env_heap[j].key;
			new_env[i].value = env_heap[j].value;
		}
		else
			break ;
		i++;
		j++;
	}
}

static void	free_match_key_value(t_env *env_heap, int j)
{
	if (env_heap[j].value != NULL)
	{
		free(env_heap[j].value);
		env_heap[j].value = NULL;
	}
	free(env_heap[j].key);
	env_heap[j].key = NULL;
}

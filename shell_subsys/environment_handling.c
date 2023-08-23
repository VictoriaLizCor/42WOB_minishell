/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_handling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranero <mgranero@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 11:47:58 by mgranero          #+#    #+#             */
/*   Updated: 2023/08/16 17:47:32 by mgranero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_subsys.h"

static int		get_env_size(char *env[]);

/**
 * @brief Setup the variable env_heap
 * 	function will split each entry from env in a key and value (separator =)
 *  and save it in one t_env struct. it returns a array of env_p
 *
 * @param env environment variable passed through main
 * @return t_env* a array of t_env that allocates memory for each entry in env
 * 	and splits it into a key and a value
 *
 */
t_env	*setup_environment(char *env[])
{
	t_env	*env_heap;
	int		i;
	char	*value;
	int		idx_eql;

	if (env == NULL)
		return (print_err_ret_0("Error: passed env to main is NULL\n"));
	env_heap = (t_env *)ft_calloc(get_env_size(env) + 1, sizeof(t_env));
	if (env_heap == NULL)
		return (print_err_ret_0("Error: ft_calloc in setup_environment\n"));
	ft_memset(&g_sig, -1, sizeof(g_sig));
	g_sig.idx = 0;
	i = 0;
	while (env[i] != NULL)
	{
		idx_eql = ft_get_index_of_char(env[i], '=');
		env_heap[i].key = ft_substr(env[i], 0, idx_eql);
		value = ft_strdup(env[i] + idx_eql + 1);
		if (value == NULL)
			env_heap[i].value = NULL;
		else
			env_heap[i].value = value;
		i++;
	}
	return (env_heap);
}

/**
 * @brief function free's memory allocated in local environment
 *
 * @param env_heap  local environment allocated by setup_environment
 */
void	free_env_heap(t_env *env_heap)
{
	int	i;

	if (env_heap == NULL)
		return ;
	i = 0;
	while (env_heap[i].key != NULL)
	{
		free(env_heap[i].key);
		if (env_heap[i].value != NULL)
			free(env_heap[i].value);
		i++;
	}
	free(env_heap);
}

/**
 * @brief fetch environment value of a environment key
 *
 * @param key key from env_heap which value should be return
 *
 * @return char* value to be returned (must be free) or NULL
 *  if key not found
 */
char	*get_env_key_value(char *key_searched, t_env *env_heap)
{
	int		i;
	size_t	lkey_searched;

	lkey_searched = ft_strlen(key_searched);
	i = 0;
	while (env_heap[i].key != NULL)
	{
		if (lkey_searched == ft_strlen(env_heap[i].key)
			&& ft_strncmp(key_searched, env_heap[i].key, lkey_searched) == 0)
		{
			return (env_heap[i].value);
		}
		i++;
	}
	return (NULL);
}

/**
 * @brief helper function that returns the amount of
 *  entries in the environment char ** passed through
 * 	main
 *
 * @param env environment variable passed through main
 * @return int number of entries (keys)
 */
static int	get_env_size(char *env[])
{
	int	i;

	i = 0;
	while (env[i] != NULL)
		i++;
	return (i);
}

/**
 * @brief helper function counts the amount of keys in env_heap
 *
 * @param env_heap local environment allocated by setup_environment
 * @return int amount of keys in env_heap
 */
int	getenvheap_size(t_env *env_heap)
{
	int	i;

	i = 0;
	while (env_heap[i].key != NULL)
		i++;
	return (i);
}

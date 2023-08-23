/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranero <mgranero@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 14:11:05 by mgranero          #+#    #+#             */
/*   Updated: 2023/08/06 20:22:07 by mgranero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_subsys.h"

static t_env	*mod_key_val(t_env *env_heap, char *key, char *value);
static t_env	*add_new_key(t_env *env_heap, char *key, char *value);

/**
 * @brief support function for ft_export
 *
 * @param l_pipex pointer to pipex list
 * @param i current cmd.exe element being analyzed
 * @return int -1 in case of error or 1 otherwise
 */
t_env	*ft_export_basic(char *key, char *value, t_env *env_heap)
{
	if (get_env_key_value(key, env_heap) != NULL)
		return (mod_key_val(env_heap, key, value));
	return (add_new_key(env_heap, key, value));
}

/**
 * @brief function will add a new key to the local environment env_heap
 *
 * @param env_heap local environment allocated by setup_environment
 * @param key key to be added
 * @param value value of the key to be added
 * @return t_env new local environment with included key or NULL in
 *  case of error
 */
static t_env	*add_new_key(t_env *env_heap, char *key, char *value)
{
	t_env	*new_env;
	int		i;

	new_env = (t_env *)ft_calloc(getenvheap_size(env_heap) + 2, sizeof(t_env));
	if (new_env == NULL)
	{
		ft_putstr_fd("Error: ft_calloc in add_new_key\n", STDERR_FILENO);
		return (NULL);
	}
	i = 0;
	while (env_heap[i].key != NULL)
	{
		new_env[i].key = env_heap[i].key;
		new_env[i].value = env_heap[i].value;
		i++;
	}
	new_env[i].key = ft_strdup(key);
	new_env[i].value = ft_strdup(value);
	free(env_heap);
	return (new_env);
}

/**
 * @brief modifies the value of an existing key in env_heap
 *
 * @param env_heap local environment allocated by setup_environment
 * @param key key which value must be modified
 * @param value new value of key
 * @return int returns NULL in case of error, otherwise env_heap
 */
static t_env	*mod_key_val(t_env *env_heap, char *key, char *value)
{
	int		i;
	size_t	lkey_searched;

	lkey_searched = ft_strlen(key);
	i = 0;
	while (env_heap[i].key != NULL)
	{
		if (lkey_searched == ft_strlen(env_heap[i].key)
			&& ft_strncmp(key, env_heap[i].key, lkey_searched) == 0)
		{
			if (env_heap[i].value != NULL)
				free(env_heap[i].value);
			env_heap[i].value = ft_strdup(value);
			if (env_heap[i].value == NULL)
			{
				ft_putstr_fd("Error: ft_strdup"
					" in modify_key_value\n", STDERR_FILENO);
				return (NULL);
			}
			break ;
		}
		i++;
	}
	return (env_heap);
}

int	export_no_args_print(t_env	*new_env)
{
	int		size_env;
	int		i;

	i = 0;
	size_env = getenvheap_size(new_env);
	while (i < size_env)
	{
		printf("declare -x %s=\"%s\"\n", new_env[i].key, new_env[i].value);
		i++;
	}
	return (0);
}

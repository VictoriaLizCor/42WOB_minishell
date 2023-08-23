/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranero <mgranero@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 21:38:20 by mgranero          #+#    #+#             */
/*   Updated: 2023/08/15 21:01:23 by mgranero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_subsys.h"

static t_env	*add_key_value(t_pipex *l_pipex, int i, t_env *env_heap);
static int		export_put_error_ident(char *identifier);
// static char		*join_new_value(t_pipex *ptr);
static char		*get_new_value(char *value, t_pipex *l_pipex);

/**
 * @brief function will check if the key already exists in local environment
 *  env_heap and if yes, value will be modified.
 *  if key does not exist, the env_heap will be resized and the new key
 *  and its value will be added to env_heap.
 * 	function does not free passed key or value pointers.
 * @param env_heap local environment allocated by setup_environment
 * @param key key to be added.
 * @param value value of the key to be added
 * @return t_env local environment with added/modified key and values
 */
int	ft_export(t_pipex *l_pipex)
{
	int		i;
	t_env	*new_env;

	if (*(l_pipex->ptr_env_heap) == NULL)
		return (print_err_ret1("Error: ft_env, env_heap passed is NULL"));
	new_env = *(l_pipex->ptr_env_heap);
	if (l_pipex->cmd.exe[1] == NULL)
		return (export_no_args_print(new_env));
	i = 1;
	while (l_pipex->cmd.exe[i] != NULL)
	{
		if (l_pipex->cmd.token_kind[i] == TOKEN_ASSIGNMENT_WORD)
		{
			new_env = add_key_value(l_pipex, i, new_env);
			if (new_env == NULL)
				return (1);
			*(l_pipex->ptr_env_heap) = new_env;
		}
		else
			export_put_error_ident(l_pipex->cmd.exe[i]);
		i++;
	}
	return (0);
}

static t_env	*add_key_value(t_pipex *l_pipex, int i, t_env *env_heap)
{
	char	*key;
	char	*value;
	t_env	*new_env;
	int		idx;

	idx = ft_get_index_of_char(l_pipex->cmd.exe[i], '=');
	key = ft_strdup_len(l_pipex->cmd.exe[i], idx);
	value = ft_strdup(l_pipex->cmd.exe[i] + idx + 1);
	value = get_new_value(value, l_pipex);
	new_env = ft_export_basic(key, value, env_heap);
	if (new_env == NULL)
		return (NULL);
	free(key);
	free(value);
	return (new_env);
}

static int	export_put_error_ident(char *identifier)
{
	ft_putstr_fd("export: ", STDERR_FILENO);
	ft_putstr_fd(identifier, STDERR_FILENO);
	ft_putstr_fd(" not a valid identifier\n", STDERR_FILENO);
	return (1);
}

static char	*get_new_value(char *value, t_pipex *l_pipex)
{
	t_Lexer	lexer_tmp;

	if (value != NULL && value[0] != '\0')
	{
		lexer_tmp = lexer(value);
		if (lexer_tmp.error == 0)
			return (rescan_assign(value, l_pipex, lexer_tmp));
		else
			return (print_err_null("Error: tmp lexer for export\n"));
	}
	return (value);
}

char	*join_new_value(t_pipex *ptr)
{
	int		i;
	char	*new_value;
	char	*old_value;

	i = 0;
	while (ptr->cmd.exe[i] != NULL)
	{
		old_value = new_value;
		if (i == 0)
			new_value = ft_strdup(ptr->cmd.exe[i]);
		else
		{
			new_value = ft_strjoin(old_value, ptr->cmd.exe[i]);
			free(old_value);
		}
		i++;
	}
	return (new_value);
}

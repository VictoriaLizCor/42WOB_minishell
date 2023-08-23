/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_extension.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 10:17:25 by mgranero          #+#    #+#             */
/*   Updated: 2023/08/15 14:32:52 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_subsys.h"

// static int	scan_env_extens(char *str);
// static int	modify_cmd_exe(t_pipex *l_pipex, int i,
// 				int idx, char *var_env);
// static int	env_var_extension_helper(t_pipex *l_pipex, int idx, int i);
// static char	*check_itoa(int last_stat, int *is_itoa);

/**
 * @brief  function to support environment variable expansion and $?.
 *  loops trough the current list and through each cmd.exe element and
 *  if finds a expandable variable it catches the value from environment
 *  if exists and modifiies the cmd.exe element with tht expanded value.
 *
 * @param l_pipex struct for the list
 * @return int returns -1 in case of error or 0 otherwise
 */
int	env_var_extension(t_pipex *l_pipex)
{
	int		i;
	char	*new_str;

	i = 0;
	if (l_pipex == NULL || l_pipex->cmd.exe == NULL || !*l_pipex->cmd.exe)
		return (0);
	while (l_pipex->cmd.exe[i] != NULL)
	{
		if (l_pipex->cmd.token_kind[i] == TOKEN_WORD
			|| l_pipex->cmd.token_kind[i] == TOKEN_NAME
			|| l_pipex->cmd.token_kind[i] == TOKEN_DOUBLE_QUOTED_STR)
		{
			new_str = subst_env_var(ft_strdup(l_pipex->cmd.exe[i]), l_pipex);
			if (new_str == NULL)
				return (1);
			free(l_pipex->cmd.exe[i]);
			l_pipex->cmd.exe[i] = new_str;
		}
		i++;
	}
	return (0);
}

// static char	*check_itoa(int last_stat, int *is_itoa)
// {
// 	*is_itoa = 1;
// 	return (ft_itoa(last_stat));
// }

// static int	modify_cmd_exe(t_pipex *l_pipex, int i, int idx, char *var_env)
// {
// 	char	*new_text;
// 	size_t	len_var_env;

// 	len_var_env = ft_strlen(var_env);
// 	new_text = (char *)ft_calloc((idx + 1) + len_var_env + 1, sizeof(char));
// 	if (new_text == NULL)
// 	{
// 		ft_putstr_fd("Error: mem alloc env_var_extension\n",
// 			STDERR_FILENO);
// 		return (1);
// 	}
// 	ft_memcpy(new_text, var_env, len_var_env);
// 	free(l_pipex->cmd.exe[i]);
// 	l_pipex->cmd.exe[i] = new_text;
// 	return (0);
// }

// static int	env_var_extension_helper(t_pipex *l_pipex, int idx, int i)
// {
// 	int		is_itoa;
// 	char	*var_env;

// 	is_itoa = 0;
// 	if (idx != -1)
// 	{
// 		if (l_pipex->cmd.exe[i][idx + 1] == '?')
// 			var_env = check_itoa(l_pipex->last_stat, &is_itoa);
// 		else
// 			var_env = get_env_key_value(&(l_pipex->cmd.exe[i][idx + 1]),
// 					*(l_pipex->ptr_env_heap));
// 		if (var_env == NULL)
// 		{
// 			if (modify_cmd_exe(l_pipex, i, idx, "\0") == 1)
// 				return (1);
// 			return (-1);
// 		}
// 		if (modify_cmd_exe(l_pipex, i, idx, var_env) == 1)
// 			return (1);
// 		if (is_itoa == 1)
// 			free(var_env);
// 	}
// 	return (0);
// }

// /**
//  * @brief / will scan the string and search for the $ and check if
//  *  the environment extension is possible. returns id of the dollar sign if
//  *  there is a march or -1 otherwise
//  *
//  * @param str string to searched
//  * @return int index of the match if found otherwise -1
//  */
// static int	scan_env_extens(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] == '$' && (str[i + 1] == '?'
// 				|| ft_isalnum(str[i + 1]) == 1
// 				|| str[i + 1] == '_' ))
// 			return (i);
// 		i++;
// 	}
// 	return (-1);
// }

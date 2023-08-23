/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fuctions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 10:48:53 by lilizarr          #+#    #+#             */
/*   Updated: 2023/08/17 13:24:35 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	find_cmd_path(char **env_path, char *tmp_cmd, char **cmd_path)
{
	char	*path_tmp;
	char	*exe_path;
	int		i;

	i = 0;
	if (env_path == NULL)
		return ;
	while (env_path[i] != NULL && tmp_cmd)
	{
		path_tmp = ft_strjoin(env_path[i], "/");
		if (ft_strnstr(tmp_cmd, path_tmp, ft_strlen(tmp_cmd)))
			tmp_cmd = tmp_cmd + ft_strlen(path_tmp);
		exe_path = ft_strjoin(path_tmp, tmp_cmd);
		if (access(exe_path, X_OK | F_OK) == 0)
		{
			*cmd_path = ft_strdup(exe_path);
			tmp_cmd = NULL;
		}
		free(path_tmp);
		free(exe_path);
		i++;
	}
}

void	cmd_exe(t_pipex *node)
{
	char		*tmp_cmd;
	char		**env_path;

	if (!node->cmd.exe)
		return ;
	tmp_cmd = node->cmd.exe[0];
	if (tmp_cmd && ft_strchr(tmp_cmd, '/') && (access(tmp_cmd, X_OK) == -1))
		ft_error(strerror(errno), tmp_cmd, 1);
	env_path = ft_split(node->paths, ':');
	find_cmd_path(&*env_path, tmp_cmd, &node->cmd.path);
	if (env_path)
		env_path = ft_free(env_path);
	if (!node->cmd.path)
	{
		if (ft_strchr(tmp_cmd, '/') && access(tmp_cmd, X_OK) == 0)
			env_path = ft_split(*node->cmd.exe, '/');
		find_cmd_path(&*env_path, tmp_cmd, &node->cmd.path);
		if (env_path)
			env_path = ft_free(env_path);
	}
}

static void	new_env(t_pipex *h)
{
	int		i;
	int		size_env;
	t_env	*env;

	i = 0;
	env = *(h->ptr_env_heap);
	size_env = getenvheap_size(env);
	h->cmd.exe = (char **)ft_calloc(sizeof(char *), size_env + 1);
	while (i <= size_env)
	{
		h->cmd.exe[i] = ft_strjoin_gnl(env[i].key, "=", 0);
		h->cmd.exe[i] = ft_strjoin_gnl(h->cmd.exe[i], env[i].value, 1);
		i++;
	}
}

void	cmd(t_pipex *node)
{
	struct stat	dir;

	if (pipex_builtin_integration(node) != -1)
		exit(node->last_stat);
	if ((!node->cmd.exe && (node->file[0].name || node->file[1].name)))
		return ;
	cmd_exe(node);
	new_env(node->head);
	if (node->cmd.path == (void *)0)
	{
		if (!ft_strchr(node->cmd.exe[0], '/'))
			ft_error(node->cmd.exe[0], "command not found", 1);
		else
			node->cmd.path = ft_strdup(node->cmd.exe[0]);
	}
	execve(node->cmd.path, node->cmd.exe, node->head->cmd.exe);
	if (stat(node->cmd.exe[0], &dir) == 0)
		ft_error(node->cmd.exe[0], strerror(EISDIR), 1);
	else
		ft_error(node->cmd.exe[0], strerror(errno), 1);
}

void	fill_cmd(t_pipex *p_cmd, char **tmp_cmd)
{
	int	i;

	i = 0;
	while (p_cmd->cmd.exe[i])
	{
		if (!*tmp_cmd)
			*tmp_cmd = ft_strdup(p_cmd->cmd.exe[0]);
		else
		{
			*tmp_cmd = ft_strjoin_gnl((*tmp_cmd), "`", 1);
			if (*p_cmd->cmd.exe[i] == '\0')
				*tmp_cmd = ft_strjoin_gnl((*tmp_cmd), " `", 1);
			else
				*tmp_cmd = ft_strjoin_gnl((*tmp_cmd), p_cmd->cmd.exe[i], 1);
		}
		i++;
	}
	if (**tmp_cmd == 0)
	{
		free(*tmp_cmd);
		*tmp_cmd = NULL;
	}
}

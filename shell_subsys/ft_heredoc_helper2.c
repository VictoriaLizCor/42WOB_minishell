/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_helper2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranero <mgranero@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 10:18:51 by mgranero          #+#    #+#             */
/*   Updated: 2023/08/12 16:50:28 by mgranero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_subsys.h"

static char	*modify_line(char *line, int idx, char *key, char *var_env);
static void	free_helper(int is_itoa, t_hdoc *hdoc, char *var_env);
static char	*modify_line_no_match(char *line, t_hdoc *hdoc);

static char	*get_var_env(char c, t_hdoc *hdoc, t_pipex *l_pipex)
{
	char	*var_env;

	hdoc->is_itoa = 0;
	if (c == '?')
	{
		if (l_pipex->head->last_stat > 255)
			l_pipex->head->last_stat -= 255;
		var_env = ft_itoa(l_pipex->head->last_stat);
		hdoc->is_itoa = 1;
	}
	else
		var_env = get_env_key_value(hdoc->key,
				*(l_pipex->ptr_env_heap));
	return (var_env);
}

char	*subst_env_var_helper(char *line, t_pipex *l_pipex, t_hdoc *hdoc)
{
	char	*var_env;

	var_env = get_var_env(line[hdoc->idx + 1], hdoc, l_pipex);
	if (var_env == NULL)
	{
		line = modify_line_no_match(line, hdoc);
		free(hdoc->key);
		return (line);
	}
	else
		line = modify_line(line, hdoc->idx, hdoc->key, var_env);
	if (line == NULL)
	{
		free(hdoc->key);
		if (hdoc->is_itoa == 1)
			free(var_env);
		hdoc->start = -1;
		return (NULL);
	}
	free_helper(hdoc->is_itoa, hdoc, var_env);
	return (line);
}

// norminette
static char	*modify_line_no_match(char *line, t_hdoc *hdoc)
{
	int		size_key;
	char	*new_line;
	int		size_line;

	size_key = ft_strlen(hdoc->key);
	size_line = ft_strlen(line);
	if (size_line - size_key - 1 == 0)
	{
		new_line = (char *)ft_calloc(1, sizeof(char));
		*new_line = '\0';
		free(line);
		return (new_line);
	}
	new_line = get_new_line(line, hdoc, size_line, size_key);
	return (new_line);
}

static void	free_helper(int is_itoa, t_hdoc *hdoc, char *var_env)
{
	hdoc->start = hdoc->idx + ft_strlen(var_env);
	if (is_itoa == 1)
		free(var_env);
	free(hdoc->key);
}

static char	*modify_line(char *line, int idx, char *key, char *var_env)
{
	char	*new_text;
	size_t	len_var_env;
	size_t	new_size;

	len_var_env = ft_strlen(var_env);
	new_size = ft_strlen(line) - 1 - ft_strlen(key) + len_var_env + 1;
	if (new_size <= 0)
	{
		ft_putstr_fd("Error: new size modify line heredoc\n",
			STDERR_FILENO);
		return (NULL);
	}
	new_text = (char *)ft_calloc(new_size, sizeof(char));
	if (new_text == NULL)
	{
		ft_putstr_fd("Error: mem alloc modify line heredoc\n",
			STDERR_FILENO);
		return (NULL);
	}
	ft_memcpy(new_text, line, idx);
	ft_memcpy(new_text + idx, var_env, len_var_env + 1);
	ft_memcpy(new_text + idx + len_var_env, line + idx + 1 + ft_strlen(key),
		new_size - idx - len_var_env - 1);
	free(line);
	return (new_text);
}

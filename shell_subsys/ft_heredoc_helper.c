/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranero <mgranero@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 20:52:38 by mgranero          #+#    #+#             */
/*   Updated: 2023/08/14 13:40:44 by mgranero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_subsys.h"

static void	scan_env_extens_heredoc(char *str, int start, t_hdoc *hdoc);
static void	count_characters(char *str, int *cnt_char, int i);

int	search_expand_env_vars(char **doc, int size, t_pipex *l_pipex)
{
	int		i;

	i = 0;
	while (i < size)
	{
		*doc = subst_env_var(*doc, l_pipex);
		i++;
	}
	return (0);
}

char	*subst_env_var(char *line, t_pipex *l_pipex)
{
	t_hdoc	hdoc;

	if (l_pipex->ptr_env_heap == NULL)
	{
		ft_putstr_fd("Error: subst_env_var empty ptr_env_heap\n", STDERR_FILENO);
		return (NULL);
	}
	hdoc.start = 0;
	while (hdoc.start < (int)ft_strlen(line))
	{
		hdoc.idx = -1;
		hdoc.key = NULL;
		scan_env_extens_heredoc(line, hdoc.start, &hdoc);
		if (hdoc.idx != -1)
		{
			line = subst_env_var_helper(line, l_pipex, &hdoc);
			if (hdoc.start == -1 || line == NULL)
				break ;
		}
		else
			break ;
	}
	return (line);
}

static void	scan_env_extens_heredoc(char *str, int start, t_hdoc *hdoc)
{
	int	i;
	int	cnt_char;

	i = start;
	cnt_char = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$' && (str[i + 1] == '?' || str[i + 1] == '_'
				|| ft_isalpha(str[i + 1]) == 1))
		{
			count_characters(str, &cnt_char, i);
			hdoc->key = ft_strdup_len(str + i + 1, cnt_char);
			hdoc->idx = i;
			return ;
		}
		i++;
	}
	hdoc->idx = -1;
}

static void	count_characters(char *str, int *cnt_char, int i)
{
	int	j;

	if (str[i + 1] == '?')
	{
		*cnt_char = 1;
		return ;
	}
	j = i + 1;
	while (str[j] != '\0'
		&& (ft_isalnum(str[j]) == 1 || str[j] == '_' ))
	{
		*cnt_char = *cnt_char + 1;
		j++;
	}
}

char	*get_new_line(char *line, t_hdoc *hdoc, int size_line, int size_key)
{
	int		i;
	int		j;
	char	*new_line;

	new_line = (char *)ft_calloc(size_line - size_key - 1, sizeof(char) + 1);
	i = 0;
	while (i < hdoc->idx)
	{
		new_line[i] = line[i];
		i++;
	}
	j = i;
	i = i + size_key + 1;
	while (i < size_line)
	{
		new_line[j] = line[i];
		i++;
		j++;
	}
	free (line);
	return (new_line);
}

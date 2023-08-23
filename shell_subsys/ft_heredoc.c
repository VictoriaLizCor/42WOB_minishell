/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranero <mgranero@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 09:13:19 by mgranero          #+#    #+#             */
/*   Updated: 2023/08/14 14:56:46 by mgranero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_subsys.h"

static int	str_compare_no_trim(char *str1, char *str2);
static void	print2pipe(char **doc, t_pipex *l_pipex);
static int	jump_tab(char *line);
static int	get_doc(int tab_supress, char *delimiter, t_pipex *l_pipex);

// static int	get_doc(char **doc, int tab_supress, char *delimiter,
// 				int fd_stdin_bkup);
// size = get_doc(doc, tab_supress, delimiter, l_pipex->fd_stdin_bkup);
int	ft_heredoc(t_pipex *l_pipex)
{
	char	*delimiter;
	int		tab_supress;

	if (l_pipex->cmd.exe[1] == NULL)
		return (1);
	if (str_compare(l_pipex->cmd.exe[1], "-") == 0)
	{
		tab_supress = 1;
		if (l_pipex->cmd.exe[2] == NULL)
			return (1);
		delimiter = l_pipex->cmd.exe[2];
	}
	else
	{
		tab_supress = 0;
		delimiter = l_pipex->cmd.exe[1];
	}
	if (get_doc(tab_supress, delimiter, l_pipex) == 1)
		return (1);
	return (0);
}

// if there is pipe, print the output otherwise prints nothing
// isatty checks if stdout is a terminal or not?
static void	print2pipe(char **doc, t_pipex *l_pipex)
{
	if (*doc != NULL)
	{
		if (l_pipex->pipex[1] != -1)
		{
			ft_putstr_fd(*doc, l_pipex->pipex[1]);
			ft_putchar_fd('\n', l_pipex->pipex[1]);
		}
	}
}

// dup2(fd_stdin_bkup, STDIN_FILENO);
// close_fd (open pipe for STDIN)
// static int	get_doc(char **doc, int tab_supress,
// 				char *delimiter, int fd_stdin_bkup)
static int	get_doc(int tab_supress, char *delm, t_pipex *l_pipex)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (line != NULL)
		{
			if ((tab_supress == 0 && str_compare_no_trim(line, delm) == 0)
				|| (tab_supress == 1
					&& str_compare_no_trim(line + jump_tab(line), delm) == 0))
			{
				free(line);
				break ;
			}
			if (search_expand_env_vars(&line, ft_strlen(line), l_pipex) == 1)
				return (1);
			print2pipe(&line, l_pipex);
			free(line);
		}
		else
			break ;
	}
	return (0);
}

static int	str_compare_no_trim(char *str1, char *str2)
{
	int		len_str1;
	int		len_str2;

	if (str1 == NULL || str2 == NULL)
		return (-1);
	len_str1 = ft_strlen(str1);
	len_str2 = ft_strlen(str2);
	if (len_str1 == len_str2
		&& ft_strncmp(str1, str2, len_str1) == 0)
		return (0);
	return (1);
}

static int	jump_tab(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ASCII_HORIZ_TAB)
		i++;
	return (i);
}

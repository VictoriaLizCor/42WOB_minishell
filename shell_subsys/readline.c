/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranero <mgranero@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:34:07 by mgranero          #+#    #+#             */
/*   Updated: 2023/08/18 11:02:58 by mgranero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_subsys.h"

static int	prompt(t_shell *shell_var, t_Lexer lex_heap);
static void	update_node_last_exec(t_pipex *l_pipex, t_shell *shell_var);
static int	check_buff_spc_tab(char *buffer);

int	prompt_readline(t_env *env_heap)
{
	t_Lexer	lex_heap;
	t_shell	shell_var;
	int		ret;

	ft_memset(&lex_heap, 0, sizeof(t_Lexer));
	shell_var.env_heap = env_heap;
	shell_var.last_exec = 0;
	ret = prompt(&shell_var, lex_heap);
	printf("\n");
	free_env_heap(shell_var.env_heap);
	return (ret);
}

static int	prompt(t_shell *shell_var, t_Lexer lex_heap)
{
	char	*buff_heap;
	t_pipex	*l_pipex;
	t_term	bckup_term;
	int		exit_val;

	bckup_term = get_term_configs();
	while (1)
	{
		buff_heap = readline("\033[1;32mminishell$  \033[0m");
		if (buff_heap == NULL)
			return (0);
		l_pipex = NULL;
		if (ft_strlen(buff_heap) > 0 && check_buff_spc_tab(buff_heap) == 0)
		{
			add_history(buff_heap);
			exit_val = check_exit(buff_heap);
			if (exit_val > 0)
				return (exit_val);
			launcher(buff_heap, shell_var, lex_heap, l_pipex);
			if (shell_var->env_heap == NULL)
				return (free_buff_ret_1(buff_heap));
		}
		free(buff_heap);
		set_term_configs(bckup_term);
	}
	free(buff_heap);
	return (0);
}

void	launcher(char *buffer, t_shell *shell_var,
					t_Lexer lex_heap, t_pipex *l_pipex)
{
	lex_heap = lexer(buffer);
	if (lex_heap.error == 0)
	{
		l_pipex = parser(&lex_heap, shell_var->env_heap, 0);
		free_lexer(&lex_heap);
		if (l_pipex != NULL)
		{
			l_pipex->last_stat = shell_var->last_exec;
			update_node_last_exec(l_pipex, shell_var);
			ft_setup_sighandler_non_interact();
			run_fork(&l_pipex);
			ft_memset(&g_sig, -1, sizeof(g_sig));
			g_sig.idx = 0;
			ft_setup_sighandler();
			shell_var->env_heap = *(l_pipex->ptr_env_heap);
			shell_var->last_exec = l_pipex->last_stat;
			free_list_pipex(l_pipex);
		}
	}
	else
		free_lexer(&lex_heap);
}

static void	update_node_last_exec(t_pipex *l_pipex, t_shell *shell_var)
{
	t_pipex	*node;

	node = l_pipex;
	while (node != NULL)
	{
		node->last_stat = shell_var->last_exec;
		node = node->next;
	}
}

static int	check_buff_spc_tab(char *buffer)
{
	int	i;
	int	buf_len;

	buf_len = ft_strlen(buffer);
	i = 0;
	while (buffer[i] != '\0' && (buffer[i] == ' '
			|| buffer[i] == '\t' || buffer[i] == '\v'
			|| buffer[i] == '\n'))
		i++;
	if (i == buf_len)
		return (1);
	return (0);
}

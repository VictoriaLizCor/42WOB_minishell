/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranero <mgranero@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 21:03:20 by mgranero          #+#    #+#             */
/*   Updated: 2023/08/15 17:23:30 by mgranero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int		is_cmd_pos0_valid(t_Lexer *lex, t_parser *p);
static void		fill_header_list(t_parser *p, t_env *env_heap);

t_pipex	*parser(t_Lexer *lex, t_env *env_heap, int scase)
{
	t_parser	p;

	ft_memset(&p, 0, sizeof(t_parser));
	p.env_heap = env_heap;
	while (p.i < lex->tokens_count)
	{
		if ((scase == 0 && (is_cmd_pos0_valid(lex, &p) == -1
					|| add_cmd(lex, &p) == -1))
			|| (scase == 1 && add_cmd(lex, &p) == -1))
		{
			free_list_pipex(p.list_exec);
			return (NULL);
		}
		p.i = p.i + 1;
	}
	if (add_new_empty_node(&p) == -1)
	{
		free_list_pipex(p.list_exec);
		return (NULL);
	}
	fill_header_list(&p, env_heap);
	if (DEBUG_PARSER == 1 && p.list_exec != NULL)
		print_pipex_list(p.list_exec);
	return (p.list_exec);
}

/**
 * @brief fill data in empty header list
 *
 * @param p
 */
static void	fill_header_list(t_parser *p, t_env *env_heap)
{
	t_pipex	*list;

	p->list_exec->pipex_status[0] = -1;
	p->list_exec->pipex_status[1] = -1;
	p->list_exec->pipex[0] = -1;
	p->list_exec->pipex[1] = -1;
	p->list_exec->child_pid = -255;
	list = p->list_exec;
	while (list != NULL)
	{
		list->head = p->list_exec;
		list->ptr_env_heap = (t_env **)ft_calloc(1, sizeof(t_env *));
		*(list->ptr_env_heap) = env_heap;
		list = list->next;
	}
}

/**
 * @brief function will check if it is the first element of command (position 0)
 *  and if it is not it will return 0.
 *  If it is, function will check if this first element of the command is
 *  a valid Name, Word, Less, Great, Double Great and Double Less Token; and
 *  return 1.
 *  It the token is invalid it will return -1.
 *
 * @param lex struct lexer
 * @param p struct parser
 * @return int returns 0 if the command position is not 0 or if it TOKEN_END.
 *  return 1 if a command is a valid token for position 0.
 *  returns -1 if a command is invalid token for position 0.
 */
static int	is_cmd_pos0_valid(t_Lexer *lex, t_parser *p)
{
	if (p->pos_in_cmd == 0 && lex->cmd_line_tok[p->i].token_kind != TOKEN_END)
	{
		if (lex->cmd_line_tok[p->i].token_kind == TOKEN_NAME
			|| lex->cmd_line_tok[p->i].token_kind == TOKEN_WORD
			|| lex->cmd_line_tok[p->i].token_kind == TOKEN_LESS
			|| lex->cmd_line_tok[p->i].token_kind == TOKEN_GREAT
			|| lex->cmd_line_tok[p->i].token_kind == TOKEN_DLESS
			|| lex->cmd_line_tok[p->i].token_kind == TOKEN_DGREAT
			|| lex->cmd_line_tok[p->i].token_kind == TOKEN_SINGLE_QUOTED_STR
			|| lex->cmd_line_tok[p->i].token_kind == TOKEN_DOUBLE_QUOTED_STR)
		{
			p->idx_pos0 = p->i;
			return (1);
		}
		else
			return (put_error_str("Error: Grammar first argument\n"));
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check_redirect_dless.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranero <mgranero@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:01:41 by mgranero          #+#    #+#             */
/*   Updated: 2023/07/13 16:42:23 by mgranero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	d_less_helper(t_parser *p);
static int	check_dless(t_Lexer *lex, t_parser *p);

int	chk_redirect_dless(t_Lexer *lex, t_parser *p)
{
	if (lex->cmd_line_tok[p->i].token_kind == TOKEN_DLESS)
	{
		if (p->pos_in_cmd > 0)
			return (chk_redirect_terminate_previous(lex, p));
		else
		{
			p->nb_of_elem = p->nb_of_elem + 1;
			p->size_cmd_exe = p->size_cmd_exe + 1;
			if (lex->cmd_line_tok[p->i + 1].token_kind == TOKEN_NAME
				|| lex->cmd_line_tok[p->i + 1].token_kind == TOKEN_WORD)
			{
				return (check_dless(lex, p));
			}
			else
				return (put_error_str("Error: Grammar heredoc\n"));
		}
		return (1);
	}
	return (0);
}

static void	d_less_helper(t_parser *p)
{
	p->nb_of_elem = p->nb_of_elem + 1;
	p->size_cmd_exe = p->size_cmd_exe + 1;
	p->pos_in_cmd = p->pos_in_cmd + 2;
	p->i = p->i + 1;
}

static int	check_dless(t_Lexer *lex, t_parser *p)
{
	d_less_helper(p);
	if (lex->cmd_line_tok[p->i].text_len == 1
		&& lex->cmd_line_tok[p->i].text[0] == '-')
	{
		if (lex->cmd_line_tok[p->i + 1].token_kind == TOKEN_NAME
			|| lex->cmd_line_tok[p->i + 1].token_kind == TOKEN_WORD)
		{
			p->nb_of_elem = p->nb_of_elem + 1;
			p->size_cmd_exe = p->size_cmd_exe + 1;
			p->pos_in_cmd = p->pos_in_cmd + 1;
			p->i = p->i + 1;
		}
		else
			return (put_error_str("Error: Grammar heredoc supression\n"));
	}
	if (add_list_node(lex, p) == -1)
		return (-1);
	p->pos_in_cmd = 0;
	if (lex->cmd_line_tok[p->i + 1].token_kind == TOKEN_PIPE
		&& lex->cmd_line_tok[p->i + 2].token_kind != TOKEN_NAME
		&& lex->cmd_line_tok[p->i + 2].token_kind != TOKEN_WORD)
		return (put_error_str("Error: pipe position\n"));
	else if (lex->cmd_line_tok[p->i + 1].token_kind == TOKEN_PIPE)
		p->i = p->i + 1;
	return (1);
}

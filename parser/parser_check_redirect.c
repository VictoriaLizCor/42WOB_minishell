/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check_redirect.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranero <mgranero@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 10:27:47 by mgranero          #+#    #+#             */
/*   Updated: 2023/08/02 20:53:30 by mgranero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	chk_redirect_helper(t_Lexer *lex, t_parser *p);

int	chk_redirect(t_Lexer *lex, t_parser *p)
{
	t_Token_kind	curr;

	curr = lex->cmd_line_tok[p->i].token_kind;
	if (curr == TOKEN_LESS || curr == TOKEN_GREAT || curr == TOKEN_DGREAT)
	{
		if (p->pos_in_cmd > 0)
			return (chk_redirect_terminate_previous(lex, p));
		else
		{
			p->nb_of_elem = p->nb_of_elem + 1;
			p->size_cmd_exe = p->size_cmd_exe + 1;
			if (lex->cmd_line_tok[p->i + 1].token_kind == TOKEN_NAME
				|| lex->cmd_line_tok[p->i + 1].token_kind == TOKEN_WORD)
				return (chk_redirect_helper(lex, p));
			else
				return (put_error_str("Error: Grammar redirection\n"));
		}
	}
	return (0);
}

int	chk_redirect_terminate_previous(t_Lexer *lex, t_parser *p)
{
	if (add_list_node(lex, p) == -1)
		return (-1);
	p->pos_in_cmd = 0;
	if (lex->cmd_line_tok[p->i + 1].token_kind == TOKEN_PIPE
		&& (lex->cmd_line_tok[p->i + 2].token_kind != TOKEN_NAME
			&& lex->cmd_line_tok[p->i + 2].token_kind != TOKEN_WORD))
		return (put_error_str("Error: Grammar cmd after a pipe\n"));
	else if (lex->cmd_line_tok[p->i + 1].token_kind == TOKEN_PIPE)
		p->i = p->i;
	else if (lex->cmd_line_tok[p->i + 1].token_kind != TOKEN_PIPE)
		p->i = p->i - 1;
	return (1);
}

static int	chk_redirect_helper(t_Lexer *lex, t_parser *p)
{
	p->nb_of_elem = p->nb_of_elem + 1;
	p->size_cmd_exe = p->size_cmd_exe + 1;
	p->pos_in_cmd = p->pos_in_cmd + 2;
	p->i = p->i + 1;
	if (add_list_node(lex, p) == -1)
		return (-1);
	p->pos_in_cmd = 0;
	if (lex->cmd_line_tok[p->i + 1].token_kind == TOKEN_PIPE
		&& lex->cmd_line_tok[p->i + 2].token_kind != TOKEN_NAME
		&& lex->cmd_line_tok[p->i + 2].token_kind != TOKEN_WORD
		&& lex->cmd_line_tok[p->i + 2].token_kind != TOKEN_LESS
		&& lex->cmd_line_tok[p->i + 2].token_kind != TOKEN_GREAT
		&& lex->cmd_line_tok[p->i + 2].token_kind != TOKEN_DLESS
		&& lex->cmd_line_tok[p->i + 2].token_kind != TOKEN_DGREAT)
		return (put_error_str("Error: pipe position\n"));
	else if (lex->cmd_line_tok[p->i + 1].token_kind == TOKEN_PIPE)
		p->i = p->i + 1;
	return (1);
}

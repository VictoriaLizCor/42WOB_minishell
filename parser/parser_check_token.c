/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranero <mgranero@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 10:10:49 by mgranero          #+#    #+#             */
/*   Updated: 2023/07/13 15:15:45 by mgranero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int		chk_pipe_end(t_Lexer *lex, t_parser *p);
static int		chk_word_name_quote(t_Lexer *lex, t_parser *p);

/**
 * @brief check elements in n position except for position 0.
 *
 * @param lex struct lexer
 * @param p struct parser
 * @param list_exec list for pipex executions
 * @return int returns 0 if not tokens where found.
 *  1 if there where matches and -1 if there are errors.
 */
int	add_cmd(t_Lexer *lex, t_parser *p)
{
	int	ret;

	ret = chk_pipe_end(lex, p);
	if (ret != 0)
		return (ret);
	ret = chk_word_name_quote(lex, p);
	if (ret != 0)
		return (ret);
	ret = chk_redirect(lex, p);
	if (ret != 0)
		return (ret);
	ret = chk_redirect_dless(lex, p);
	if (ret != 0)
		return (ret);
	printf("%sToken: %s,", CRED, get_token_name(lex->cmd_line_tok[p->i]));
	printf("not supported by parser yet. %s\n", CWHT);
	return (-1);
}

/**
 * @brief function checks if the tokens passed are END or PIPE otherwise return
 *  0. If the tokens are END and PIPE it will check if the next element are
 *  a Name or Word. If yes it returns 1, otherwise returns -1 for error in
 *  the grammar.
 *
 * @param lex struct lexer
 * @param p struct parser
 * @param list_exec list for pipex executions
 * @return int return 0 if tokens is not pipe or end; returns 1 if it is and if
 *  current element is a pipe and next is a word or name; return -1 otherwise.
 */
static int	chk_pipe_end(t_Lexer *lex, t_parser *p)
{
	if (lex->cmd_line_tok[p->i].token_kind == TOKEN_PIPE
		|| lex->cmd_line_tok[p->i].token_kind == TOKEN_END)
	{
		if (p->pos_in_cmd == 0
			&& lex->cmd_line_tok[p->i].token_kind == TOKEN_END)
			return (1);
		if (lex->cmd_line_tok[p->i].token_kind == TOKEN_PIPE
			&& lex->cmd_line_tok[p->i + 1].token_kind != TOKEN_NAME
			&& lex->cmd_line_tok[p->i + 1].token_kind != TOKEN_WORD
			&& lex->cmd_line_tok[p->i + 1].token_kind != TOKEN_DGREAT
			&& lex->cmd_line_tok[p->i + 1].token_kind != TOKEN_DLESS
			&& lex->cmd_line_tok[p->i + 1].token_kind != TOKEN_LESS
			&& lex->cmd_line_tok[p->i + 1].token_kind != TOKEN_GREAT)
			return (put_error_str("Error: Grammar cmd after a pipe\n"));
		if (add_list_node(lex, p) == -1)
			return (-1);
		p->pos_in_cmd = 0;
		return (1);
	}
	return (0);
}

static int	chk_word_name_quote(t_Lexer *lex, t_parser *p)
{
	if (lex->cmd_line_tok[p->i].token_kind == TOKEN_WORD
		|| lex->cmd_line_tok[p->i].token_kind == TOKEN_NAME
		|| lex->cmd_line_tok[p->i].token_kind == TOKEN_ASSIGNMENT_WORD
		|| lex->cmd_line_tok[p->i].token_kind == TOKEN_SINGLE_QUOTED_STR
		|| lex->cmd_line_tok[p->i].token_kind == TOKEN_DOUBLE_QUOTED_STR)
	{
		p->size_cmd_exe = p->size_cmd_exe + 1;
		p->pos_in_cmd = p->pos_in_cmd + 1;
		p->nb_of_elem = p->nb_of_elem + 1;
		return (1);
	}
	return (0);
}

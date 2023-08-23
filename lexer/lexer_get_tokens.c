/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_get_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranero <mgranero@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 09:34:32 by mgranero          #+#    #+#             */
/*   Updated: 2023/08/14 17:36:02 by mgranero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	is_token_literals(char c, t_Toklit	tok_lit);
static void	trim_left_spaces(t_Lexer *l);
static void	ft_token_end(t_Lexer *l, t_Token *token);

/**
 * @brief function analyses the command line in a specific l->iter index,
 *   character per character until a token is found and this token struct
 *   is built and returned. Function must be called in a loop until the
 *   TOKEN_END token is returned indicating that the string is at the
 *   end.
 *
 * @param l
 * @param tok_lit
 * @return t_Token
 */
t_Token	lexer_get_tokens(t_Lexer *l, t_Toklit tok_lit)
{
	t_Token	token;
	int		ret_is_literal;

	ft_memset(&token, 0, sizeof(token));
	trim_left_spaces(l);
	ret_is_literal = is_token_literals(l->cmd_line[l->iter], tok_lit);
	if (l->cmd_line[l->iter] == '\0')
		ft_token_end(l, &token);
	else if ((l->cmd_line[l->iter] == '>' && l->cmd_line[l->iter + 1] == '>')
		|| (l->cmd_line[l->iter] == '<' && l->cmd_line[l->iter + 1] == '<'))
		ft_token_dgreat_dless(l, &token);
	else if (ret_is_literal != -1)
		ft_token_lit(l, &token, tok_lit, ret_is_literal);
	else if (l->cmd_line[l->iter] == ASCII_SINGLE_QUOTE
		|| l->cmd_line[l->iter] == ASCII_DOUBLE_QUOTE)
		ft_token_quotes(l, &token);
	else if (ft_isalpha(l->cmd_line[l->iter]) == 1
		|| l->cmd_line[l->iter] == '_')
		ft_token_name(l, &token);
	else
		ft_token_word(l, &token);
	return (token);
}

/**
 * @brief creates and return token end if
 *  a terminator is found
 *
 * @param l struct lexer
 * @param token struct token to be updated with token
 *  end values
 */
static void	ft_token_end(t_Lexer *l, t_Token *token)
{
	token->token_kind = TOKEN_END;
	token->text = ft_calloc(1, sizeof(char));
	if (token->text == NULL)
	{
		l->error = 1;
		return ;
	}
	*token->text = '\0';
	token->text_len = 1;
	token->id = l->iter;
	l->tokens_count = l->tokens_count + 1;
	token->id = l->tokens_count;
}

/**
 * @brief trims left spaces and new lines from a give string
 *  by incrementing the iter variable inside lexer struct
 * @param l  pointer to lexer struct
 * @param token returns
 */
static void	trim_left_spaces(t_Lexer *l)
{
	while (l->cmd_line[l->iter] == ' ' || l->cmd_line[l->iter] == '\n'
		|| l->cmd_line[l->iter] == '\t' || l->cmd_line[l->iter] == '\v')
		l->iter = l->iter + 1;
}

/**
 * @brief checks if the given char is a match for any of the
 *  token literals chars and if its is, returns index of the
 *  matching token literal so the matching text of the token
 *  can also be retrieved.
 *
 * @param c char to be compared to the char literals
 * @param tok_lit struct with token literals data
 * @return int -1 if no match is found, otherwise the index of
 *  the match
 */
static int	is_token_literals(char c, t_Toklit	tok_lit)
{
	int	i;

	i = 0;
	while (i < tok_lit.size_char_literals)
	{
		if (c == tok_lit.char_literals[i])
			return (i);
		i++;
	}
	return (-1);
}

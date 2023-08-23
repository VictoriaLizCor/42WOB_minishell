/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranero <mgranero@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 08:42:45 by mgranero          #+#    #+#             */
/*   Updated: 2023/08/06 17:16:54 by mgranero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static t_Lexer	create_new_lexer(char *command_line);
static t_Toklit	init_token_literals_struct(void);
static int		append_token_to_lexer(t_Lexer *l, t_Token token);

/**
 * @brief function analyse the command_line character by character and group
 *  them in pre-defined groups named as Tokens.
 *
 * @param command_line char * command line passed by the user
 * @return t_Lexer a lexer struct containing informations about the command
 *  line passed and the created cmd_line_tok with an array of Token types
 */
t_Lexer	lexer(char *command_line)
{
	t_Lexer		l;
	t_Token		token;
	t_Toklit	tok_lit;

	l = create_new_lexer(command_line);
	tok_lit = init_token_literals_struct();
	token.token_kind = TOKEN_INVALID;
	while (token.token_kind != TOKEN_END)
	{
		token = lexer_get_tokens(&l, tok_lit);
		if (l.error != 0 || token.text == NULL
			|| token.token_kind == TOKEN_INVALID
			|| append_token_to_lexer(&l, token) == -1)
		{
			l.error = 1;
			return (l);
		}
	}
	if (DEBUG_LEXER == 1)
		print_lexer_tokens(&l);
	return (l);
}

/**
 * @brief function free the memory allocated in the struct
 *  lexer
 *
 * @param l lexer struct
 */
void	free_lexer(t_Lexer *l)
{
	int	i;

	i = l->tokens_count - 1;
	while (i >= 0)
	{
		if (l->cmd_line_tok[i].text != NULL)
			free(l->cmd_line_tok[i].text);
		l->cmd_line_tok[i].text = 0;
		i--;
	}
	if (l->cmd_line_tok != NULL)
		free(l->cmd_line_tok);
	l->cmd_line_tok = 0;
	return ;
}

/**
 * @brief Create a new lexer struct and initialize the internal
 *  values
 *
 * @param command_line command line from readline
 * @return t_Lexer returns a initialized Lexer
 */
static t_Lexer	create_new_lexer(char *command_line)
{
	t_Lexer	l;

	ft_memset(&l, 0, sizeof(t_Lexer));
	l.cmd_line = command_line;
	l.cmd_line_len = ft_strlen(command_line);
	return (l);
}

/**
 * @brief Initialize the token literals char and token kind
 *  and returns a struct containg this data to be used
 *  to find if a token a token literal is
 *
 * @return tok_lit struct with token literals and
 *  there char (c_) with associated kind (k_)
 */
static t_Toklit	init_token_literals_struct(void)
{
	t_Toklit	tok_lit;

	ft_memset(&tok_lit, 0, sizeof(tok_lit));
	tok_lit.char_literals[0] = '|';
	tok_lit.token_kind_literals[0] = TOKEN_PIPE;
	tok_lit.char_literals[1] = '<';
	tok_lit.token_kind_literals[1] = TOKEN_LESS;
	tok_lit.char_literals[2] = '>';
	tok_lit.token_kind_literals[2] = TOKEN_GREAT;
	tok_lit.size_char_literals = 3;
	return (tok_lit);
}

/**
 * @brief reallocate memory from lexer command line token (cmd_line_tok)
 * 	incrementing the size according to the amount of tokens found.
 *  ft_realloc will copy the tokens already in lexers cmd_line_tok to
 *  the new array and free's the old array.
 *  the token to be added, will be added at the end of the array
 * @param l struct lexer containg amount of tokens found and an array
 *  of tokens
 * @param token token to be appended to the tokens array cmd_line_tok
 *  inside the lexer struct
 */
static int	append_token_to_lexer(t_Lexer *l, t_Token token)
{
	size_t	count;

	count = l->tokens_count;
	if (count == 0)
		l->cmd_line_tok = ft_realloc(l->cmd_line_tok, 0, sizeof(t_Token));
	else
		l->cmd_line_tok = ft_realloc(
				l->cmd_line_tok, sizeof(t_Token)
				* (count - 1), sizeof(t_Token) * count);
	if (l->cmd_line_tok == NULL)
		return (-1);
	l->cmd_line_tok[l->tokens_count - 1] = token;
	return (0);
}

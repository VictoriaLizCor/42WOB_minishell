/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handle_tokens.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranero <mgranero@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 16:47:44 by mgranero          #+#    #+#             */
/*   Updated: 2023/08/06 20:13:56 by mgranero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/**
 * @brief handles tokens of type word
 *
 * @param l struct lexer
 * @param token struct token
 */
void	ft_token_word(t_Lexer *l, t_Token *token)
{
	int	count_chars;
	int	init_idx;

	count_chars = 0;
	init_idx = l->iter;
	token->token_kind = TOKEN_WORD;
	l->tokens_count = l->tokens_count + 1;
	token->id = l->tokens_count;
	while (l->iter < l->cmd_line_len && l->cmd_line[l->iter] != ' '
		&& l->cmd_line[l->iter] != '\n' && l->cmd_line[l->iter] != '|'
		&& l->cmd_line[l->iter] != '<' && l->cmd_line[l->iter] != '>'
		&& l->cmd_line[l->iter] != ASCII_SINGLE_QUOTE
		&& l->cmd_line[l->iter] != ASCII_DOUBLE_QUOTE)
	{
		token->text_len += 1;
		count_chars++;
		l->iter = l->iter + 1;
	}
	token->text = ft_substr(l->cmd_line, init_idx, count_chars + 1);
	if (token->text == NULL)
		return ;
	token->text[count_chars] = '\0';
}

// //move to another file
// int	ft_token_assignment_word(t_Lexer *l, t_Token *token)
// {
// 	int	count_chars;

// 	count_chars = 0;
// 	token->token_kind = TOKEN_ASSIGNMENT_WORD;
// 	while (l->cmd_line[l->iter] != ' ' && l->cmd_line[l->iter] != '\n'
// 		&& l->cmd_line[l->iter] != '\0')
// 	{
// 		token->text_len += 1;
// 		count_chars++;
// 		l->iter = l->iter + 1;
// 	}
// 	return (count_chars);
// }

// /**
//  * @brief checks if the analyzed name is actually a word
//  *
//  * @param l
//  * @return int
//  */
// int	is_it_a_word(t_Lexer *l)
// {
// 	if (ft_isalnum(l->cmd_line[l->iter]) != 1 && l->cmd_line[l->iter] != '_'
// 		&& l->cmd_line[l->iter] != '=' && l->cmd_line[l->iter] != ' '
// 		&& l->cmd_line[l->iter] != '\n' && l->cmd_line[l->iter] != '\0')
// 		return (1);
// 	return (0);
// }

// /**
//  * @brief loops chars collecting text for TOKEN_NAME and checking
//  *  if it is not a TOKEN_WORD
//  *
//  * @param l
//  * @param token
//  * @param init_idx
//  * @return int
//  */
// int	get_token_name_text(t_Lexer *l, t_Token *token, int init_idx)
// {
// 	int	count_chars;

// 	count_chars = 0;
// 	while ((ft_isalnum(l->cmd_line[l->iter]) == 1
// 			|| l->cmd_line[l->iter] == '_' || l->cmd_line[l->iter] == '=')
// 		&& l->iter < l->cmd_line_len)
// 	{
// 		if (l->cmd_line[l->iter] == '=')
// 		{
// 			count_chars += ft_token_assignment_word(l, token);
// 			return (count_chars);
// 		}
// 		token->text_len += 1;
// 		count_chars++;
// 		l->iter = l->iter + 1;
// 		if (is_it_a_word(l) == 1)
// 		{
// 			l->iter = init_idx;
// 			l->tokens_count = l->tokens_count - 1;
// 			ft_token_word(l, token);
// 			return (-1);
// 		}
// 	}
// 	return (count_chars);
// }

// /**
//  * @brief handles the token name
//  *
//  * @param l struct lexer
//  * @param token  struct token
//  */
// void	ft_token_name(t_Lexer *l, t_Token *token)
// {
// 	int	count_chars;
// 	int	init_idx;

// 	init_idx = l->iter;
// 	token->token_kind = TOKEN_NAME;
// 	l->tokens_count = l->tokens_count + 1;
// 	token->id = l->tokens_count;
// 	count_chars = get_token_name_text(l, token, init_idx);
// 	if (count_chars == -1)
// 		return ;
// 	token->text = ft_substr(l->cmd_line, init_idx, count_chars + 1);
// 	if (token->text == NULL)
// 		return (set_lexer_error_return(l));
// 	token->text[count_chars] = '\0';
// }

/**
 * @brief handles tokens of single and double quotes, wraping the text
 *  in between the quotes in the token text and indenfies if it is
 *  a double or single quote token.
 *
 * @param l struct lexer
 * @param token struct token
 */
void	ft_token_quotes(t_Lexer *l, t_Token *token)
{
	int		idx;

	idx = ft_get_index_of_char(l->cmd_line + l->iter + 1, l->cmd_line[l->iter]);
	if (idx == -1)
	{
		ft_putstr_fd("Error: no handle for unclosed quotes\n", STDERR_FILENO);
		return (set_lexer_error_return(l));
	}
	else
	{
		if (l->cmd_line[l->iter] == ASCII_SINGLE_QUOTE)
			token->token_kind = TOKEN_SINGLE_QUOTED_STR;
		else
			token->token_kind = TOKEN_DOUBLE_QUOTED_STR;
		l->tokens_count = l->tokens_count + 1;
		token->id = l->tokens_count;
		token->text = ft_substr(l->cmd_line, l->iter + 1, idx);
		if (token->text == NULL)
			return (set_lexer_error_return(l));
		token->text_len = idx + 1;
		l->iter = l->iter + idx + 2;
	}
}

/**
 * @brief handles tokens double great and double less
 *
 * @param l struct lexer
 * @param token struct token
 */
void	ft_token_dgreat_dless(t_Lexer *l, t_Token *token)
{
	if (l->cmd_line[l->iter] == '>' && l->cmd_line[l->iter + 1] == '>')
		token->token_kind = TOKEN_DGREAT;
	else if (l->cmd_line[l->iter] == '<' && l->cmd_line[l->iter + 1] == '<')
		token->token_kind = TOKEN_DLESS;
	token->text_len = 2;
	token->text = ft_calloc(3, sizeof(char));
	if (token->text == NULL)
		return (set_lexer_error_return(l));
	token->text[0] = l->cmd_line[l->iter];
	token->text[1] = l->cmd_line[l->iter + 1];
	token->text[2] = '\0';
	l->iter = l->iter + 2;
	l->tokens_count = l->tokens_count + 1;
	token->id = l->tokens_count;
}

/**
 * @brief handles tokens of that are included in the literal tokens
 *  lists like |, <, > as there presence represents a direct token.
 *
 * @param l  struct lexer
 * @param token struct token
 * @param tok_lit struct token_lit with token literals data to be compared
 * @param ret index of the found match in tok_lit
 */
void	ft_token_lit(t_Lexer *l, t_Token *token, t_Toklit	tok_lit, int ret)
{
	token->token_kind = tok_lit.token_kind_literals[ret];
	token->text_len = 1;
	token->text = ft_calloc(2, sizeof(char));
	if (token->text == NULL)
		return (set_lexer_error_return(l));
	token->text[0] = tok_lit.char_literals[ret];
	token->text[1] = '\0';
	l->iter = l->iter + 1;
	l->tokens_count = l->tokens_count + 1;
	token->id = l->tokens_count;
}

int	change_from_name_to_word(t_Lexer *l, t_Token *token, int init_idx)
{
	l->iter = init_idx;
	l->tokens_count = l->tokens_count - 1;
	ft_token_word(l, token);
	return (-1);
}

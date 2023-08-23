/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handle_token_name.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranero <mgranero@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 14:36:36 by mgranero          #+#    #+#             */
/*   Updated: 2023/08/06 20:14:01 by mgranero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	get_token_name_text(t_Lexer *l, t_Token *token, int init_idx);
static int	ft_token_assignment_word(t_Lexer *l, t_Token *token);
static int	is_it_a_word(t_Lexer *l);
static int	ft_handle_assign_quotes(t_Lexer *l, t_Token *token);

/**
 * @brief handles the token name
 *
 * @param l struct lexer
 * @param token  struct token
 */
void	ft_token_name(t_Lexer *l, t_Token *token)
{
	int	count_chars;
	int	init_idx;

	init_idx = l->iter;
	token->token_kind = TOKEN_NAME;
	l->tokens_count = l->tokens_count + 1;
	token->id = l->tokens_count;
	count_chars = get_token_name_text(l, token, init_idx);
	if (count_chars == -1)
		return ;
	token->text = ft_substr(l->cmd_line, init_idx, count_chars + 1);
	if (token->text == NULL)
		return (set_lexer_error_return(l));
	token->text[count_chars] = '\0';
}

static int	ft_handle_assign_quotes(t_Lexer *l, t_Token *token)
{
	int		idx;
	int		count_chars;

	idx = ft_get_index_of_char(l->cmd_line + l->iter + 1, l->cmd_line[l->iter]);
	if (idx != -1)
	{
		token->text_len += idx + 2;
		count_chars = idx + 2;
		l->iter += idx + 2;
	}
	else
	{
		ft_putstr_fd("Error: no handle for unclosed quotes\n", STDERR_FILENO);
		if (l->tokens_count > 0)
			l->tokens_count = l->tokens_count - 1;
		l->error = 1;
		return (-1);
	}
	return (count_chars);
}

//move to another file
static int	ft_token_assignment_word(t_Lexer *l, t_Token *token)
{
	int		count_chars;
	int		ret;

	count_chars = 0;
	token->token_kind = TOKEN_ASSIGNMENT_WORD;
	while (l->cmd_line[l->iter] != ' ' && l->cmd_line[l->iter] != '\n'
		&& l->cmd_line[l->iter] != '\0' && l->cmd_line[l->iter] != '|')
	{
		if (l->cmd_line[l->iter] == ASCII_SINGLE_QUOTE
			|| l->cmd_line[l->iter] == ASCII_DOUBLE_QUOTE)
		{
			ret = ft_handle_assign_quotes(l, token);
			if (ret == -1)
				return (-1);
			count_chars += ret;
		}
		else
		{
			token->text_len += 1;
			count_chars++;
			l->iter = l->iter + 1;
		}
	}
	return (count_chars);
}

/**
 * @brief checks if the analyzed name is actually a word
 *
 * @param l
 * @return int
 */
static int	is_it_a_word(t_Lexer *l)
{
	if (ft_isalnum(l->cmd_line[l->iter]) != 1 && l->cmd_line[l->iter] != '_'
		&& l->cmd_line[l->iter] != '=' && l->cmd_line[l->iter] != ' '
		&& l->cmd_line[l->iter] != '\n' && l->cmd_line[l->iter] != '\0')
		return (1);
	return (0);
}

/**
 * @brief loops chars collecting text for TOKEN_NAME and checking
 *  if it is not a TOKEN_WORD
 *
 * @param l
 * @param token
 * @param init_idx
 * @return int
 */
static int	get_token_name_text(t_Lexer *l, t_Token *token, int init_idx)
{
	int	count_chars;
	int	ret;

	count_chars = 0;
	while ((ft_isalnum(l->cmd_line[l->iter]) == 1
			|| l->cmd_line[l->iter] == '_' || l->cmd_line[l->iter] == '=')
		&& l->iter < l->cmd_line_len && l->cmd_line[l->iter] != '|'
		&& l->cmd_line[l->iter] != ASCII_SINGLE_QUOTE
		&& l->cmd_line[l->iter] != ASCII_DOUBLE_QUOTE)
	{
		if (l->cmd_line[l->iter] == '=')
		{
			ret = ft_token_assignment_word(l, token);
			if (ret == -1)
				return (-1);
			return (count_chars + ret);
		}
		token->text_len += 1;
		count_chars++;
		l->iter = l->iter + 1;
		if (is_it_a_word(l) == 1)
			return (change_from_name_to_word(l, token, init_idx));
	}
	return (count_chars);
}

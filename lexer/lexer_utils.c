/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranero <mgranero@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 08:42:45 by mgranero          #+#    #+#             */
/*   Updated: 2023/07/07 14:01:26 by mgranero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static char	*get_token_name_part2(t_Token token);

/**
 * @brief prints lexer token text, id and kind
 *
 * @param lexer created lexer with tokens
 */
void	print_lexer_tokens(t_Lexer	*lexer)
{
	size_t	i;

	i = 0;
	printf("\n* * * * * Lexical Analyses Output * * * * *\n");
	if (lexer == NULL)
		printf("passed a NULL lexer\n");
	while (i < lexer->tokens_count)
	{
		printf("\n%s%s$", "\x1B[31m", lexer->cmd_line_tok[i].text);
		printf("%s:id%d ", "\x1B[34m", lexer->cmd_line_tok[i].id);
		printf("(%s)%s\n", get_token_name(lexer->cmd_line_tok[i]), "\x1B[37m");
		i++;
	}
	printf("\n* * * * * * * * * *\n\n");
}

/**
 * @brief function used for debugging, it will return
 *  a string with the token idenfication
 * @param token token which name must be returned
 * @return char* name identifing the token
 */
char	*get_token_name(t_Token token)
{
	if (token.token_kind == TOKEN_END)
		return ("end");
	else if (token.token_kind == TOKEN_WORD)
		return ("word");
	else if (token.token_kind == TOKEN_NAME)
		return ("name");
	else if (token.token_kind == TOKEN_PIPE)
		return ("pipe");
	else if (token.token_kind == TOKEN_SINGLE_QUOTED_STR)
		return ("single quoted string");
	else if (token.token_kind == TOKEN_DOUBLE_QUOTED_STR)
		return ("double quoted string");
	else if (token.token_kind == TOKEN_NO_SPACE)
		return ("no space");
	return (get_token_name_part2(token));
}

/**
 * @brief continuation of the get_token_name
 *
 * @param token
 * @return char*
 */
static char	*get_token_name_part2(t_Token token)
{
	if (token.token_kind == TOKEN_LESS)
		return ("operator less");
	else if (token.token_kind == TOKEN_GREAT)
		return ("operator great");
	else if (token.token_kind == TOKEN_DGREAT)
		return ("operator double great");
	else if (token.token_kind == TOKEN_DLESS)
		return ("operator double less");
	else if (token.token_kind == TOKEN_ASSIGNMENT_WORD)
		return ("assignment word");
	return ("Error: token name not found");
}

/**
 * @brief Set the lexer error and returns function
 *
 * @param l
 */
void	set_lexer_error_return(t_Lexer *l)
{
	l->error = 1;
}

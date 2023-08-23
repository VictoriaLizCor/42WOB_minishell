/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranero <mgranero@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:06:37 by mgranero          #+#    #+#             */
/*   Updated: 2023/08/06 20:13:38 by mgranero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "../libft/libft.h"

# ifndef DEBUG_LEXER
#  define DEBUG_LEXER 0
# endif

# define ASCII_SINGLE_QUOTE	39
# define ASCII_DOUBLE_QUOTE	34

typedef enum kind{
	TOKEN_END,
	TOKEN_WORD,
	TOKEN_NAME,
	TOKEN_ASSIGNMENT_WORD,
	TOKEN_PIPE,
	TOKEN_SINGLE_QUOTED_STR,
	TOKEN_DOUBLE_QUOTED_STR,
	TOKEN_NO_SPACE,
	TOKEN_LESS,
	TOKEN_GREAT,
	TOKEN_DLESS,
	TOKEN_DGREAT,
	TOKEN_INVALID,
	TOKEN_IGNORE,
	NB_OF_TOKEN_KINDS,
}	t_Token_kind;

typedef struct s_token {
	t_Token_kind	token_kind;
	char			*text;
	size_t			text_len;
	int				id;
}	t_Token;

typedef struct s_lexer{
	char		*cmd_line;
	size_t		cmd_line_len;
	size_t		iter;
	size_t		tokens_count;
	t_Token		*cmd_line_tok;
	int			error;
}	t_Lexer;

typedef struct s_toklit{
	char	char_literals[14];
	int		token_kind_literals[14];
	int		size_char_literals;
}	t_Toklit;

t_Lexer	lexer(char *command_line);
void	free_lexer(t_Lexer *l);
t_Token	lexer_get_tokens(t_Lexer *l, t_Toklit	tok_lit);
void	ft_token_name(t_Lexer *l, t_Token *token);
void	ft_token_word(t_Lexer *l, t_Token *token);
void	ft_token_quotes(t_Lexer *l, t_Token *token);
void	ft_token_dgreat_dless(t_Lexer *l, t_Token *token);
void	ft_token_lit(t_Lexer *l, t_Token *token, t_Toklit	tok_lit, int ret);
void	print_lexer_tokens(t_Lexer	*lexer);
char	*get_token_name(t_Token token);
void	set_lexer_error_return(t_Lexer *l);
int		change_from_name_to_word(t_Lexer *l, t_Token *token, int init_idx);

#endif
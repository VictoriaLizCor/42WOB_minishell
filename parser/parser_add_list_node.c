/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_add_list_node.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranero <mgranero@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 21:43:52 by mgranero          #+#    #+#             */
/*   Updated: 2023/08/04 17:19:14 by mgranero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	fill_list_data(t_Lexer *lex, t_parser *p);
static int	get_cmd_exec(t_Lexer *lex, t_parser *p);
static int	get_file_data(t_Lexer *lex, t_parser *p);
static void	get_file_data_helper(t_parser *p, t_Token_kind tok, int type);

int	add_list_node(t_Lexer *lex, t_parser *p)
{
	if (add_new_empty_node(p) == -1)
		return (-1);
	if (fill_list_data(lex, p) == -1)
		return (-1);
	return (0);
}

static int	fill_list_data(t_Lexer *lex, t_parser *p)
{
	p->list_exec->paths = get_env_key_value("PATH", p->env_heap);
	p->list_exec->cmd.exe = (char **)ft_calloc((p->size_cmd_exe + 1),
			sizeof(char *));
	p->list_exec->cmd.token_kind = (t_Token_kind *)ft_calloc(
			(p->size_cmd_exe + 1), sizeof(t_Token_kind *));
	if (p->list_exec->cmd.exe == NULL || p->list_exec->cmd.token_kind == NULL)
	{
		ft_putstr_fd("Error: calloc in add_list_node\n", STDERR_FILENO);
		return (-1);
	}
	if (get_cmd_exec(lex, p) == -1 || get_file_data(lex, p) == -1)
		return (-1);
	p->size_cmd_exe = 0;
	p->nb_of_elem = 0;
	p->list_exec->pipex_status[0] = -1;
	p->list_exec->pipex_status[1] = -1;
	p->list_exec->pipex[0] = -1;
	p->list_exec->pipex[1] = -1;
	p->list_exec->child_pid = -255;
	if (p->idx_pos0 > 0
		&& lex->cmd_line_tok[p->idx_pos0 - 1].token_kind == TOKEN_PIPE)
		p->list_exec->is_pipe = 1;
	return (0);
}

static int	get_cmd_exec(t_Lexer *lex, t_parser *p)
{
	int		i;
	size_t	j;

	i = 0;
	j = p->idx_pos0 ;
	p->list_exec->cmd.status = -1;
	while (j < p->idx_pos0 + p->nb_of_elem)
	{
		p->list_exec->cmd.exe[i] = ft_substr(lex->cmd_line_tok[j].text, 0,
				lex->cmd_line_tok[j].text_len + 1);
		if (p->list_exec->cmd.exe[i] == NULL)
			return (put_error_str("Error: memory alloc in get_cmd_exec\n"));
		p->list_exec->cmd.token_kind[i] = lex->cmd_line_tok[j].token_kind;
		i++;
		j++;
	}
	return (0);
}

static int	get_file_data(t_Lexer *lex, t_parser *p)
{
	int				i;
	t_Token_kind	tok;

	i = p->idx_pos0;
	tok = lex->cmd_line_tok[i].token_kind;
	initialize_file_struct(p);
	if (tok == TOKEN_GREAT || tok == TOKEN_DGREAT \
	|| tok == TOKEN_LESS || tok == TOKEN_DLESS)
	{
		if (tok == TOKEN_GREAT || tok == TOKEN_DGREAT)
			get_file_data_helper(p, tok, 1);
		else
			get_file_data_helper(p, tok, 0);
		i++;
		p->list_exec->file[p->list_exec->f_inout].name = (char *)ft_calloc(
				lex->cmd_line_tok[i].text_len + 1, sizeof(char));
		if (p->list_exec->file[p->list_exec->f_inout].name == NULL)
			return (put_error_str("Error: memory alloc in get_file_data\n"));
		if (p->list_exec->f_inout != -1)
		{
			ft_strlcpy(p->list_exec->file[p->list_exec->f_inout].name,
				lex->cmd_line_tok[i].text, lex->cmd_line_tok[i].text_len + 1);
		}
	}
	return (0);
}

static void	get_file_data_helper(t_parser *p, t_Token_kind tok, int type)
{
	if (type == 1)
	{
		p->list_exec->f_inout = 1;
		if (tok == TOKEN_GREAT)
			p->list_exec->file[p->list_exec->f_inout].oflag = \
				O_CREAT | O_WRONLY | O_TRUNC;
		else if (tok == TOKEN_DGREAT)
			p->list_exec->file[p->list_exec->f_inout].oflag = O_CREAT
				| O_WRONLY | O_APPEND;
	}
	else if (type == 0)
	{
		p->list_exec->f_inout = 0;
		if (tok == TOKEN_LESS)
		{
			p->list_exec->file[p->list_exec->f_inout].oflag = O_RDONLY;
		}
		if (tok == TOKEN_DLESS)
		{
			p->list_exec->file[p->list_exec->f_inout].fd = 0;
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranero <mgranero@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:30:28 by mgranero          #+#    #+#             */
/*   Updated: 2023/08/15 22:08:53 by mgranero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../libft/libft.h"
# include "../shell_subsys/environment_handling.h"
# include "../lexer/lexer.h"
# include <stdio.h>

# ifndef DEBUG_PARSER
#  define DEBUG_PARSER 0
# endif

typedef struct s_cmd
{
	char			*str_in;
	char			**exe;
	char			*path;
	char			*error_str;
	int				status;
	t_Token_kind	*token_kind;
}	t_cmd;

typedef struct s_file
{
	char	*name;
	int		fd;
	int		oflag;
}	t_file;

typedef struct s_pipex
{
	pid_t			child_pid;
	int				idx;
	int				pipex[2];
	char			*paths;
	t_cmd			cmd;
	t_file			file[2];
	int				f_inout;
	int				pipex_status[2];
	struct stat		info_pipex[2];
	int				is_pipe;
	struct s_pipex	*head;
	struct s_pipex	*previous;
	struct s_pipex	*next;
	int				last_stat;
	t_env			**ptr_env_heap;
	int				error;
	int				fd_stdin_bkup;
}	t_pipex;

typedef struct s_parser{
	size_t		i;
	int			pos_in_cmd;
	size_t		idx_pos0;
	size_t		size_cmd_exe;
	size_t		nb_of_elem;
	int			count_cmd;
	t_env		*env_heap;
	t_pipex		*list_exec;
}	t_parser;

t_pipex	*parser(t_Lexer *lex, t_env *env_heap, int scase);
int		chk_redirect(t_Lexer *lex, t_parser *p);
int		chk_redirect_dless(t_Lexer *lex, t_parser *p);
int		chk_redirect_terminate_previous(t_Lexer *lex, t_parser *p);
int		add_cmd(t_Lexer *lex, t_parser *p);
int		add_list_node(t_Lexer *lex, t_parser *p);
int		add_new_empty_node(t_parser *p);
void	free_list_pipex(t_pipex *l_pipex);
void	print_pipex_list(t_pipex *l_pipex);
int		put_error_str(char *str);
void	initialize_file_struct(t_parser *p);

# define CNRM  "\x1B[0m"
# define CRED  "\x1B[31m"
# define CGRN  "\x1B[32m"
# define CYEL  "\x1B[33m"
# define CBLU  "\x1B[34m"
# define CMAG  "\x1B[35m"
# define CCYN  "\x1B[36m"
# define CWHT  "\x1B[37m"

#endif
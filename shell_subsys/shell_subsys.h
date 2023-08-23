/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_subsys.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranero <mgranero@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:30:28 by mgranero          #+#    #+#             */
/*   Updated: 2023/08/17 16:02:15 by mgranero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_SUBSYS_H
# define SHELL_SUBSYS_H

# include "../parser/parser.h"
# include "../lexer/lexer.h"
# include "environment_handling.h"
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include "../pipex_repo/include/pipex.h"
# include <signal.h>
# include <unistd.h>
# include <termios.h>

# ifndef DEBUG_SUB
#  define DEBUG_SUB 0
# endif

# define CNRM  "\x1B[0m"
# define CRED  "\x1B[31m"
# define CGRN  "\x1B[32m"
# define CYEL  "\x1B[33m"
# define CBLU  "\x1B[34m"
# define CMAG  "\x1B[35m"
# define CCYN  "\x1B[36m"
# define CWHT  "\x1B[37m"

# define ASCII_HORIZ_TAB 9

typedef struct term{
	struct termios	orig_term_in;
	struct termios	orig_term_out;
	struct termios	orig_term_err;
}	t_term;

typedef struct t_hdoc{
	char	*key;
	int		idx;
	int		start;
	int		is_itoa;
}	t_hdoc;

typedef struct s_shell
{
	t_env	*env_heap;
	int		last_exec;
}	t_shell;

typedef struct s_sig
{
	pid_t	child_pid;
	int		idx;
}	t_signals;

extern t_signals	g_sig;

int			prompt_readline(t_env *env_heap);
int			check_exit(char *buff_heap);
int			ft_setup_sighandler(void);
void		ft_signal_handler(int signum);
void		ft_signal_handler_non_interact(int signum);
int			ft_setup_sighandler_non_interact(void);
int			ft_setup_sighandler_heredoc(void);
int			ft_setup_sighandler_parent(void);
void		ft_signal_handlerheredoc_parent(int signum);
void		ft_signal_handlerheredoc_child(int signum);
char		*rescan_assign(char *value, t_pipex *l_pipex, t_Lexer lexer_tmp);
void		executor(t_pipex *l_pipex);
t_env		*print_err_ret_0(char *str);
int			ft_env(t_env *env_heap, int fd);
int			ft_export(t_pipex *l_pipex);
char		*join_new_value(t_pipex *ptr);
t_env		*ft_export_basic(char *key, char *value, t_env *env_heap);
int			export_no_args_print(t_env	*new_env);
char		*print_err_null(char *str);
int			print_err_ret1(char *str);
int			ft_unset(t_pipex *l_pipex);
int			ft_unset_basic(char *key, t_env **ptr_env_heap);
int			search_builtin(t_pipex *ptr);
void		update_nodes_env(t_pipex *l_pipex, t_env *new_env);
int			get_return_status(t_pipex *l_pipex);
int			ft_cd(char *new_dir, t_env **ptr_env_heap);
int			ft_echo(t_cmd *cmd);
int			ft_pwd(int fd);
int			ft_heredoc(t_pipex *l_pipex);
char		*get_new_line(char *line, t_hdoc *hdoc, int size_line,
				int size_key);
void		set_prompt_txt(char *prompt, char *msg);
int			str_compare(char *str1, char *str2);
t_env		*setup_environment(char *env[]);
void		free_env_heap(t_env *env_heap);
int			env_var_extension(t_pipex *l_pipex);
char		*subst_env_var(char *line, t_pipex *l_pipex);
void		rl_clear_history(void);
void		launcher(char *buffer, t_shell *shell_var,
				t_Lexer lex_heap, t_pipex *l_pipex);
int			search_expand_env_vars(char **doc, int size, t_pipex *l_pipex);
char		*subst_env_var_helper(char *line, t_pipex *l_pipex, t_hdoc *hdoc);
t_term		get_term_configs(void);
void		set_term_configs(t_term term);
int			free_buff_ret_1(char *buff);
#endif
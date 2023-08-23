/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranero <mgranero@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:31:11 by mgranero          #+#    #+#             */
/*   Updated: 2023/08/18 10:53:47 by mgranero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		print_intro(void);
static int		no_prompt(char *command, t_env *env_heap);

t_signals	g_sig;

int	main(int argc, char *argv[], char *env[])
{
	t_env	*env_heap;

	if (argc == 2 && str_compare(argv[1], "-h") == 0)
	{
		printf("\n* * * * * Minishell Help * * * * * * * * * * * *\n");
		printf("   ./minishell: for interactive mode\n");
		printf("   or add:\n     -h: for Help\n     -c \"command\":"
			" to pass a single command line\n");
		printf("* * * * * * * * * * * * * * * * * * * * * * * * *\n\n");
		return (0);
	}
	env_heap = setup_environment(env);
	if (argc == 3 && str_compare(argv[1], "-c") == 0)
		return (no_prompt(argv[2], env_heap));
	else if (argc > 2)
	{
		printf("Incorrect input, call ./minishell -h for help\n");
		free_env_heap(env_heap);
		return (1);
	}
	ft_setup_sighandler();
	print_intro();
	return (prompt_readline(env_heap));
	// return (0);
}

static int	no_prompt(char *command, t_env *env_heap)
{
	t_Lexer	lex_heap;
	t_pipex	l_pipex;
	int		ret;
	t_shell	shell_var;

	ft_memset(&lex_heap, 0, sizeof(t_Lexer));
	ft_memset(&l_pipex, 0, sizeof(t_pipex));
	ret = 0;
	shell_var.env_heap = env_heap;
	launcher(command, &shell_var, lex_heap, &l_pipex);
	if (shell_var.env_heap == NULL)
		ret = 1;
	free_env_heap(shell_var.env_heap);
	return (ret);
}

static	void	print_intro(void)
{
	printf("\n%s     . . . . . .    \n  ..         42..", CCYN);
	printf("\n ..             ..\n");
	printf(".     .. ..      ..\n..   .      .    ..\n");
	printf("..   .   .   .   ..\n");
	printf(" ..    ..    .   ..\n  ..        .    .\n");
	printf("    .. .. ..    ..\n\n%s", CNRM);
	printf("%s oh my Minishell!\n ---------------%s\n", CGRN, CNRM);
}

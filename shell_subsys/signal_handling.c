/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranero <mgranero@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:59:20 by mgranero          #+#    #+#             */
/*   Updated: 2023/08/17 16:31:40 by mgranero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_subsys.h"

static void	handle_sigquit(void);

/**
 * @brief Setups and configuration of signal handlers.
 *
 * Function responsible for the setup of the signal handler.
 * This means configuring the struct sigaction by first setting an
 * empty mask and adding only the 1 signals of interest (SIGINT).
 * The handler functions for these signals
 * will be also set.
 */

int	ft_setup_sighandler(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sa.sa_flags = 0;
	sa.sa_handler = &ft_signal_handler;
	signal(SIGQUIT, SIG_IGN);
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		ft_putstr_fd("Error: ft_setup_sighandler\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	ft_setup_sighandler_non_interact(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sigaddset(&sa.sa_mask, SIGQUIT);
	sa.sa_flags = 0;
	sa.sa_handler = &ft_signal_handler_non_interact;
	if (sigaction(SIGINT, &sa, NULL) == -1
		|| sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		ft_putstr_fd("Error: ft_setup_sighandler\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}

/**
 * functions: ft_signal_handler
 * if a signal SIGINT (ctrl+c) is received ft_signal_handler
 * is called.
 * function will get the sender of the pid if it comes from another process
 * and writes to pid_sig_sender in the global variable g_sig.
 * if SIGINT is received a new line in the prompt is created
 * variable is_quit will be set to 1. Making the loop in prompt_readline
 * stop.
*/

void	ft_signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		if (g_sig.idx == 0)
		{
			ft_putchar('\n');
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
	}
}

void	ft_signal_handler_non_interact(int signum)
{
	if (signum == SIGINT)
	{
		if (g_sig.child_pid != -1)
		{
			ft_putstr_fd("\n", 2);
			kill(g_sig.child_pid, SIGTERM);
			waitpid(g_sig.child_pid, NULL, 0);
		}
		if (g_sig.idx != 0)
			exit(1);
	}
	else if (signum == SIGQUIT)
		handle_sigquit();
	if (g_sig.idx != 0)
		exit(1);
}

static void	handle_sigquit(void)
{
	if (g_sig.child_pid != -1)
	{
		if (g_sig.idx == 0)
			ft_putstr_fd("Quit: 3\n", 2);
		kill(g_sig.child_pid, SIGTERM);
		waitpid(g_sig.child_pid, NULL, 0);
	}
	if (g_sig.idx != 0)
		exit(1);
}

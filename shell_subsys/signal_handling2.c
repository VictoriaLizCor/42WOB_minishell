/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranero <mgranero@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 13:37:15 by mgranero          #+#    #+#             */
/*   Updated: 2023/08/17 16:32:23 by mgranero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_subsys.h"

int	ft_setup_sighandler_heredoc(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sigaddset(&sa.sa_mask, SIGTERM);
	sa.sa_flags = 0;
	sa.sa_handler = &ft_signal_handlerheredoc_child;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_DFL);
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		ft_putstr_fd("Error: ft_setup_sighandler\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	ft_setup_sighandler_parent(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sigaddset(&sa.sa_mask, SIGQUIT);
	sa.sa_flags = 0;
	sa.sa_handler = &ft_signal_handlerheredoc_parent;
	signal(SIGQUIT, SIG_IGN);
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		ft_putstr_fd("Error: ft_setup_sighandler\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}

void	ft_signal_handlerheredoc_parent(int signum)
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
			exit (1);
	}
}

void	ft_signal_handlerheredoc_child(int signum)
{
	if (signum == SIGINT)
	{
		if (g_sig.child_pid != -1)
		{
			kill(g_sig.child_pid, SIGTERM);
			waitpid(g_sig.child_pid, NULL, 0);
		}
		if (g_sig.idx != 0)
			exit (1);
	}
}

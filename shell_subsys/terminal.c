/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranero <mgranero@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 13:53:23 by mgranero          #+#    #+#             */
/*   Updated: 2023/08/14 14:27:02 by mgranero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_subsys.h"

t_term	get_term_configs(void)
{
	t_term	term;

	tcgetattr(STDIN_FILENO, &term.orig_term_in);
	tcgetattr(STDOUT_FILENO, &term.orig_term_out);
	tcgetattr(STDERR_FILENO, &term.orig_term_err);
	return (term);
}

void	set_term_configs(t_term term)
{
	if (!(term.orig_term_in.c_oflag & ONLCR))
		term.orig_term_in.c_oflag |= ONLCR;
	tcsetattr(STDIN_FILENO, TCSANOW, &term.orig_term_in);
	tcsetattr(STDOUT_FILENO, TCSANOW, &term.orig_term_out);
	tcsetattr(STDERR_FILENO, TCSANOW, &term.orig_term_err);
}

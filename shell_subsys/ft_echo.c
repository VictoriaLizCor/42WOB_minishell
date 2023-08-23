/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranero <mgranero@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 10:47:24 by mgranero          #+#    #+#             */
/*   Updated: 2023/08/04 17:23:32 by mgranero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_subsys.h"

/**
 * @brief
 * The echo utility writes any specified operands, separated by single
 * blank (‘ ’)characters and followed by a newline (‘\n’) character, to the
 * standard output.
 *
 *  The following option is available:
 *
 *  -n     Do not print the trailing newline character.  This may also
 *         be achieved by appending ‘\c’ to the end of the string, as
 *         is done by iBCS2 compatible systems.  Note that this option
 *         as well as the effect of ‘\c’ are
 *         implementation-defined in IEEE Std 1003.1-2001 (“POSIX.1”) as
 *         amended by Cor. 1-2002.  Applications aiming for maximum
 *         portability are strongly
 *         encouraged to use printf(1) to suppress the newline character.
 *
 * Some shells may provide a builtin echo command which is similar or
 * identical to this utility.  Most notably, the builtin echo in sh(1)
 * does not accept the -n option.  Consult the builtin(1) manual page.
 * The echo utility exits 0 on success, and >0 if an error occurs.
 *
 * @param str string to be printed
 * @param n_option pass 0 to use echo without options and pass 1 to
 *    use echo -n option
 * @return returns 0 on success, and >0 if an error occurs.
 */
int	ft_echo(t_cmd *cmd)
{
	int	i;
	int	n_option;

	if (cmd->exe[1] != NULL && cmd->exe[1][0] != '\0'
		&& str_compare(cmd->exe[1], "-n") == 0)
		n_option = 1;
	else
		n_option = 0;
	if (n_option == 0)
		i = 1;
	else
		i = 2;
	while (cmd->exe[i] != NULL)
	{
		printf("%s", cmd->exe[i]);
		i++;
		if (cmd->exe[i] != NULL && cmd->exe[i][0] != '\0')
			printf(" ");
	}
	if (n_option == 0)
		printf("\n");
	return (0);
}

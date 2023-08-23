/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranero <mgranero@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 20:03:22 by mgranero          #+#    #+#             */
/*   Updated: 2023/07/09 15:08:45 by mgranero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_subsys.h"

/***
 * The pwd command writes to standard output the full path name of your
 * current directory (from the root directory). All directories are separated
 * by a / (slash). The root directory is represented by the first /, and the
 * last directory named is your current directory.
*/

/**
 * @brief writes current path to an fd output
 * The pwd command writes to standard output the full path name of your
 * current directory (from the root directory). All directories are separated
 * by a / (slash). The root directory is represented by the first /, and the
 * last directory named is your current directory.
 * @param fd files descriptor to write the output
 * @return int if no error returns 0 otherwise returns 1
 */
int	ft_pwd(int fd)
{
	char	cwd[256];
	char	*ret;

	ret = getcwd(cwd, sizeof(cwd));
	if (ret == NULL)
		return (1);
	ft_putstr_fd(cwd, fd);
	ft_putchar_fd('\n', fd);
	return (0);
}

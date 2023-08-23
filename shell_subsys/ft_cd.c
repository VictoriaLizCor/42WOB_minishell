/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranero <mgranero@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 20:18:24 by mgranero          #+#    #+#             */
/*   Updated: 2023/08/09 21:15:03 by mgranero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_subsys.h"

static int	update_env_pwd(t_env **ptr_env_heap);
static void	ft_get_old_pwd(t_env **ptr_env_heap, char *old_pwd);

/**
 * @brief
 * The command cd directory changes the working directory of the current
 * shell execution environment (see sh) to directory. If you specify
 * directory as an absolute path name, beginning with /, this is the target
 * directory. cd assumes the target directory to be the name just as you
 * specified it. If you specify directory as a relative path name, cd assumes
 * it to be relative to the current working directory.
 * The shell keeps the name of the working directory in the variable PWD.
 * The cd command scans the current value of PWD and replaces the first
 * occurrence of the string old with the string new.
 *
 * The shell displays the resulting value of PWD, and it becomes
 * the new working directory.
 *
 * Calling cd without arguments sets the working directory to the value
 * of the HOME environment variable, if the variable exists. If there is
 * no HOME variable, cd does not change the working directory.
 *
 *
 * The single dot represents the current directory
 *
 * @param new_dir new directory to be set
 * @param env_heap environment variable where PWD and OLDPWD
 *  will be update if the request succeed
 * @return returns the updated env_heap or NULL in case of error
 */

int	ft_cd(char *new_dir, t_env **ptr_env_heap)
{
	if (new_dir == NULL)
	{
		new_dir = get_env_key_value("HOME", *(ptr_env_heap));
		if (new_dir == NULL)
		{
			ft_putstr_fd("Error: cd: HOME not set\n", STDERR_FILENO);
			return (1);
		}
	}
	if (chdir(new_dir) == -1)
	{
		perror("chdir error");
		return (1);
	}
	if (update_env_pwd(ptr_env_heap) == 1)
		return (1);
	return (0);
}

/**
 * @brief updates PWD and OLDPWD after a change directory cd, command
 *
 * @param env_heap
 * @return t_env*
 */
static int	update_env_pwd(t_env **ptr_env_heap)
{
	char	pwd[500];
	char	*old_pwd;
	char	*ret;

	ret = getcwd(pwd, sizeof(pwd));
	if (ret == NULL)
		return (1);
	old_pwd = get_env_key_value("PWD", *(ptr_env_heap));
	ft_get_old_pwd(ptr_env_heap, old_pwd);
	if (old_pwd != NULL)
	{
		if (ft_unset_basic("PWD", ptr_env_heap) == 1)
			return (1);
	}
	*(ptr_env_heap) = ft_export_basic("PWD", pwd, *(ptr_env_heap));
	return (0);
}

static void	ft_get_old_pwd(t_env **ptr_env_heap, char *old_pwd)
{
	char	*curr_old_pwd;

	curr_old_pwd = get_env_key_value("OLDPWD", *(ptr_env_heap));
	if (curr_old_pwd != NULL)
	{
		ft_unset_basic("OLDPWD", ptr_env_heap);
		if (old_pwd == NULL)
			*(ptr_env_heap) = ft_export_basic("OLDPWD", "\0", *(ptr_env_heap));
		else
			*(ptr_env_heap) = ft_export_basic("OLDPWD",
					old_pwd, *(ptr_env_heap));
	}
	else
		*(ptr_env_heap) = ft_export_basic("OLDPWD", "\0", *(ptr_env_heap));
}

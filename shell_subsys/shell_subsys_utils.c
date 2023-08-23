/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_subsys_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranero <mgranero@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 10:54:30 by mgranero          #+#    #+#             */
/*   Updated: 2023/08/18 11:12:17 by mgranero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_subsys.h"

void	set_prompt_txt(char *prompt, char *msg)
{
	ft_strlcpy(prompt, msg, ft_strlen(msg));
}

int	str_compare(char *str1, char *str2)
{
	int		len_str1;
	int		len_str2;
	char	*str1_no_spaces;
	char	*str2_no_spaces;

	if (str1 == NULL || *str1 == 0 || str2 == NULL)
		return (-1);
	str1_no_spaces = ft_strtrim(str1, " \t\v\n");
	str2_no_spaces = ft_strtrim(str2, " \t\v\n");
	len_str1 = ft_strlen(str1_no_spaces);
	len_str2 = ft_strlen(str2_no_spaces);
	if (len_str1 == len_str2
		&& ft_strncmp(str1_no_spaces, str2_no_spaces, len_str1) == 0)
	{
		free(str1_no_spaces);
		free(str2_no_spaces);
		return (0);
	}
	free(str1_no_spaces);
	free(str2_no_spaces);
	return (1);
}

/**
 * @brief support function for printing error
 *  message and return NULL
 *
 * @param str error message to be printed in stderr
 * @return t_env* always returns NULL
 */
t_env	*print_err_ret_0(char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	return (NULL);
}

/**
 * @brief function checks if the input was exit and exits the code
 *
 * @param buff_heap
 * @param env_heap
 * @return int
 */
int	check_exit(char *buff_heap)
{
	char	**split;
	int		nb;
	int		i;
	int		is_digit;

	split = ft_split(buff_heap, ' ');
	i = 0;
	is_digit = 0;
	if (split[1] != NULL)
	{
		while (split[1][i])
		{
			if (ft_isdigit(split[1][i]) == 1)
			{
				is_digit = 1;
			}
			else
			{
				is_digit = 0;
				break;
			}
			i++;
		}
		if (is_digit == 1)
			nb = ft_atoi(split[1]);
		else
			nb = 255;
	}
	else
	{
		is_digit = 1;
		nb = 1;
	}

	if ((str_compare(split[0], "exit") == 0 && is_digit == 1 )
		|| (str_compare(split[0], "exit") == 0 && nb == 255))
	{
		printf("exit requested by user\n\n");
		free(buff_heap);
		if (split)
			split = ft_free(split);

		return (nb);
	}
	if (split)
		split = ft_free(split);
	return (0);
}

int	free_buff_ret_1(char *buff)
{
	free(buff);
	return (1);
}

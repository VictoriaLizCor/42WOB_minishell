/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_put_error_str.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranero <mgranero@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:03:22 by mgranero          #+#    #+#             */
/*   Updated: 2023/07/07 15:03:34 by mgranero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 * @brief function used to print a string in STDERROR and returns -1
 *
 * @param str
 * @return int
 */
int	put_error_str(char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	return (-1);
}

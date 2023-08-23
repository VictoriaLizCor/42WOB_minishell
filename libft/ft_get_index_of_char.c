/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_index_of_char.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranero <mgranero@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 16:52:46 by mgranero          #+#    #+#             */
/*   Updated: 2023/07/10 21:39:33 by mgranero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Get the index of char inside a string that matches the passed
 *  character c
 *
 * @param str string to be scanned
 * @param c character to be searched
 * @return int returns the index of the found char or -1 for no matches
 */
int	ft_get_index_of_char(char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

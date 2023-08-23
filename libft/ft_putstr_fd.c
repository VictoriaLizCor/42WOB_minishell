/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:03:20 by mgranero          #+#    #+#             */
/*   Updated: 2023/08/16 16:39:18 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Outputs the string ’s’ to the given file
descriptor.

Parameters:
	s:  The string to output.
	fd:  The file descriptor on which to write.

void ft_putstr_fd(char *s, int fd);
*/
#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s == 0)
		return ;
	if (fd == 2)
		write(fd, "\033[1;31m", ft_strlen("\033[1;31m"));
	while (s[i] != '\0')
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
	if (fd == 2)
		write(fd, "\033[1;31m", ft_strlen("\033[1;31m"));
}

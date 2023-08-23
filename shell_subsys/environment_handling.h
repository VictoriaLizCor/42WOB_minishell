/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_handling.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranero <mgranero@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 19:39:24 by mgranero          #+#    #+#             */
/*   Updated: 2023/07/23 09:24:15 by mgranero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_HANDLING_H
# define ENVIRONMENT_HANDLING_H

# include "../libft/libft.h"

typedef struct s_enviroment
{
	char	*key;
	char	*value;
}	t_env;

char	*get_env_key_value(char *key_searched, t_env *env_heap);
int		getenvheap_size(t_env *env_heap);

#endif
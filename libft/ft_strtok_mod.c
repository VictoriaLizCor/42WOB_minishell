/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok_mod.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranero <mgranero@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 11:56:21 by mgranero          #+#    #+#             */
/*   Updated: 2023/07/12 18:01:20 by mgranero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*get_last_token(char *str, int idx_sep, int *idx_next, int match);
static char	*get_token(char *str, char *sep, int *idx_next);
static char	*create_token(char *str, int *idx_next, int match, int i);

/**
 * @brief The strtok() function is used to isolate sequential tokens in a
 * 	null-terminated string, str.  These tokens are
 *  separated in the string by at least one of the characters in sep.
 * 	it return the token as the match of the first occurence.
 *  this modified function does not has a static variable to remmember the
 *  the last match and return the next token. Therefore the first time it
 *  runs, an int idx_next variable to be initialized to 0, in the next calls
 *  this idx_next must be passed and not modified and enables getting the
 *  next match of the delimiter. The str to be searched must be passed in e
 *  very call without being change.
 *  similar to strktok original the function does not allocate memory.
 *  example :
 *  #include <printf.h>
 *   int main (void)
 *	 {
 *		char line_1[] ={"--cm'- with this separtor--"};
 *		char sep[] = {" '"};
 *		char *token;
 *		int idx_next = 0;
 *
 *		token = ft_strtok_mod(line_2, sep, &idx_next);
 *		while (token != NULL)
 *		{
 *			printf("token:%s\n", token);
 *			token = ft_strtok_mod(line_2, sep, &idx_next);
 *		}
 *		printf("mod line is:%s\n", token);
 *		return (0);
 *	}
 * @param str string to be tokenized
 * @param sep group of n characters to be individually searched in str
 * @param idx_last_match address of a variable to be passed in and
 *  will store the value of the index of the last match of sep +1 in the
 *  last call as ft_strtok_mod. In the first call idx_last_match must be
 *  intialized to 0.
 *  (replaces the original static memory variable from the original strtok)
 * @return char* functions return a pointer to the beginning of each subsequent
 *   token in the string,
 *   after replacing the token itself with a NUL character.
 *   When no more tokens remain, a null pointer is returned.
 */
char	*ft_strtok_mod(char *str, char *sep, int *idx_next)
{
	if (str == NULL || sep == NULL || idx_next == NULL)
	{
		write(2, "Error: ft_strtok_mod incorrect arguments\n", 41);
		return (NULL);
	}
	if (*idx_next == -2)
		return (NULL);
	return (get_token(str, sep, idx_next));
}

static char	*get_token(char *str, char *sep, int *idx_next)
{
	int		match;
	int		i;
	int		j;

	match = 0;
	i = 0;
	while (*(str + *idx_next + i) != '\0')
	{
		j = 0;
		while (sep[j] != '\0')
		{
			if (*(str + *idx_next + i) == sep[j])
			{
				if (i == match)
					return (get_last_token(str, -1, idx_next, ++match));
				else
					return (create_token(str, idx_next, match, i));
			}
			j++;
		}
		i++;
	}
	return (get_last_token(str, -1, idx_next, match));
}

static char	*get_last_token(char *str, int idx_sep, int *idx_next, int match)
{
	char	*token;

	if (idx_sep == -1 && *(str + *idx_next + match) != '\0')
	{
		token = str + *idx_next + match;
		*idx_next = -2;
		return (token);
	}
	return (NULL);
}

static char	*create_token(char *str, int *idx_next, int match, int i)
{
	int		idx_sep;
	char	*token;

	idx_sep = i;
	str[idx_sep + *idx_next] = '\0';
	token = str + *idx_next + match;
	*idx_next = idx_sep + *idx_next + 1;
	return (token);
}

/*
#include <string.h>
#include <printf.h>

int main(void)
{
	char line_1[] ={"--cm'- with this separtor--"};
	char line_2[]={"--cm'- with this separtor--"};
	char sep[] = {" '"};
	char *token_original;
	char *token_mod;
	int idx_next = 0;

	// original
	token_original = strtok(line_1, sep);
	while (token_original != NULL)
	{
		printf("token_original:%s\n", token_original);
		// free(token_original);
		token_original = strtok(NULL, sep);
	}
	printf("original line is:%s\n", token_original);
	printf("\n");
	// modified

	token_mod = ft_strtok_mod(line_2, sep, &idx_next);
	while (token_mod != NULL)
	{
		printf("token_mod:%s\n", token_mod);
		token_mod = ft_strtok_mod(line_2, sep, &idx_next);
	}
	printf("mod line is:%s\n", token_mod);
	return (0);
}
*/

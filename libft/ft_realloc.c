/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgranero <mgranero@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 14:24:04 by mgranero          #+#    #+#             */
/*   Updated: 2023/08/04 17:20:02 by mgranero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief
 * The realloc() function tries to change the size of the allocation pointed
 * to by ptr to size, and returns ptr.
 * the memory allocation pointed to by ptr, realloc () creates a new
 * allocation, copies as much of the old data pointed to by ptr as will fit
 * to the new allocation, frees the old allocation, and returns a pointer
 * to the allocated memory.
 * If ptr is NULL, realloc() is identical to a call to
 * malloc() for size bytes.
 * If size is zero and ptr is not NULL, a new,
 * minimum sized object is allocate d and the original object is
 * freed.
 *
 * @param ptr ptr to be reallocated
 * @param size size of new ptr allocated
 * @return void*  new ptr with data. the input pointer is still valid if
 *  reallocation failed.
 */
void	*ft_realloc(void *ptr, size_t curr_size, size_t new_size)
{
	char	*new_ptr;
	size_t	i;

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		ptr = 0;
		return (NULL);
	}
	new_ptr = malloc (new_size);
	if (new_ptr == NULL)
		return (ptr);
	ft_memset(new_ptr, 0, new_size);
	if (ptr == NULL)
		return (new_ptr);
	i = 0;
	while (i < curr_size)
	{
		new_ptr[i] = *(char *)(ptr + i);
		i++;
	}
	free(ptr);
	return (new_ptr);
}

/* testing main*/
/*
#include <stdio.h> // testing
int	main(int argc, char **argv)
{
	char *str0 = 0;
	char *str1 = ft_strdup("this string first\n");
	char *str2 =  ft_strdup("extended version with much more data\n");
	char *out = 0;

	printf("str1 %p\n", str1);
	printf("str2 %p\n", str2);

	// firt call will allocate some memory
	out = ft_realloc(str0, 10);
	printf("1malloc pointer %p, text:%s\n", out, out);

	free(out);


	out = ft_realloc(str1, 19);
	printf("2realloc 1 pointer %p, text:%s", out, out);

	free(out);

	out = ft_realloc(str2, 38);
	printf("3realloc 2 pointer %p, text:%s", out, out);

	out = ft_realloc(out, 0);
	if (out != NULL)
		printf("4 return the passed %p, text:%s", out, out);
	else
		printf("4 out was freed\n");
	// free(str1);
	//free(str2);
	return (0);
}*/
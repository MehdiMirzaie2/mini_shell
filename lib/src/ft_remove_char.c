/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 13:09:47 by mehdimirzai       #+#    #+#             */
/*   Updated: 2023/10/07 13:18:01 by mehdimirzai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_remove_char(char *haystack, char to_remove)
{
    int new_len; // Initialize the length of the new string
    int i; // Initialize the index for the input string
	char *result;

	i = 0;
	new_len = 0;
	while (haystack[i] != '\0')
        if (haystack[i++] != to_remove)
            new_len++;
	i = 0;
	new_len = 0;
	result = malloc(new_len + 1); // Allocate memory for the result string
    if (result == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    while (haystack[i] != '\0')
	{
        if (haystack[i] != to_remove)
		{
            result[new_len] = haystack[i]; // Append non-matching character to the result
            new_len++;
        }
        i++;
    }
    result[new_len] = '\0'; // Null-terminate the result string
    return (result);
}

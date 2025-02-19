/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:30:49 by rraumain          #+#    #+#             */
/*   Updated: 2024/10/30 11:19:48 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Find the first occurrence of a character in a string.
 *
 * Searches the string `s` for the first occurrence of the character `c`.
 * The search includes the null terminator, so if `c` is `\0`, the function
 * returns a pointer to the null terminator at the end of `s`.
 *
 * @param s The string to search within.
 * @param c The character to locate, interpreted as an unsigned char.
 * @return A pointer to the first occurrence of `c` in `s`, or `NULL` if `c` is
 * not found.
 */
char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if ((unsigned char)*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if ((unsigned char)*s == (unsigned char)c)
		return ((char *)s);
	return (NULL);
}

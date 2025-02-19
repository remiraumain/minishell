/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:59:58 by rraumain          #+#    #+#             */
/*   Updated: 2024/10/30 11:19:40 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Find the last occurrence of a character in a string.
 *
 * Searches the string `s` for the last occurrence of the character `c`.
 *
 * @param s The string to search in.
 * @param c The character to find (converted to unsigned char).
 * @return A pointer to the last occurrence of `c` in `s`, or NULL if `c` is not
 * found.
 */
char	*ft_strrchr(const char *s, int c)
{
	char	*last;

	last = NULL;
	while (*s)
	{
		if ((unsigned char)*s == (unsigned char)c)
			last = (char *)s;
		s++;
	}
	if ((unsigned char)*s == (unsigned char)c)
		last = (char *)s;
	return (last);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 19:38:01 by rraumain          #+#    #+#             */
/*   Updated: 2024/10/30 11:19:42 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Compare two strings up to a specified length.
 *
 * Compares up to `n` characters of the strings `s1` and `s2`. The comparison
 * stops if a null character is encountered or if the characters differ.
 *
 * @param s1 The first string to compare.
 * @param s2 The second string to compare.
 * @param n Maximum number of characters to compare.
 * @return An integer less than, equal to, or greater than zero if `s1` is
 * found to be less than, equal to, or greater than `s2`.
 */
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	c1;
	unsigned char	c2;

	if (!n)
		return (0);
	while (n--)
	{
		c1 = (unsigned char)*s1;
		c2 = (unsigned char)*s2;
		if (c1 != c2)
			return (c1 - c2);
		if (c1 == '\0')
			return (0);
		s1++;
		s2++;
	}
	return (0);
}

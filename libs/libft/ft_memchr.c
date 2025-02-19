/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 19:58:30 by rraumain          #+#    #+#             */
/*   Updated: 2024/10/30 11:19:56 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Search for a byte in memory.
 *
 * Scans the first `n` bytes of the memory area pointed to by `s` for the
 * first occurrence of the byte `c`.
 *
 * @param s Pointer to the memory area to search.
 * @param c Byte value to search for (converted to unsigned char).
 * @param n Number of bytes to search in `s`.
 * @return Pointer to the first occurrence of `c` in `s`, or `NULL` if not
 * found.
 */
void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n--)
	{
		if (*ptr == (unsigned char)c)
			return (ptr);
		ptr++;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 09:25:13 by rraumain          #+#    #+#             */
/*   Updated: 2024/10/30 11:19:44 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Copy a string to another with size limit.
 *
 * Copy up to `dstsize - 1` characters from the NUL-terminated string `src` to
 * `dst`, NUL-terminating the result.
 *
 * @param dst The destination string to copy to.
 * @param src The source string to copy.
 * @param dstsize The total size of the destination buffer.
 * @return The length of `src`.
 */
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		if (i < dstsize)
			dst[i] = src[i];
		i++;
	}
	if (i < dstsize)
		dst[i] = '\0';
	else
		dst[dstsize - 1] = '\0';
	return (i);
}

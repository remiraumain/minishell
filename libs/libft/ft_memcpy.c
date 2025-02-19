/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:54:31 by rraumain          #+#    #+#             */
/*   Updated: 2024/10/30 11:19:55 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Copy `n` bytes from a source to a destination.
 *
 * Copies `n` bytes from memory area `src` to memory area `dest`. The memory
 * areas must not overlap. Use ft_memmove if the memory areas do overlap.
 *
 * @param dest Pointer of the destination.
 * @param src Pointer of the source that is being copied.
 * @param n Number of bytes to copy.
 * @return A pointer to dest.
 */
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*ptr_src;
	char	*ptr_dest;

	i = 0;
	ptr_src = (char *)src;
	ptr_dest = (char *)dest;
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		ptr_dest[i] = ptr_src[i];
		i++;
	}
	return (dest);
}

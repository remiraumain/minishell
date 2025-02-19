/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:41:17 by rraumain          #+#    #+#             */
/*   Updated: 2024/10/30 11:19:53 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Replace `n` bytes of `s` with the constant byte `c`.
 *
 * Fills the first `n` bytes of the memory area pointed to by `s` with the
 * constant byte `c`.
 *
 * @param s Pointer of the memory's location.
 * @param c The constant byte that is used for the replacement.
 * @param n Number of bytes to erase.
 */
void	*ft_memset(void *s, int c, size_t n)
{
	char	*ptr;

	ptr = (char *)s;
	while (n)
	{
		*ptr = c;
		ptr++;
		n--;
	}
	return (s);
}

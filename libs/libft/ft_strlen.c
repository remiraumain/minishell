/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 08:15:44 by rraumain          #+#    #+#             */
/*   Updated: 2024/10/30 11:19:44 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Calculate the length of a string.
 *
 * Calculates the length of the string pointed to by `s`, excluding the
 * terminating null byte (`\0`).
 *
 * @param s Pointer of the string.
 * @return The lenght of the string (number of bytes) pointed by `s`.
 */
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

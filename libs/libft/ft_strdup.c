/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:19:54 by rraumain          #+#    #+#             */
/*   Updated: 2024/10/30 11:19:47 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Allocate and duplicate a string.
 *
 * The ft_strdup() function returns a pointer to a new string which is a
 * duplicate of the string `s`. Memory for the new string is obtained with
 * malloc(3), and can be freed with free(3).
 *
 * @param s The string to duplicate.
 * @return The duplicated string. `NULL` if insufficient memory was available.
 */
char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*dup;

	len = ft_strlen(s) + 1;
	dup = malloc(len * sizeof(char));
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, s, len);
	return (dup);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 07:22:43 by rraumain          #+#    #+#             */
/*   Updated: 2024/10/30 11:19:39 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Return a substring.
 *
 * Allocates (with malloc(3)) and returns a substring from the string `s`. The
 * substring begins at index `start` and is of maximum size `len`.
 *
 * @param s String from which to create the substring.
 * @param start Index of the substring in the string `s`.
 * @param len The maximum length of the substring.
 * @return The substring. `NULL` if the allocation fails.
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	size_t	sub_len;
	char	*sub;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
	{
		sub = ft_strdup("");
		return (sub);
	}
	if (s_len - start < len)
		sub_len = s_len - start;
	else
		sub_len = len;
	sub = malloc((sub_len + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	ft_strlcpy(sub, s + start, sub_len + 1);
	return (sub);
}

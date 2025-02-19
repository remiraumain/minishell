/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 08:06:22 by rraumain          #+#    #+#             */
/*   Updated: 2024/10/30 11:19:41 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Find a substring within a string up to a limit.
 *
 * Searches for the first occurrence of the null-terminated `needle` within
 * `haystack`, up to `len` characters. Stops searching after any '\0'.
 *
 * @param haystack The string to search in.
 * @param needle The substring to find.
 * @param len Maximum characters to search in haystack.
 * @return Pointer to the first occurrence of needle, or `NULL` if not found.
 * Returns haystack if needle is empty.
 */
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	char	*ptr;

	if (!haystack && len == 0)
		return (NULL);
	if (*needle == '\0')
		return ((char *)haystack);
	i = ft_strlen(needle);
	ptr = (char *)haystack;
	while (*ptr && len >= i)
	{
		if (*ptr == *needle && ft_strncmp(ptr, needle, i) == 0)
			return (ptr);
		ptr++;
		len--;
	}
	return (NULL);
}

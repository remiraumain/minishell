/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:49:24 by rraumain          #+#    #+#             */
/*   Updated: 2024/10/30 11:19:43 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Return a new string with the function `f` applied on each character.
 *
 * Applies the function `f` to each character of the string `s`, passing its
 * `index` as the first argument and the `character` itself as the second. A new
 * string is created (using malloc(3)) to collect the results from the
 * successive applications of `f`.
 *
 * @param s The string on which to iterate.
 * @param f The function to apply to each character.
 * @return The string created from the successive applications of `f`. `NULL` if
 * the allocation fails.
 */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*dup;

	if (!s || !f)
		return (NULL);
	i = ft_strlen(s);
	dup = malloc((i + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	dup[i] = '\0';
	while (i)
	{
		i--;
		dup[i] = f(i, s[i]);
	}
	return (dup);
}

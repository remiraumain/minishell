/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 09:17:03 by rraumain          #+#    #+#             */
/*   Updated: 2024/10/30 11:19:38 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Convert an uppercase letter to lowercase.
 *
 * If `c` is an uppercase letter, converts it to the corresponding lowercase
 * letter. If `c` is not an uppercase letter, it is returned unchanged.
 *
 * @param c The character to convert.
 * @return The lowercase equivalent of `c` if it is uppercase, otherwise `c`
 * unchanged.
 */
int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	else
		return (c);
}

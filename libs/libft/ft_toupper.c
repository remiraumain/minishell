/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 09:11:47 by rraumain          #+#    #+#             */
/*   Updated: 2024/10/30 11:19:37 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Convert a lowercase letter to uppercase.
 *
 * If `c` is a lowercase letter, converts it to the corresponding uppercase
 * letter. If `c` is not a lowercase letter, it is returned unchanged.
 *
 * @param c The character to convert.
 * @return The uppercase equivalent of `c` if it is lowercase, otherwise `c`
 * unchanged.
 */
int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	else
		return (c);
}

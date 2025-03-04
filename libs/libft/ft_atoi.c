/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:27:49 by rraumain          #+#    #+#             */
/*   Updated: 2025/03/04 15:30:01 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Convert a string to an integer.
 *
 * Converts the initial portion of the string pointed to by `nptr` to an
 * integer. ft_atoi() does not detect errors.
 *
 * @param nptr Pointer of the string to convert into an int.
 * @return The converted value or zero `0` on error.
 */
int	ft_atoi(const char *nptr)
{
	int	i;
	int	res;
	int	sign;

	i = 0;
	res = 0;
	sign = 1;
	while (nptr[i] == ' ' || nptr[i] == '\t' || nptr[i] == '\n'
		|| nptr[i] == '\v' || nptr[i] == '\f' || nptr[i] == '\r')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + (nptr[i++] - '0');
	}
	return (res * sign);
}

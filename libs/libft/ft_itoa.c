/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 08:35:54 by rraumain          #+#    #+#             */
/*   Updated: 2024/10/30 11:20:09 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	negative(int n, char *a, int size)
{
	a[0] = '-';
	a[size] = '\0';
	size--;
	n = n * -1;
	while (0 < size)
	{
		a[size] = n % 10 + '0';
		n = n / 10;
		size--;
	}
}

static void	positive(int n, char *a, int size)
{
	a[size] = '\0';
	size--;
	while (0 <= size)
	{
		a[size] = n % 10 + '0';
		n = n / 10;
		size--;
	}
}

static int	get_size(int n)
{
	int	size;

	size = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		size++;
		n = n * -1;
	}
	while (n > 0)
	{
		size++;
		n = n / 10;
	}
	return (size);
}

/**
 * @brief Alloate and return as a string the integer.
 * 
 * Allocates (with malloc(3)) and returns a string representing the integer 
 * received as an argument. 
 * 
 * @param n The integer to convert.
 * @return The string representing the integer. `NULL` if the allocation fails.
 */
char	*ft_itoa(int n)
{
	int		size;
	char	*a;

	if (n == -2147483648)
	{
		a = ft_strdup("-2147483648");
		return (a);
	}
	size = get_size(n);
	a = malloc(size * sizeof(char) + 1);
	if (!a)
		return (NULL);
	a[0] = '\0';
	if (n == 0)
		a[0] = '0';
	if (n < 0)
		negative(n, a, size);
	if (n > 0)
		positive(n, a, size);
	a[size] = '\0';
	return (a);
}

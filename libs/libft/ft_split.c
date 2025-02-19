/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 06:00:48 by rraumain          #+#    #+#             */
/*   Updated: 2024/10/30 11:19:49 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	i;
	int	count;
	int	in_word;

	i = 0;
	count = 0;
	in_word = 0;
	while (s[i])
	{
		if (s[i] != c && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (s[i] == c)
			in_word = 0;
		i++;
	}
	return (count);
}

static char	*malloc_word(const char *s, char c, int *start)
{
	int		tmp;
	int		len;
	char	*word;

	tmp = *start;
	len = 0;
	while (s[*start] && s[*start] != c)
	{
		(*start)++;
		len++;
	}
	if (!len)
		return (NULL);
	word = ft_substr(s, tmp, len);
	return (word);
}

static int	fill_arr(char **arr, int word_count, char const *s, char c)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	while (i < word_count)
	{
		while (s[start] == c)
			start++;
		arr[i] = malloc_word(s, c, &start);
		if (!arr[i])
		{
			while (i > 0)
			{
				i--;
				free(arr[i]);
			}
			free(arr);
			return (-1);
		}
		i++;
	}
	arr[i] = 0;
	return (0);
}

/**
 * @brief Return an array of the split strings.
 *
 * Allocates (with malloc(3)) and returns an array of strings obtained by
 * splitting `s` using the character `c` as a delimiter. The array must end
 * with a NULL pointer.
 *
 * @param s string to be split.
 * @param start Delimiter characte.
 * @return The array of new strings resulting from the split. `NULL` if the
 * allocation fails.
 */
char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		word_count;
	int		success;

	if (!s)
		return (NULL);
	word_count = count_words(s, c);
	arr = malloc((word_count + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	success = fill_arr(arr, word_count, s, c);
	if (success == -1)
		return (NULL);
	return (arr);
}

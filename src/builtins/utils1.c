/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 08:22:54 by nolecler          #+#    #+#             */
/*   Updated: 2025/03/11 10:16:32 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (1);
	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0')
		i++;
	if (s1[i] == s2[i])
		return (0);
	return (1);
}

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

// char	*ft_strdup(char *src)
// {
// 	int	i;
// 	char	*dest;

// 	i = 0;
// 	dest = malloc(sizeof(char) * ft_strlen(src) + 1);
// 	if (!dest)
// 		return (NULL);
// 	while (src[i])
// 	{
// 		dest[i] = src[i];
// 		i++;
// 	}
// 	dest[i] = '\0';
// 	return (dest);
// }

// void	ft_lstadd_back(t_envp **lst, t_envp *new)// libft ??
// {
// 	t_envp	*tmp;

//     if (!lst || !new)
//         return ;
// 	if (*lst == NULL)
// 	{
// 		*lst = new;
// 		return ;
// 	}
// 	tmp = *lst;
// 	while (tmp->next != NULL)
// 		tmp = tmp->next;
// 	tmp->next = new;
// }

void free_env_copy(t_envp *var)
{
    t_envp *tmp;
    
    while (var)
    {
        tmp = var;
        var = var->next;
        free(tmp->name);
        free(tmp->value);
        free(tmp);
    }
}
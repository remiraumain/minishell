/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 20:02:31 by rraumain          #+#    #+#             */
/*   Updated: 2025/02/16 23:39:35 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(t_token_type type, char *value)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = type;
	new_token->value = value;
	new_token->next = NULL;
	return (new_token);
}

void	add_token(t_token **head, t_token *newt)
{
	t_token	*tmp;

	if (!*head)
		*head = newt;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = newt;
	}
}

void	free_token_list(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head->value);
		free(head);
		head = tmp;
	}
}

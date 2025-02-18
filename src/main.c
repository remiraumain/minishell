/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraumain <rraumain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:40:01 by rraumain          #+#    #+#             */
/*   Updated: 2025/02/17 00:00:30 by rraumain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_data	data;
	t_token	*tokens;
	t_token	*tmp;

	(void)argc;
	(void)argv;
	data.env = env;
	(void)data;
	input = readline("minishell> ");
	tokens = lexer(input);
	tmp = tokens;
	while (tmp)
	{
		printf("type=%d, value=%s\n", tmp->type, tmp->value);
		tmp = tmp->next;
	}
	free_token_list(tokens);
	free(input);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 11:38:39 by nolecler          #+#    #+#             */
/*   Updated: 2025/03/20 14:36:59 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

// unset VAR_NAME
// unset VAR1 VAR2 VAR3
// unset suivi d une variable inconnue ne renvoie pas de message d erreur

// creer une copie de l envp (char **);
// unset export en liste chainee
// reconstituer char ** pour l execution 
// copier chaque variable dans une liste chainee
// recuperer l index pour preciser quelle variable on veut supprimer



int exec_unset(t_cmd *cmd, t_global_data *data)
{
	(void)cmd;
	(void)data;
	// int i;
	
	// i = 1;
	
	// if (!data->envp || !data->envp[0])
	// return (0);
	// while (cmd->argv[i])
	// {	
	// 	// 	if (is_var_valid(cmd->argv[i]) == 1)// invalide
	// 	// 		return (0);
	// 	if (is_var_exist(cmd, data) == 1)
	// 	return (0);
	// 	//delete_var(cmd);
	// 	// ft_lstdelone;
	// 	i++;
	// }
	return (1);// test
	
}

// creer une fonction qui supprime la variable donnee en argv[]

// void static delete_var(t_cmd *cmd, t_envp **var_list)
// {
//     t_envp *current;
//     t_envp *previous;
   
// 	current = *var_list;
//     previous = NULL;
//     while (current != NULL)
//     {
//         if (ft_strcmp(cmd->argv[1], current->name) == 0)
//         {
// 			if (previous == NULL)
// 				*var_list = current->next;
// 			else
// 				previous->next = current->next;
// 			free(current->name);
// 			free(current->value);
// 			free(current);
//             //delete(current);
// 			//ft_lstclear();
// 			// ft_lstdelone;
// 			// ou juste free(current)
//             return;
//         }
//         previous = current;
//         current = current->next;
//     }
// }


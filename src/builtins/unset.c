/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 11:38:39 by nolecler          #+#    #+#             */
/*   Updated: 2025/03/07 17:49:55 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

// unset VAR_NAME
// unset VAR1 VAR2 VAR3
// unset suivi d une variable inconnue ne renvoie pas de message d erreur


static int is_var_valid(char *str)
{
	int	i;

	i = 0;
	if (str[0] != '_' && !ft_isalpha(str[0])) // ft_isalpha retourn 0 si faux
		return (1); // false
	if (str[0] == '_' && ft_isdigit(str[1]))
        return (1);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')// _VAR
			return (1);
		i++;
	}
	return (0); // true
}


static int is_var_exist(t_cmd *cmd, t_global_data *data)
{
	int		i;// index de l envp[i]
	int		j;// index de la cmd->argv[j]

	i = 0;
	j = 1; // car av[0] = "unset"
	if (!data->envp || !data->envp[0])
		return (1);
	while (data->envp[i])
	{
		if (ft_strcmp(cmd->argv[j], data->envp[i]) == 0)
			return (0);	// la variable existe
		i++;
	}
	return (1);// variable non existant
}

// creer une fonction qui supprime la variable donnee en argv[]

void static delete_var(t_cmd *cmd, t_envp *var)
{
    t_envp *current;
    t_envp *previous;
    t_envp *head;

    head = var; // tête de liste
    current = head;
    previous = NULL;
    while (current != NULL)
    {
        if (ft_strcmp(cmd->argv[1], current->name) == 0)
        {
            // Si c'est la tête de la liste
            if (current == head)
                head = current->next; // Réaffecte la tête
            else
                previous->next = current->next; // Mise à jour du précédent nœud
            delete(current); // Supprimer le nœud
            return;
        }
        previous = current;      // Sauvegarde le nœud précédent
        current = current->next;
    }
}


// int exec_unset(t_cmd *cmd, t_global_data *data)
// {
// 	int i;
	
// 	i = 0;

// 	if (!data->envp || !data->envp[0])
// 		return (0);
// 	if (!cmd->argv[1])
// 		return (0);
// 	if (is_var_valid(cmd->argv[1]) == 1)// invalide
// 		return (0);
// 	if (is_var_exist(cmd, data) == 1)
// 		return (0);
		


		
// }
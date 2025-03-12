/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:32:20 by nolecler          #+#    #+#             */
/*   Updated: 2025/03/12 16:43:17 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// Syntaxe : export VAR=VALUE
// Si aucun argument : afficher toutes les variables triées.
// Si VAR existe déjà : mettre à jour sa valeur.
// Si syntaxe invalide (ex. : VAR@VALUE) : afficher une erreur.

// export VAR=VALUE → ajoute ou met à jour la variable.
// export VAR → ajoute une variable vide.
// export → affiche les variables triées.


// static int is_var_valid(char *str)
// {
// 	int	i;

// 	i = 0;
// 	if (str[0] != '_' && !ft_isalpha(str[0])) // ft_isalpha retourn 0 si faux
// 		return (1); // false
// 	if (str[0] == '_' && ft_isdigit(str[1]))
//         return (1);
// 	while (str[i])
// 	{
// 		if (!ft_isalnum(str[i]) && str[i] != '_')// _VAR
// 			return (1);
// 		i++;
// 	}
// 	return (0); // true
// }


// export sans argument
// affichage comme ceci declare -x LESS="-R"
// affiche les variables d env dans l ordre alphabetique precede de declare -x





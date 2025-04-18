/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   underscore.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:34:23 by nolecler          #+#    #+#             */
/*   Updated: 2025/04/18 16:35:39 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UNDERSCORE_H
# define UNDERSCORE_H

# include "minishell.h"

void	reset_underscore(t_global_data *data);
void	update_underscore(t_cmd *cmds, t_global_data *data);

#endif
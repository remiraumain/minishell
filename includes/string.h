/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 08:32:33 by nolecler          #+#    #+#             */
/*   Updated: 2025/02/28 10:56:50 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef STRING_H
# define STRING_H

int		is_whitespace(char c);
int		ft_strcmp(char *s1, char *s2);
void	ft_putstr_fd(char *str, int fd);



#endif
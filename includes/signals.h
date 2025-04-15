/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolecler <nolecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 16:26:56 by rraumain          #+#    #+#             */
/*   Updated: 2025/04/15 15:26:35 by nolecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

void	handle_sigint_no_redisplay(int sig);
void	set_parent_signals(void);
void	set_heredoc_signals(void);
void	set_child_signals(void);

#endif
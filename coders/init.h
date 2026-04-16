/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrishero <chrishero@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 14:41:14 by chrishero         #+#    #+#             */
/*   Updated: 2026/04/16 14:41:15 by chrishero        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H
# include "utils.h"
# include "codexion.h"

t_args			init_args(char **argv);
t_dongle		*init_dongles(int n_dongle);
t_coder			*init_coders(int n_coder);
t_simulation	*init_simulation(t_dongle *dongles,
					t_coder *coders,
					t_args params);
void			assign_dongles(t_dongle *dongles, t_coder *coders);
t_queue			*init_queue(void);

#endif
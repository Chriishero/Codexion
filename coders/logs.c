/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrishero <chrishero@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 14:40:49 by chrishero         #+#    #+#             */
/*   Updated: 2026/04/16 20:25:36 by chrishero        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	print_log(t_simulation *sim, t_coder *coder)
{
	t_coder_state	state;

	pthread_mutex_lock(&coder->mutex);
	state = coder->state;
	pthread_mutex_unlock(&coder->mutex);
	pthread_mutex_lock(&sim->state_mutex);
	if (sim->state == FINISH)
		return (pthread_mutex_unlock(&sim->state_mutex), (void)0);
	pthread_mutex_unlock(&sim->state_mutex);
	pthread_mutex_lock(&sim->logs_mutex);
	if (state == TAKEN_DONGLE)
		printf("%ld %d has taken a dongle\n", get_time(sim->start_time),
			coder->id);
	else if (state == COMPILING)
		printf("%ld %d is compiling\n", get_time(sim->start_time), coder->id);
	else if (state == DEBUGGING)
		printf("%ld %d is debugging\n", get_time(sim->start_time), coder->id);
	else if (state == REFACTORING)
		printf("%ld %d is refactoring\n", get_time(sim->start_time), coder->id);
	else if (state == BURNOUT)
		printf("%ld %d burned out\n", get_time(sim->start_time), coder->id);
	pthread_mutex_unlock(&sim->logs_mutex);
}

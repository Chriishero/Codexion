/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrishero <chrishero@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 14:40:24 by chrishero         #+#    #+#             */
/*   Updated: 2026/04/16 20:40:13 by chrishero        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	monitor(void *simulation_data)
{
	t_simulation	*sim;
	t_coder			*coder;

	sim = (t_simulation *)simulation_data;
	while (1)
	{
		update_dongles_state(sim->dongles, sim);
		coder = sim->coders;
		if (stop_condition(sim, coder) == TRUE)
			return (stop_simulation(sim));
	}
}

void	update_dongles_state(t_dongle *dongle, t_simulation *simulation)
{
	int			i;

	i = 0;
	while (i < simulation->params.number_of_coders)
	{
		pthread_mutex_lock(&dongle->mutex);
		if (get_time(simulation->start_time) >= dongle->cooldown
			&& dongle->state == IN_COOLDOWN)
		{
			dongle->state = AVAILABLE;
			dongle->cooldown = 0;
			pthread_cond_broadcast(&dongle->cond);
		}
		pthread_mutex_unlock(&dongle->mutex);
		dongle = dongle->next;
		i++;
	}
}

int	stop_condition(t_simulation *simulation, t_coder *coder)
{
	int	i;
	int	stop;

	i = 0;
	stop = TRUE;
	while (i < simulation->params.number_of_coders)
	{
		pthread_mutex_lock(&coder->mutex);
		if (get_time(simulation->start_time) - coder->last_compile_start
			> simulation->params.time_to_burnout && coder->state != FINISH)
		{
			coder->state = BURNOUT;
			pthread_mutex_unlock(&coder->mutex);
			print_log(simulation, coder);
			return (TRUE);
		}
		else if (coder->state != FINISH)
			stop = FALSE;
		pthread_mutex_unlock(&coder->mutex);
		coder = coder->next;
		i++;
	}
	return (stop);
}

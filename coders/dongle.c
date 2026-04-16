/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrishero <chrishero@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 14:40:17 by chrishero         #+#    #+#             */
/*   Updated: 2026/04/16 20:37:57 by chrishero        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	take_dongle(t_coder *coder, t_dongle *dongle, t_simulation *simulation)
{
	pthread_mutex_lock(&dongle->mutex);
	add_coder(&dongle->queue, coder, simulation->params);
	while (take_dongle_condition(coder, dongle) == FALSE)
	{
		pthread_cond_wait(&dongle->cond, &dongle->mutex);
		if (is_finish(simulation, coder))
		{
			pop_coder(&dongle->queue);
			pthread_mutex_unlock(&dongle->mutex);
			return (FALSE);
		}
	}
	dongle->state = USED;
	dongle->cooldown = 0;
	pop_coder(&dongle->queue);
	pthread_mutex_unlock(&dongle->mutex);
	return (TRUE);
}

void	release_dongle(t_dongle *dongle, t_simulation *simulation)
{
	pthread_mutex_lock(&dongle->mutex);
	dongle->state = IN_COOLDOWN;
	dongle->cooldown = (get_time(simulation->start_time)
			+ simulation->params.dongle_cooldown);
	pthread_mutex_unlock(&dongle->mutex);
}

int	take_dongle_condition(t_coder *coder, t_dongle *dongle)
{
	if (dongle->state == AVAILABLE
		&& dongle->queue->coder->id == coder->id)
		return (TRUE);
	return (FALSE);
}

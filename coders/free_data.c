/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrishero <chrishero@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 14:41:08 by chrishero         #+#    #+#             */
/*   Updated: 2026/04/16 14:41:08 by chrishero        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	free_data(t_simulation *simulation)
{
	t_dongle		*d_prev;
	t_coder			*c_prev;
	int				i;

	i = 0;
	while (i < simulation->params.number_of_coders)
	{
		d_prev = simulation->dongles;
		c_prev = simulation->coders;
		simulation->coders = simulation->coders->next;
		simulation->dongles = simulation->dongles->next;
		free_dongle(d_prev);
		free_coder(c_prev);
		i++;
	}
	free_simulation(simulation);
}

void	free_dongle(t_dongle *dongle)
{
	t_queue	*prev;

	pthread_mutex_destroy(&dongle->mutex);
	while (dongle->queue)
	{
		prev = dongle->queue;
		dongle->queue = dongle->queue->next;
		free(prev);
	}
	pthread_cond_destroy(&dongle->cond);
	free(dongle);
}

void	free_coder(t_coder *coder)
{
	pthread_mutex_destroy(&coder->mutex);
	free(coder);
}

void	free_simulation(t_simulation *simulation)
{
	pthread_mutex_destroy(&simulation->state_mutex);
	pthread_mutex_destroy(&simulation->logs_mutex);
	free(simulation);
}

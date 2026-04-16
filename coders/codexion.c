/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrishero <chrishero@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 14:40:37 by chrishero         #+#    #+#             */
/*   Updated: 2026/04/16 20:37:01 by chrishero        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	start_simulation(t_simulation *simulation)
{
	t_thread_data	*all_data;

	simulation->state = TRUE;
	simulation->start_time = get_time(-1);
	all_data = create_thread(simulation);
	if (all_data == NULL)
		return (1);
	join_thread(simulation);
	return (free(all_data), 0);
}

void	stop_simulation(t_simulation *simulation)
{
	t_dongle	*dongle;
	int			i;

	dongle = simulation->dongles;
	i = 0;
	pthread_mutex_lock(&simulation->state_mutex);
	simulation->state = FALSE;
	pthread_mutex_unlock(&simulation->state_mutex);
	while (i < simulation->params.number_of_coders)
	{
		pthread_mutex_lock(&dongle->mutex);
		pthread_cond_broadcast(&dongle->cond);
		pthread_mutex_unlock(&dongle->mutex);
		dongle = dongle->next;
		i++;
	}
}

t_thread_data	*create_thread(t_simulation *sim)
{
	int				i;
	t_thread_data	*all_data;
	t_coder			*head;

	i = 0;
	all_data = (t_thread_data *)malloc(sizeof(t_thread_data)
			* sim->params.number_of_coders);
	if (!all_data)
		return (NULL);
	head = sim->coders;
	while (i < sim->params.number_of_coders)
	{
		all_data[i].simulation = sim;
		all_data[i].coder = sim->coders;
		pthread_create(&sim->coders->thread, NULL,
			&coder_function, &all_data[i]);
		sim->coders = sim->coders->next;
		i++;
	}
	sim->coders = head;
	pthread_create(&sim->monitor, NULL,
		(void *)monitor, (void *)sim);
	return (all_data);
}

void	join_thread(t_simulation *sim)
{
	int				i;
	t_coder			*head;

	i = 0;
	head = sim->coders;
	pthread_join(sim->monitor, NULL);
	while (i < sim->params.number_of_coders)
	{
		pthread_join(sim->coders->thread, NULL);
		sim->coders = sim->coders->next;
		i++;
	}
	sim->coders = head;
}

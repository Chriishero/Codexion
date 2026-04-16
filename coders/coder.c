/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrishero <chrishero@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 14:40:47 by chrishero         #+#    #+#             */
/*   Updated: 2026/04/16 21:15:15 by chrishero        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	*coder_function(void *thread_data)
{
	t_thread_data	*data;
	t_coder			*coder;
	t_simulation	*simulation;

	data = (t_thread_data *)thread_data;
	coder = data->coder;
	simulation = data->simulation;
	while (!is_finish(simulation, coder))
	{
		if (coder->left->id < coder->right->id)
			coding_routine(coder, coder->left, coder->right, simulation);
		else if (coder->right->id < coder->left->id)
			coding_routine(coder, coder->right, coder->left, simulation);
	}
	return (thread_data);
}

int	is_finish(t_simulation *simulation, t_coder *coder)
{
	pthread_mutex_lock(&coder->mutex);
	if (coder->n_compilation == simulation->params.number_of_compiles_required)
	{
		coder->state = FINISH;
		pthread_mutex_unlock(&coder->mutex);
		return (TRUE);
	}
	else if (coder->state == BURNOUT)
	{
		pthread_mutex_unlock(&coder->mutex);
		return (TRUE);
	}
	pthread_mutex_unlock(&coder->mutex);
	pthread_mutex_lock(&simulation->state_mutex);
	if (simulation->state == FALSE)
	{
		pthread_mutex_unlock(&simulation->state_mutex);
		return (TRUE);
	}
	pthread_mutex_unlock(&simulation->state_mutex);
	return (FALSE);
}

void	coding_routine(t_coder *coder, t_dongle *first_dongle,
	t_dongle *second_dongle, t_simulation *simulation)
{
	if (take_dongle(coder, first_dongle, simulation) == FALSE)
		return ;
	coder_action(coder, TAKEN_DONGLE, simulation);
	if (take_dongle(coder, second_dongle, simulation) == FALSE)
	{
		release_dongle(first_dongle, simulation);
		return ;
	}
	coder_action(coder, TAKEN_DONGLE, simulation);
	pthread_mutex_lock(&coder->mutex);
	coder->n_compilation += 1;
	coder->last_compile_start = get_time(simulation->start_time);
	pthread_mutex_unlock(&coder->mutex);
	coder_action(coder, COMPILING, simulation);
	release_dongle(second_dongle, simulation);
	release_dongle(first_dongle, simulation);
	coder_action(coder, DEBUGGING, simulation);
	coder_action(coder, REFACTORING, simulation);
	pthread_mutex_lock(&coder->mutex);
	coder->state = INACTIVE;
	pthread_mutex_unlock(&coder->mutex);
}

void	coder_action(t_coder *coder, t_coder_state state,
	t_simulation *simulation)
{
	pthread_mutex_lock(&simulation->state_mutex);
	if (simulation->state == FALSE)
	{
		pthread_mutex_unlock(&simulation->state_mutex);
		return ;
	}
	pthread_mutex_unlock(&simulation->state_mutex);
	pthread_mutex_lock(&coder->mutex);
	coder->state = state;
	pthread_mutex_unlock(&coder->mutex);
	print_log(simulation, coder);
	if (state == COMPILING)
		usleep(simulation->params.time_to_compile * 1000);
	else if (state == DEBUGGING)
		usleep(simulation->params.time_to_debug * 1000);
	else if (state == REFACTORING)
		usleep(simulation->params.time_to_refactor * 1000);
}

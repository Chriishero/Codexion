/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrishero <chrishero@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 14:41:10 by chrishero         #+#    #+#             */
/*   Updated: 2026/04/16 14:41:11 by chrishero        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

t_args	init_args(char **argv)
{
	t_args	args;

	args.number_of_coders = atoi(argv[1]);
	args.time_to_burnout = atoi(argv[2]);
	args.time_to_compile = atoi(argv[3]);
	args.time_to_debug = atoi(argv[4]);
	args.time_to_refactor = atoi(argv[5]);
	args.number_of_compiles_required = atoi(argv[6]);
	args.dongle_cooldown = atoi(argv[7]);
	args.scheduler = argv[8];
	return (args);
}

t_dongle	*init_dongles(int n_dongle)
{
	t_dongle	*head;
	t_dongle	*first;
	t_dongle	*prev;
	int			i;

	i = -1;
	while (++i < n_dongle)
	{
		head = (t_dongle *)malloc(sizeof(t_dongle));
		if (!head)
			return (NULL);
		if (i == 0)
			first = head;
		else
			prev->next = head;
		head->id = i + 1;
		head->state = AVAILABLE;
		head->cooldown = 0;
		pthread_mutex_init(&head->mutex, NULL);
		pthread_cond_init(&head->cond, NULL);
		head->queue = init_queue();
		prev = head;
	}
	return (prev->next = first, first);
}

t_coder	*init_coders(int n_coder)
{
	t_coder		*head;
	t_coder		*first;
	t_coder		*prev;
	int			i;

	i = 0;
	while (i < n_coder)
	{
		head = (t_coder *)malloc(sizeof(t_coder));
		if (!head)
			return (NULL);
		if (i == 0)
			first = head;
		else
			prev->next = head;
		head->id = i + 1;
		head->state = INACTIVE;
		head->n_compilation = 0;
		head->last_compile_start = 0;
		pthread_mutex_init(&head->mutex, NULL);
		head->thread = 0;
		prev = head;
		i++;
	}
	return (prev->next = first, first);
}

t_simulation	*init_simulation(t_dongle *dongles,
					t_coder *coders,
					t_args params)
{
	t_simulation	*simulation;

	simulation = (t_simulation *)malloc(sizeof(t_simulation));
	if (!simulation)
		return (NULL);
	simulation->dongles = dongles;
	simulation->coders = coders;
	simulation->params = params;
	simulation->state = 0;
	pthread_mutex_init(&simulation->state_mutex, NULL);
	pthread_mutex_init(&simulation->logs_mutex, NULL);
	simulation->monitor = 0;
	return (simulation);
}

void	assign_dongles(t_dongle *dongles, t_coder *coders)
{
	t_dongle	*curr_dongle;
	t_coder		*curr_coder;
	int			prev_id;

	curr_dongle = dongles;
	curr_coder = coders;
	prev_id = -1;
	while (curr_coder->id > prev_id)
	{
		prev_id = curr_coder->id;
		curr_coder->left = curr_dongle;
		curr_coder->right = curr_dongle->next;
		curr_coder = curr_coder->next;
		curr_dongle = curr_dongle->next;
	}
}

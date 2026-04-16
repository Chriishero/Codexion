/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrishero <chrishero@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 14:40:51 by chrishero         #+#    #+#             */
/*   Updated: 2026/04/16 14:40:52 by chrishero        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	add_coder(t_queue **queue, t_coder *coder, t_args params)
{
	t_queue	*new;
	t_queue	*head;

	head = *queue;
	if (head->coder == NULL)
	{
		head->coder = coder;
		head->deadline = coder->last_compile_start + params.time_to_burnout;
		return ;
	}
	new = malloc(sizeof(t_queue));
	new->coder = coder;
	new->deadline = coder->last_compile_start + params.time_to_burnout;
	new->next = NULL;
	head->next = new;
	if (!strcmp(params.scheduler, "edf")
		&& head->deadline > head->next->deadline)
		swap_coders(queue);
}

void	pop_coder(t_queue **queue)
{
	t_queue	*head;
	t_queue	*next;

	head = *queue;
	next = head->next;
	if (head->coder == NULL)
		return ;
	if (next == NULL)
	{
		head->coder = NULL;
		head->deadline = 0;
		return ;
	}
	head->coder = next->coder;
	head->deadline = next->deadline;
	head->next = next->next;
	free(next);
}

void	swap_coders(t_queue **queue)
{
	t_queue	*first;
	t_queue	*second;

	if (!(*queue) || !(*queue)->next)
		return ;
	first = *queue;
	second = first->next;
	first->next = second->next;
	second->next = first;
	*queue = second;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrishero <chrishero@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 14:41:18 by chrishero         #+#    #+#             */
/*   Updated: 2026/04/16 14:41:19 by chrishero        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

t_queue	*init_queue(void)
{
	t_queue	*queue;

	queue = (t_queue *)malloc(sizeof(t_queue));
	if (!queue)
		return (NULL);
	queue->coder = NULL;
	queue->deadline = 0;
	queue->next = NULL;
	return (queue);
}

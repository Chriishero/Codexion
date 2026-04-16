/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrishero <chrishero@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 14:41:23 by chrishero         #+#    #+#             */
/*   Updated: 2026/04/16 14:41:23 by chrishero        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(int argc, char **argv)
{
	t_args			params;
	t_dongle		*dongles;
	t_coder			*coders;
	t_simulation	*simulation;

	if (parser(argc, argv) != TRUE)
		return (1);
	params = init_args(argv);
	dongles = init_dongles(params.number_of_coders);
	coders = init_coders(params.number_of_coders);
	simulation = init_simulation(dongles, coders, params);
	assign_dongles(dongles, coders);
	if (start_simulation(simulation) == 1)
	{
		free_data(simulation);
		return (1);
	}
	free_data(simulation);
	return (0);
}

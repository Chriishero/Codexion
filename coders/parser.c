/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrishero <chrishero@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 14:41:55 by chrishero         #+#    #+#             */
/*   Updated: 2026/04/16 14:41:55 by chrishero        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	parser(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc - 1 > 8 || argc - 1 < 8)
		return (exit_err(ERR_ARGS_COUNT, -1));
	while (i < argc - 1)
	{
		if (is_str_num(argv[i]) == FALSE)
			return (exit_err(ERR_NOT_INT, i));
		if (strlen(argv[i]) > 10 || ft_atol(argv[i]) > INT_MAX)
			return (exit_err(ERR_OVERFLOW, i));
		if (atoi(argv[i]) < 0)
			return (exit_err(ERR_NEGATIVE, i));
		i++;
	}
	if (is_str_num(argv[i]) == TRUE)
		return (exit_err(ERR_NOT_STR, i));
	if (strcmp(argv[i], "edf") && strcmp(argv[i], "fifo"))
		return (exit_err(ERR_NOT_EDF_FIFO, i));
	return (TRUE);
}

int	exit_err(int code, int arg_idx)
{
	char	*arg_name;

	arg_name = find_arg_name(arg_idx);
	if (code == ERR_ARGS_COUNT)
		fprintf(stderr, "Error: the number of argument must be 8.\n");
	else if (code == ERR_NOT_INT)
		fprintf(stderr, "Error: argument '%s' must be an integer.\n", arg_name);
	else if (code == ERR_NOT_STR)
		fprintf(stderr, "Error: argument '%s' must be a string.\n", arg_name);
	else if (code == ERR_NEGATIVE)
		fprintf(stderr,
			"Error: argument '%s' must be an positive integer.\n", arg_name);
	else if (code == ERR_OVERFLOW)
		fprintf(stderr,
			"Error: argument '%s' cannot exceed INT_MAX.\n", arg_name);
	else if (code == ERR_NOT_EDF_FIFO)
		fprintf(stderr,
			"Error: argument '%s' must be 'edf' or 'fifo'.\n", arg_name);
	free(arg_name);
	return (code);
}

char	*find_arg_name(int arg_idx)
{
	if (arg_idx == 1)
		return (ft_strdup("number_of_coders"));
	else if (arg_idx == 2)
		return (ft_strdup("time_to_burnout"));
	else if (arg_idx == 3)
		return (ft_strdup("time_to_compile"));
	else if (arg_idx == 4)
		return (ft_strdup("time_to_debug"));
	else if (arg_idx == 5)
		return (ft_strdup("time_to_refactor"));
	else if (arg_idx == 6)
		return (ft_strdup("number_of_compiles_required"));
	else if (arg_idx == 7)
		return (ft_strdup("dongle_cooldown"));
	else if (arg_idx == 8)
		return (ft_strdup("scheduler"));
	return (ft_strdup(""));
}

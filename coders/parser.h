/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrishero <chrishero@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 14:41:32 by chrishero         #+#    #+#             */
/*   Updated: 2026/04/16 14:41:33 by chrishero        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "utils.h"
# define TRUE 1
# define FALSE 0

typedef enum e_err
{
	ERR_ARGS_COUNT = 3,
	ERR_NOT_INT,
	ERR_NOT_STR,
	ERR_NEGATIVE,
	ERR_OVERFLOW,
	ERR_NOT_EDF_FIFO
}	t_err;

typedef struct s_args
{
	int		number_of_coders;
	int		time_to_burnout;
	int		time_to_compile;
	int		time_to_debug;
	int		time_to_refactor;
	int		number_of_compiles_required;
	int		dongle_cooldown;
	char	*scheduler;
}	t_args;

int		parser(int argc, char **argv);
int		exit_err(int code, int arg_idx);
char	*find_arg_name(int arg_idx);

#endif
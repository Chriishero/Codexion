/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chrishero <chrishero@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 14:40:43 by chrishero         #+#    #+#             */
/*   Updated: 2026/04/16 20:37:34 by chrishero        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H
# include "parser.h"

typedef struct s_coder	t_coder;

typedef enum e_dongle_state
{
	AVAILABLE = 1,
	USED,
	IN_COOLDOWN
}	t_dongle_state;

typedef enum e_coder_state
{
	INACTIVE = 0,
	TAKEN_DONGLE,
	COMPILING,
	DEBUGGING,
	REFACTORING,
	BURNOUT,
	FINISH
}	t_coder_state;

typedef struct s_queue
{
	t_coder			*coder;
	long int		deadline;
	struct s_queue	*next;
}	t_queue;

typedef struct s_dongle
{
	int				id;
	int				state;
	long int		cooldown;
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
	t_queue			*queue;
	struct s_dongle	*next;
}	t_dongle;

typedef struct s_coder
{
	int				id;
	int				state;
	int				n_compilation;
	long int		last_compile_start;
	pthread_mutex_t	mutex;	
	pthread_t		thread;
	t_dongle		*left;
	t_dongle		*right;
	struct s_coder	*next;
}	t_coder;

typedef struct s_simulation
{
	t_coder			*coders;
	t_dongle		*dongles;
	t_args			params;
	long int		start_time;
	int				state;
	pthread_mutex_t	state_mutex;
	pthread_mutex_t	logs_mutex;
	pthread_t		monitor;
}	t_simulation;

typedef struct s_thread_data
{
	t_simulation	*simulation;
	t_coder			*coder;
}	t_thread_data;

int				start_simulation(t_simulation *simulation);
void			stop_simulation(t_simulation *sim);
t_thread_data	*create_thread(t_simulation *sim);
void			join_thread(t_simulation *sim);
void			monitor(void *simulation_data);
void			update_dongles_state(t_dongle *dongle, t_simulation *sim);
int				stop_condition(t_simulation *simulation, t_coder *coder);
void			*coder_function(void *thread_data);
int				is_finish(t_simulation *simulation, t_coder *coder);
void			coding_routine(t_coder *coder, t_dongle *first_dongle,
					t_dongle *second_dongle, t_simulation *simulation);
void			coder_action(t_coder *coder, t_coder_state state,
					t_simulation *simulation);
int				take_dongle(t_coder *coder, t_dongle *dongle,
					t_simulation *sim);
void			release_dongle(t_dongle *dongle, t_simulation *sim);
int				take_dongle_condition(t_coder *coder, t_dongle *dongle);
void			add_coder(t_queue **queue, t_coder *coder,
					t_args params);
void			pop_coder(t_queue **queue);
void			swap_coders(t_queue **queue);
void			print_log(t_simulation *sim, t_coder *coder);
void			free_data(t_simulation *simulation);
void			free_dongle(t_dongle *dongle);
void			free_coder(t_coder *coder);
void			free_simulation(t_simulation *simulation);

#endif
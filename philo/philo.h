/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 15:30:10 by yehan             #+#    #+#             */
/*   Updated: 2022/09/14 11:10:57 by yehan            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>

/* for monitor threads */
# define MONITOR_CNT 2
# define DEATH 0
# define MUSTEAT 1

/* for print state */
typedef enum e_state_type
{
	FORK,
	EAT,
	SLEEP,
	THINK,
	DEAD
}	t_state_type;

/* milliseconds */
typedef long long							t_msec;

/* fork valuable */
typedef int									t_fork;

typedef struct s_condition_of_simulation	t_condition;

/** NOTE:
 * 1) the name of philosophers start from 1.
 * 2) start_time_of_last_meal: for monitoring death.
 * 3) number_of_times_eaten: for monitoring must-eat.
 * 4) left, right: pre-calculate own fork's indexs, just for convinence.
 * 5) condition: pointer of condition struct.
 */
typedef struct s_state_of_philosopher
{
	int			name;
	pthread_t	tid;
	t_msec		start_time_of_last_meal;
	int			number_of_times_eaten;
	size_t		left;
	size_t		right;
	t_condition	*condition;
}	t_philosopher;

/** NOTE:
 * 1) first 5 members are arguments got from user.
 * 2) start_time_of_simlutation: to get time passed.
 * 3) need_stop: 1) check if somebody dead, 2) prevent message mixing.
 * 4) fork: used while eating.
 * 5) philosopher: all structs of philosophers.
 * 6) monitor_tid: store monitor thread id.
 */
typedef struct s_condition_of_simulation
{
	int				number_of_philosophers;
	t_msec			time_to_die;
	t_msec			time_to_eat;
	t_msec			time_to_sleep;
	int				number_of_times_each_must_eat;
	t_msec			start_time_of_simlutation;
	bool			need_stop;
	pthread_mutex_t	*need_stop_lock;
	t_fork			*fork;
	pthread_mutex_t	*fork_lock;
	t_philosopher	*philosopher;
	pthread_t		*monitor_tid;
}	t_condition;

/* init.c */
bool	init_condition(t_condition *cond, int argc, char **argv);

/* init2.c */
bool	init_argument(t_condition *cond, int argc, char **argv);
bool	init_need_stop(t_condition *cond);
bool	init_forks(t_condition *cond);

/* philo.c */
void	create_philosophers(t_condition *cond);

/* philo2.c */
bool	take_forks(t_philosopher *self);
bool	eating(t_philosopher *self);
bool	sleeping(t_philosopher *self);
bool	thinking(t_philosopher *self);

/* monitor.c */
void	create_monitor_death(t_condition *cond);
void	create_monitor_must_eat(t_condition *cond);

/* free.c */
void	wait_threads(t_condition *cond);
void	free_forks(t_condition *cond);
void	free_need_stop(t_condition *cond);
void	free_all(t_condition *cond);

/* utils.c */
void	*ft_calloc(size_t count, size_t size);
t_msec	get_current_time(void);
bool	print_state(t_condition *cond, int name, t_state_type type);
void	usleep_precise(t_condition *cond, t_msec must_time);
bool	is_need_stop_true(t_condition *cond);

#endif /* PHILO_H */
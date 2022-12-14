/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 09:54:29 by yehan             #+#    #+#             */
/*   Updated: 2022/10/01 13:13:19 by yehan            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "philo_bonus.h"

void	take_forks(t_condition *cond)
{
	t_philosopher	*self;

	self = cond->self;
	sem_wait(cond->sem_forks);
	print_state(cond, self->name, FORK);
	if (cond->number_of_philosophers == 1)
	{
		sem_post(cond->sem_forks);
		usleep_precise(cond, cond->time_to_die * 2);
	}
	else
	{
		sem_wait(cond->sem_forks);
		print_state(cond, self->name, FORK);
	}
}

/** STEPS:
 * 1) print message.
 * 2) reset valuables about eating.
 * 3) sleep until 'time_to_eat'.
 * 4) put down forks.
 * */
void	eating(t_condition *cond)
{
	t_philosopher	*self;

	self = cond->self;
	print_state(cond, self->name, EAT);
	sem_wait(cond->last_meal_lock);
	self->start_time_of_last_meal = get_current_msec();
	sem_post(cond->last_meal_lock);
	usleep_precise(cond, cond->time_to_eat);
	self->number_of_times_eaten++;
	sem_post(cond->sem_forks);
	sem_post(cond->sem_forks);
	if (cond->number_of_times_each_must_eat > -1
		&& self->number_of_times_eaten \
			>= cond->number_of_times_each_must_eat)
		exit(EXIT_FULL);
}

void	sleeping(t_condition *cond)
{
	t_philosopher	*self;

	self = cond->self;
	print_state(cond, self->name, SLEEP);
	usleep_precise(cond, cond->time_to_sleep);
}

/** NOTE:
 * 1) Situations that require more than 'time_to_eat' time to think:
 * 1-1) When the number of philosophers is odd.
 * (Divide into 3 groups and compete)
 * 1-2) Sleeping less than eating.
 * (Wakes up too quickly and try to compete with a starving one)
*/
void	thinking(t_condition *cond)
{
	t_philosopher	*self;

	self = cond->self;
	print_state(cond, self->name, THINK);
	if (cond->number_of_philosophers % 2 \
		&& cond->time_to_eat >= cond->time_to_sleep)
		usleep_precise(cond, cond->time_to_eat);
}

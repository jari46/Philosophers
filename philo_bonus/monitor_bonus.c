/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: han-yeseul <han-yeseul@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 09:52:27 by yehan             #+#    #+#             */
/*   Updated: 2022/09/23 09:31:50 by han-yeseul       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "philo_bonus.h"

/** STEPS:
 * 1) check own's death.
 * NOTES:
 * 1) since this thread can be pushed to a lower priority
 * due to while statement, need to sleep for a while.
*/
static void	*death_routine(void *arg)
{
	t_condition		*cond;
	t_philosopher	*self;

	cond = (t_condition *)arg;
	self = cond->self;
	while (true)
	{
		sem_wait(cond->monitor_lock);
		if (get_current_msec() - self->start_time_of_last_meal \
			>= cond->time_to_die)
		{
			sem_post(cond->monitor_lock);
			print_state(cond, self->name, DIE);
			exit(EXIT_DIE);
		}
		sem_post(cond->monitor_lock);
		usleep(100);
	}
}

void	create_monitor(t_condition *cond)
{
	pthread_create(cond->self->monitor_tid, NULL, death_routine, cond);
}

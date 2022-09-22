/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: han-yeseul <han-yeseul@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 09:55:09 by yehan             #+#    #+#             */
/*   Updated: 2022/09/22 14:26:44 by han-yeseul       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "philo_bonus.h"

/** STEPS:
 * 1) first n philosophers could have chance to take a fork.
 * 2) this proccess will end up as
 * 2-1) own's full or death -> exit by own's thread.
 * 2-2) other's death -> killed by main proccess.
*/
static int	run_simulation(t_condition *cond)
{
	t_philosopher	*self;

	self = cond->self;
	create_monitor_self(cond);
	if (cond->number_of_philosophers / 2 < self->name)
		usleep(3000);
	while (1)
	{
		take_forks(cond);
		eating(cond);
		sleeping(cond);
		thinking(cond);
	}
}

void	create_philosophers(t_condition *cond)
{
	int				i;

	i = 0;
	while (i < cond->number_of_philosophers)
	{
		cond->self->name = i + 1;
		cond->philosopher_pid[i] = fork();
		if (cond->philosopher_pid[i] == CHILD)
			exit(run_simulation(cond));
		else
			i++;
	}
}

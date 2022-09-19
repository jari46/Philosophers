/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 15:37:54 by yehan             #+#    #+#             */
/*   Updated: 2022/09/19 10:29:32 by yehan            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "philo.h"

void	free_forks(t_condition *cond)
{
	int	i;

	free(cond->fork);
	i = 0;
	while (i < cond->number_of_philosophers)
	{
		pthread_mutex_destroy(&(cond->fork_lock[i]));
		i++;
	}
	free(cond->fork_lock);
}

void	free_need_stop(t_condition *cond)
{
	pthread_mutex_destroy(cond->need_stop_lock);
	free(cond->need_stop_lock);
}

void	wait_threads(t_condition *cond)
{
	int				i;
	t_philosopher	*philo;

	i = 0;
	while (i < cond->number_of_philosophers)
	{
		philo = &(cond->philosopher[i]);
		pthread_join(philo->tid, NULL);
		i++;
	}
	pthread_join(cond->monitor_tid[DEATH], NULL);
	if (cond->number_of_times_each_must_eat > -1)
		pthread_join(cond->monitor_tid[MUSTEAT], NULL);
}

void	free_all(t_condition *cond)
{
	free_need_stop(cond);
	free_forks(cond);
	free(cond->philosopher);
	free(cond->monitor_tid);
	free(cond);
}

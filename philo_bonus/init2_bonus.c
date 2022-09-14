/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 09:51:52 by yehan             #+#    #+#             */
/*   Updated: 2022/09/14 14:54:06 by yehan            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "philo_bonus.h"

static bool	init_number(int *buf, char *str)
{
	long long	num;
	int			i;

	num = 0;
	i = 0;
	while ('0' <= str[i] && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
	{
		printf("Error: arguments must be a number\n");
		return (false);
	}
	*buf = num;
	return (true);
}

static bool	init_msec(t_msec *buf, char *str)
{
	long long	num;
	int			i;

	num = 0;
	i = 0;
	while ('0' <= str[i] && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
	{
		printf("Error: arguments must be a number\n");
		return (false);
	}
	*buf = num;
	return (true);
}

/** NOTE:
 * 1) init_number() and init_msec() are different
 * just because they have different argument type.
 * 2) both doesn't handle overflow or underflow.
 */
bool	init_argument(t_condition *cond, int argc, char **argv)
{
	if (init_number(&(cond->number_of_philosophers), argv[1]) == false
		|| init_msec(&(cond->time_to_die), argv[2]) == false
		|| init_msec(&(cond->time_to_eat), argv[3]) == false
		|| init_msec(&(cond->time_to_sleep), argv[4]) == false)
		return (false);
	cond->number_of_times_each_must_eat = -1;
	if (argc == 6)
		if (init_number(&(cond->number_of_times_each_must_eat), argv[5])
			== false)
			return (false);
	return (true);
}

void	init_semaphores(t_condition *cond)
{
	int	i;

	cond->print_lock \
		= sem_open("print_lock", O_CREAT, 0644, 1);
	cond->fork_lock \
		= sem_open("fork_lock", O_CREAT, 0644, cond->number_of_philosophers);
	cond->full_lock \
		= sem_open("full_lock", O_CREAT, 0644, cond->number_of_philosophers);
	i = 0;
	while (i < cond->number_of_philosophers)
	{
		sem_wait(cond->full_lock);
		i++;
	}
}
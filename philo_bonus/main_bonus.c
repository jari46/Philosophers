/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 09:53:54 by yehan             #+#    #+#             */
/*   Updated: 2022/10/01 13:31:34 by yehan            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/errno.h>
#include "philo_bonus.h"

/** NOTE:
 * 1) visualizer: https://nafuka11.github.io/philosophers-visualizer/
 * 2) error control:
 * 2-1) only user-set errors print error message.
 * 2-2) semaphore-initiation errors are only detached.
*/
int	main(int argc, char **argv)
{
	t_condition	*cond;

	if (argc < 5 || 6 < argc)
	{
		printf("Error: the number of arguments must be 4 or 5\n");
		return (1);
	}
	cond = ft_calloc(1, sizeof(t_condition));
	if (init_condition(cond, argc, argv) == false)
	{
		free(cond);
		return (1);
	}
	create_philosopher(cond);
	wait_proccess(cond);
	free_all(cond);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkilic <hkilic@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:57:42 by hkilic            #+#    #+#             */
/*   Updated: 2022/12/30 17:35:47 by hkilic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

bool	init_mutex(t_simulation *sim)
{
	int	i;

	i = sim->philo_count;
	while (--i >= 0)
		if (pthread_mutex_init(&sim->forks[i], NULL))
			return (false);
	if (pthread_mutex_init(&sim->typing, NULL))
		return (false);
	return (true);
}

void	init_philosophers(t_simulation *sim)
{
	int	i;

	i = sim->philo_count;
	while (--i >= 0)
	{
		sim->philosophers[i].id = i;
		sim->philosophers[i].left_fork_id = i;
		sim->philosophers[i].right_fork_id = (i + 1) % sim->philo_count;
		sim->philosophers[i].sim = sim;
		sim->philosophers[i].last_eat = get_time();
		sim->philosophers[i].eat_count = 0;
	}
}

int	init_all(t_simulation *sim, char **argv)
{
	sim->philo_count = atoi(argv[1]);
	sim->die_time = atoi(argv[2]);
	sim->eat_time = atoi(argv[3]);
	sim->sleep_time = atoi(argv[4]);
	sim->all_eated = false;
	sim->died = false;
	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->philo_count);
	sim->philosophers = malloc(sizeof(t_philosopher) * sim->philo_count);
	if (argv[5])
		sim->nb_eat = atoi(argv[5]);
	else
		sim->nb_eat = -1;
	if (sim->philo_count <= 0 || sim->die_time <= 0
		||sim->eat_time <= 0 || sim->sleep_time <= 0)
	{
		printf("Wrong argument!");
		return (1);
	}
	if (!init_mutex(sim))
		if (print_error("mutex init error !") == 1)
			return (2);
	init_philosophers(sim);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkilic <hkilic@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:57:15 by hkilic            #+#    #+#             */
/*   Updated: 2022/12/30 17:34:43 by hkilic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	end_sim(t_simulation *sim, t_philosopher *phil)
{
	int	i;

	i = -1;
	while (++i < sim->philo_count)
		pthread_join(phil[i].thread_id, NULL);
	i = -1;
	while (++i < sim->philo_count)
		pthread_mutex_destroy(&sim->forks[i]);
	free (sim->forks);
	free (sim->philosophers);
	pthread_mutex_destroy(&sim->typing);
}

int	are_you_dead(t_simulation *sim, t_philosopher *p)
{
	int	i;

	while (!sim->all_eated)
	{
		i = -1;
		while (++i < sim->philo_count && !sim->died)
		{
			if (get_time() - p[i].last_eat > sim->die_time)
			{
				action_printer(sim, p[i].id, "died !");
				if (sim->philo_count == 1)
					return (1);
				sim->died = true;
			}
			usleep(100);
			if (sim->nb_eat != -1 && p[0].eat_count >= sim->nb_eat)
				sim->all_eated = true;
		}
		if (sim->died)
			break ;
	}
	return (0);
}

void	eat_bro(t_philosopher *phil)
{
	t_simulation	*s;

	s = phil->sim;
	pthread_mutex_lock(&s->forks[phil->left_fork_id]);
	action_printer(s, phil->id, "took the left fork");
	pthread_mutex_lock(&s->forks[phil->right_fork_id]);
	action_printer(s, phil->id, "took the right fork");
	action_printer(s, phil->id, "eating meat");
	phil->last_eat = get_time();
	phil->eat_count++;
	i_need_sleep(s->eat_time, s);
	pthread_mutex_unlock(&s->forks[phil->left_fork_id]);
	pthread_mutex_unlock(&s->forks[phil->right_fork_id]);
}

void	*thread(void *void_philo)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)void_philo;
	if (philo->id % 2 != 0)
		usleep(1000);
	while (!philo->sim->died)
	{
		eat_bro(philo);
		if (philo->sim->all_eated)
			break ;
		action_printer(philo->sim, philo->id, "sleeping");
		i_need_sleep(philo->sim->sleep_time, philo->sim);
		action_printer(philo->sim, philo->id, "thinking...");
	}
	return (NULL);
}

int	sim_start(t_simulation *sim)
{
	int				i;
	t_philosopher	*phil;

	phil = sim->philosophers;
	sim->start_time = get_time();
	i = 0;
	while (i < sim->philo_count)
	{
		pthread_create(&phil[i].thread_id, NULL, thread, &phil[i]);
		i++;
	}
	if (are_you_dead(sim, phil) == 1)
		return (1);
	end_sim(sim, phil);
	i = 0;
	return (0);
}

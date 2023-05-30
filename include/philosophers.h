/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkilic <hkilic@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:58:12 by hkilic            #+#    #+#             */
/*   Updated: 2022/12/30 17:35:31 by hkilic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <ctype.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>

# define CNRM  "\x1B[0m"
# define CRED  "\x1B[31m"
# define CGRN  "\x1B[32m"
# define CYEL  "\x1B[33m"
# define CBLU  "\x1B[34m"
# define CMAG  "\x1B[35m"
# define CCYN  "\x1B[36m"
# define CWHT  "\x1B[37m"

struct	s_simulation;

typedef struct s_philosopher
{
	int					id;
	int					left_fork_id;
	int					right_fork_id;
	long long			last_eat;
	int					eat_count;
	pthread_t			thread_id;
	struct s_simulation	*sim;
}		t_philosopher;

typedef struct s_simulation
{
	int				philo_count;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				nb_eat;
	bool			died;
	bool			all_eated;
	long long		start_time;
	pthread_mutex_t	typing;
	pthread_mutex_t	*forks;
	t_philosopher	*philosophers;
}		t_simulation;

int			init_all(t_simulation *sim, char **argv);
int			sim_start(t_simulation *sim);
long long	get_time(void);
void		action_printer(t_simulation *sim, int id, char *msg);
void		i_need_sleep(long long time, t_simulation *sim);
int			ft_atoi(char *ptr);
int			print_error(char *message);

#endif
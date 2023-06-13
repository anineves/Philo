/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asousa-n <asousa-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 12:27:37 by asousa-n          #+#    #+#             */
/*   Updated: 2023/05/06 12:27:39 by asousa-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>

//Strutures 
typedef struct s_data	t_data;
typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				meals_count;
	int				fork[2];
	pthread_mutex_t	eat_lock;
	time_t			last_meal;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	time_t			start_time;
	int				nbrs_philo;
	int				nbrs_forks;
	pthread_t		ft_control;
	time_t			time_die;
	time_t			time_eat;
	time_t			time_sleep;
	time_t			time_think;
	int				must_eat;
	bool			stop;
	pthread_mutex_t	sim_stop_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	*fork_locks;
	t_philo			**philo;
}	t_data;

//Funcions

int		ft_verific(char **argv);
int		ft_atoi(const char *str);
t_data	*ft_init_data(char **argv);
void	ft_start_simulation(t_data *data);
void	*ft_routine(void *data);
time_t	ft_get_time(void);
void	*handle_error(char *str, t_data *data);
void	ft_usleep(t_data *data, time_t sleep_time);
void	sim_start_delay(time_t start_time);
void	*ft_control(void *data);
bool	ft_data_stop(t_data *data);
void	*free_data(t_data *data);
void	destroy_mutexes(t_data *data);
void	ft_print(t_philo *philo, bool die, char *str);
void	stop_simulation(t_data	*data);

#endif

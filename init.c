/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asousa-n <asousa-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 12:28:09 by asousa-n          #+#    #+#             */
/*   Updated: 2023/05/06 16:07:20 by asousa-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*ft_init_forks(t_data *data)
{
	pthread_mutex_t		*forks;
	int					i;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * data->nbrs_forks);
	if (!forks)
		handle_error("malloc forks", data);
	while (i < data->nbrs_forks)
	{
		if (pthread_mutex_init(&forks[i], 0) != 0)
			handle_error("init mutex", data);
		i++;
	}
	return (forks);
}

void	ft_odd(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		philo->fork[0] = (philo->id + 1) % philo->data->nbrs_philo;
		philo->fork[1] = philo->id;
	}
}

static t_philo	**init_philosophers(t_data *data)
{
	t_philo	**philo;
	int		i;

	i = 0;
	philo = malloc(sizeof(t_philo) * data->nbrs_philo);
	if (!philo)
		handle_error("malloc philos", data);
	while (i < data->nbrs_philo)
	{
		philo[i] = malloc(sizeof(t_philo) * 1);
		if (pthread_mutex_init(&philo[i]->eat_lock, 0) != 0)
			handle_error("init mutex", data);
		philo[i]->data = data;
		philo[i]->id = i;
		philo[i]->meals_count = 0;
		philo[i]->last_meal = 0;
		philo[i]->fork[0] = philo[i]->id;
		philo[i]->fork[1] = (philo[i]->id + 1) % data->nbrs_philo;
		ft_odd(philo[i]);
		i++;
	}
	return (philo);
}

void	ft_init_mutex(t_data *data)
{
	if (pthread_mutex_init(&data->sim_stop_lock, 0) != 0)
	{
		destroy_mutexes(data);
		handle_error ("mutex init", data);
	}
	if (pthread_mutex_init(&data->write_lock, 0) != 0)
	{
		destroy_mutexes(data);
		handle_error("mutex init", data);
	}
}

t_data	*ft_init_data(char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->nbrs_philo = ft_atoi(argv[1]);
	data->nbrs_forks = ft_atoi(argv[1]);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	data->must_eat = -1;
	if (argv[5])
		data->must_eat = ft_atoi(argv[5]);
	if (data->must_eat == 0 || data->nbrs_philo == 0)
		return (handle_error ("number of philo and must_eat must be\
		higher than 0\n", data));
	if (data->time_die < 0)
		return (handle_error ("time_die must be a litle higher\n", data));
	data->philo = init_philosophers(data);
	data->fork_locks = ft_init_forks(data);
	ft_init_mutex(data);
	data->stop = false;
	return (data);
}

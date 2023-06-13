/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asousa-n <asousa-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 12:28:42 by asousa-n          #+#    #+#             */
/*   Updated: 2023/05/06 16:15:27 by asousa-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_think(t_philo *philo)
{
	time_t	time_to_think;

	pthread_mutex_lock(&philo->eat_lock);
	time_to_think = ((philo->data->time_die
				- (ft_get_time() - philo->last_meal)
				- philo->data->time_eat) / 2);
	if (time_to_think < 0)
		time_to_think = 0;
	pthread_mutex_unlock(&philo->eat_lock);
	ft_print(philo, false, "is thinking 🧘");
	ft_usleep(philo->data, time_to_think);
}

static void	ft_eat_sleep(t_philo *philo)
{
	ft_print(philo, false, "is eating 🍝");
	pthread_mutex_lock(&philo->eat_lock);
	philo->last_meal = ft_get_time();
	pthread_mutex_unlock(&philo->eat_lock);
	ft_usleep(philo->data, philo->data->time_eat);
	if (ft_data_stop(philo->data) == false)
	{
		pthread_mutex_lock(&philo->eat_lock);
		philo->meals_count += 1;
		pthread_mutex_unlock(&philo->eat_lock);
	}
	ft_print(philo, false, "is sleeping 😴");
	pthread_mutex_unlock(&philo->data->fork_locks[philo->fork[1]]);
	pthread_mutex_unlock(&philo->data->fork_locks[philo->fork[0]]);
	ft_usleep(philo->data, philo->data->time_sleep);
}

static void	ft_take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->fork_locks[philo->fork[0]]);
	ft_print(philo, false, "has taken a fork 🍴");
	pthread_mutex_lock(&philo->data->fork_locks[philo->fork[1]]);
	ft_print(philo, false, "has taken a fork 🍴");
}

void	*ft_just_one(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->fork_locks[philo->fork[0]]);
	ft_print(philo, false, "has taken a fork 🍴");
	ft_usleep(philo->data, philo->data->time_die);
	ft_print(philo, false, "died");
	pthread_mutex_unlock(&philo->data->fork_locks[philo->fork[0]]);
	return (NULL);
}

void	*ft_routine(void *info)
{
	t_philo	*philo;

	philo = (t_philo *)info;
	pthread_mutex_lock(&philo->eat_lock);
	philo->last_meal = philo->data->start_time;
	pthread_mutex_unlock(&philo->eat_lock);
	if (philo->data->nbrs_philo == 1)
		return (ft_just_one(philo));
	while (1)
	{
		if (ft_data_stop(philo->data) == true)
			break ;
		ft_take_forks(philo);
		ft_eat_sleep(philo);
		ft_think(philo);
	}
	return (NULL);
}

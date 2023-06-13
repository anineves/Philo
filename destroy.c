/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asousa-n <asousa-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 12:27:59 by asousa-n          #+#    #+#             */
/*   Updated: 2023/05/06 16:19:08 by asousa-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*handle_error(char *str, t_data *data)
{
	free_data(data);
	printf("Error %s", str);
	return (NULL);
}

void	*free_data(t_data *data)
{
	int	i;

	i = 0;
	if (!data)
		return (NULL);
	if (data->fork_locks != NULL)
		free(data->fork_locks);
	if (data->philo != NULL)
	{
		while (i < data->nbrs_philo)
		{
			if (data->philo[i] != NULL)
				free(data->philo[i]);
			i++;
		}
		free(data->philo);
	}
	free(data);
	return (NULL);
}

void	destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbrs_forks)
	{
		pthread_mutex_destroy(&data->fork_locks[i]);
		pthread_mutex_destroy(&data->philo[i]->eat_lock);
		i++;
	}
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->sim_stop_lock);
}

void	stop_simulation(t_data	*data)
{
	int	i;

	i = 0;
	while (i < data->nbrs_philo)
	{
		pthread_join(data->philo[i]->thread, NULL);
		i++;
	}
	if (data->nbrs_philo > 1)
		pthread_join(data->ft_control, NULL);
	destroy_mutexes(data);
	free_data(data);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asousa-n <asousa-n@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 12:28:50 by asousa-n          #+#    #+#             */
/*   Updated: 2023/05/06 13:09:57 by asousa-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print(t_philo *philo, bool die, char *str)
{
	pthread_mutex_lock(&philo->data->write_lock);
	if (ft_data_stop(philo->data) == true && die == false)
	{
		pthread_mutex_unlock(&philo->data->write_lock);
		return ;
	}
	printf("%ld %d %s\n", ft_get_time() - philo->data->start_time,
		philo->id + 1, str);
	pthread_mutex_unlock(&philo->data->write_lock);
}

bool	ft_data_stop(t_data *data)
{
	bool	stop;

	stop = false;
	pthread_mutex_lock(&data->sim_stop_lock);
	if (data->stop == true)
		stop = true;
	pthread_mutex_unlock(&data->sim_stop_lock);
	return (stop);
}

void	ft_usleep(t_data *data, time_t sleep_time)
{
	time_t	sleep;

	sleep = ft_get_time() + sleep_time;
	while (ft_get_time() <= sleep)
	{
		if (ft_data_stop(data))
			break ;
		usleep(20);
	}
}

/* struct    timeval  {
  time_t        tv_sec ;   //used for seconds
  suseconds_t       tv_usec ;   //used for microseconds
} */
time_t	ft_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

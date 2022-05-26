/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarci <sdarci@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 20:00:15 by sdarci            #+#    #+#             */
/*   Updated: 2022/05/18 21:35:28 by sdarci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_usleep(int ms)
{
	unsigned long long		start;
	unsigned long long		now;

	if (get_time_ms(&start) || get_time_ms(&now))
		return (1);
	while ((now - start) < (unsigned long long)ms)
	{
		usleep(100);
		if (get_time_ms(&now))
			return (1);
	}
	return (0);
}

int	ft_print(t_phil *phil, char *str)
{
	unsigned long long	time_from_start;

	pthread_mutex_lock(&(phil->ptr_data->mutex_end));
	pthread_mutex_lock(&(phil->ptr_data->mutex_all_have_eaten));
	if ((phil->ptr_data->end == -1) && \
		(phil->ptr_data->all_have_eaten != phil->ptr_data->total_phil))
	{
		if (stamp(phil, &time_from_start))
			return (1);
		pthread_mutex_lock(&(phil->ptr_data->mutex_print));
		printf("%llu %d %s\n", time_from_start, phil->num_phil, str);
		pthread_mutex_unlock(&(phil->ptr_data->mutex_print));
	}
	pthread_mutex_unlock(&(phil->ptr_data->mutex_all_have_eaten));
	pthread_mutex_unlock(&(phil->ptr_data->mutex_end));
	return (0);
}

static int	eating(t_phil *phil, int first_fork, int second_fork)
{
	pthread_mutex_lock(&(phil->ptr_data->mutex_forks[first_fork]));
	if (ft_print(phil, "has taken a fork"))
		return (1);
	if (phil->ptr_data->total_phil == 1)
	{
		ft_one_philo(phil, first_fork);
		return (1);
	}
	pthread_mutex_lock(&(phil->ptr_data->mutex_forks[second_fork]));
	if (ft_print(phil, "has taken a fork"))
		return (1);
	if (ft_print(phil, "is eating"))
		return (1);
	pthread_mutex_lock(&(phil->ptr_data->mutex_time));
	if (get_time_ms(&(phil->last_meal_ms)))
		return (1);
	pthread_mutex_unlock(&(phil->ptr_data->mutex_time));
	phil->num_eat++;
	if (ft_usleep(phil->time_to_eat))
		return (1);
	pthread_mutex_unlock(&(phil->ptr_data->mutex_forks[second_fork]));
	pthread_mutex_unlock(&(phil->ptr_data->mutex_forks[first_fork]));
	return (0);
}

static int	check_and_eat(t_phil *phil)
{
	if (eating(phil, phil->num_right_fork, phil->num_left_fork))
		return (1);
	if (phil->num_eat == phil->ptr_data->total_eat)
	{
		pthread_mutex_lock(&(phil->ptr_data->mutex_all_have_eaten));
		phil->ptr_data->all_have_eaten++;
		if (phil->ptr_data->all_have_eaten == phil->ptr_data->total_phil)
		{
			pthread_mutex_unlock(&(phil->ptr_data->mutex_all_have_eaten));
			return (1);
		}
		pthread_mutex_unlock(&(phil->ptr_data->mutex_all_have_eaten));
	}
	return (0);
}

void	*phil_life(void *phil)
{
	t_phil	*phi;

	phi = &(*(t_phil *)phil);
	if (phi->num_phil % 2 == 0)
		usleep(150);
	while (1)
	{		
		pthread_mutex_lock(&(phi->ptr_data->mutex_end));
		if (phi->ptr_data->end)
		{
			pthread_mutex_unlock(&(phi->ptr_data->mutex_end));
			if (check_and_eat(phi))
				return (NULL);
			if (ft_print(phil, "is sleeping"))
				return (NULL);
			if (ft_usleep(phi->time_to_sleep) || \
				ft_print(phil, "is thinking"))
				return (NULL);
		}
		else
		{
			pthread_mutex_unlock(&(phi->ptr_data->mutex_end));
			return (NULL);
		}
	}
}

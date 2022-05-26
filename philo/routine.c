/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarci <sdarci@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 20:00:46 by sdarci            #+#    #+#             */
/*   Updated: 2022/05/18 21:35:26 by sdarci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_structs(int **args, t_data *data)
{
	data->total_phil = (*args)[0];
	data->time_to_die = (*args)[1];
	data->total_eat = (*args)[4];
	data->end = -1;
	data->phil = malloc (sizeof(t_phil) * data->total_phil);
	if (!data->phil)
		return (print_error("Malloc error!\n"));
	if (get_time_ms(&(data->start_ms)))
		return (1);
	data->all_have_eaten = 0;
	init_phil_structs(args, data);
	return (0);
}

unsigned long long	stamp(t_phil *phil, unsigned long long	*time_from_start)
{
	unsigned long long	now_ms;

	if (get_time_ms(&now_ms))
		return (1);
	*time_from_start = now_ms - phil->ptr_data->start_ms;
	return (0);
}

static int	check_all_have_eaten(t_data *data)
{
	pthread_mutex_lock(&(data->mutex_all_have_eaten));
	if (data->all_have_eaten == data->total_phil)
	{
		pthread_mutex_unlock(&(data->mutex_all_have_eaten));
		pthread_mutex_lock(&(data->mutex_end));
		data->end = 0;
		pthread_mutex_unlock(&(data->mutex_end));
		return (1);
	}
	else
		pthread_mutex_unlock(&(data->mutex_all_have_eaten));
	return (0);
}

static int	check_time_to_die(t_data *data, int i)
{
	unsigned long long	now_ms;
	unsigned long long	time_from_start;

	if (get_time_ms(&now_ms))
		return (1);
	pthread_mutex_lock(&(data->mutex_time));
	if ((now_ms - data->phil[i].last_meal_ms) > \
		((unsigned long long)data->time_to_die))
	{
		pthread_mutex_unlock(&(data->mutex_time));
		pthread_mutex_lock(&(data->mutex_end));
		data->end = 0;
		pthread_mutex_unlock(&(data->mutex_end));
		if (stamp(&(data->phil[i]), &time_from_start))
			return (1);
		pthread_mutex_lock(&(data->mutex_print));
		printf("%llu %d died\n", time_from_start, data->phil[i].num_phil);
		pthread_mutex_unlock(&(data->mutex_print));
		return (1);
	}
	else
		pthread_mutex_unlock(&(data->mutex_time));
	return (0);
}

void	*check_death(void *data)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < ((t_data *)data)->total_phil)
		{
			if (check_all_have_eaten((t_data *)data))
				return (NULL);
			if (check_time_to_die((t_data *)data, i))
				return (NULL);
			i++;
		}
	}
}

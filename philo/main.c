/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarci <sdarci@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 20:34:29 by sdarci            #+#    #+#             */
/*   Updated: 2022/05/18 21:51:33 by sdarci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time_ms(unsigned long long *time_ms)
{
	struct timeval		time;

	if (gettimeofday(&time, NULL) != 0)
		return (print_error("gettimeofday error!\n"));
	*time_ms = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (0);
}

int	print_error(char *str)
{
	printf("%s", str);
	return (1);
}

static int	init_threads(t_data *data, pthread_t **th, pthread_t *supervisor)
{
	int	i;

	*th = malloc(sizeof(pthread_t) * data->total_phil);
	if (!(*th))
		return (print_error("Malloc error!\n"));
	pthread_mutex_init(&(data->mutex_print), NULL);
	pthread_mutex_init(&(data->mutex_time), NULL);
	pthread_mutex_init(&(data->mutex_end), NULL);
	pthread_mutex_init(&(data->mutex_all_have_eaten), NULL);
	data->mutex_forks = malloc(sizeof(pthread_mutex_t) * data->total_phil);
	if (!(data->mutex_forks))
		return (print_error("Malloc error!\n"));
	i = 0;
	while (i < data->total_phil)
		pthread_mutex_init(&(data->mutex_forks[i++]), NULL);
	i = 0;
	while (i < data->total_phil)
	{
		if (pthread_create(*(th) + i, NULL, &phil_life, &(data->phil[i])) != 0)
			return (print_error("Failed to create thread!\n"));
		i++;
	}
	if (pthread_create(supervisor, NULL, &check_death, data) != 0)
		return (print_error("Failed to create thread!\n"));
	return (0);
}

static int	join_threads(t_data *data, pthread_t **th, pthread_t *supervisor)
{
	int	i;

	if (pthread_join(*supervisor, NULL) != 0)
		return (print_error("Failed to join thread!\n"));
	i = 0;
	while (i < data->total_phil)
	{
		if (pthread_join((*th)[i], (void **) &(data->phil[i])) != 0)
			return (print_error("Failed to join thread!\n"));
		i++;
	}
	pthread_mutex_destroy(&(data->mutex_print));
	pthread_mutex_destroy(&(data->mutex_time));
	pthread_mutex_destroy(&(data->mutex_end));
	pthread_mutex_destroy(&(data->mutex_all_have_eaten));
	i = 0;
	while (i < data->total_phil)
		pthread_mutex_destroy(&(data->mutex_forks[i++]));
	free(*th);
	free(data->phil);
	free(data->mutex_forks);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	*philosophers;
	pthread_t	supervisor;

	if (input(argc, argv, &data))
		return (1);
	if (init_threads(&data, &philosophers, &supervisor))
		return (1);
	if (join_threads(&data, &philosophers, &supervisor))
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarci <sdarci@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 21:10:37 by sdarci            #+#    #+#             */
/*   Updated: 2022/05/19 14:46:08 by sdarci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_one_philo(t_phil *phil, int first_fork)
{
	pthread_mutex_lock(&(phil->ptr_data->mutex_end));
	phil->ptr_data->end = 0;
	pthread_mutex_unlock(&(phil->ptr_data->mutex_end));
	pthread_mutex_unlock(&(phil->ptr_data->mutex_forks[first_fork]));
	return ;
}

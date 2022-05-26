/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarci <sdarci@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 19:59:24 by sdarci            #+#    #+#             */
/*   Updated: 2022/05/18 21:35:23 by sdarci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

struct	s_data;

typedef struct s_phil
{
	int					num_phil;
	int					total_phil;
	int					time_to_eat;
	int					time_to_sleep;
	int					num_eat;
	int					num_left_fork;
	int					num_right_fork;
	unsigned long long	last_meal_ms;
	struct s_data		*ptr_data;
}	t_phil;

typedef struct s_data
{
	int					total_phil;
	int					time_to_die;
	int					total_eat;
	int					all_have_eaten;
	int					end;
	unsigned long long	start_ms;
	pthread_mutex_t		mutex_print;
	pthread_mutex_t		mutex_time;
	pthread_mutex_t		mutex_end;
	pthread_mutex_t		mutex_all_have_eaten;
	pthread_mutex_t		*mutex_forks;
	t_phil				*phil;
}	t_data;

void				*phil_life(void *phil);
void				*check_death(void *data);
void				init_phil_structs(int **args, t_data *data);
int					input(int argc, char **argv, t_data *data);
int					print_error(char *str);
int					ft_print(t_phil *phil, char *str);
int					get_time_ms(unsigned long long *time_ms);
int					init_structs(int **args, t_data *data);
unsigned long long	stamp(t_phil *phil, unsigned long long	*time_from_start);
void				ft_one_philo(t_phil *phil, int first_phork);

#endif
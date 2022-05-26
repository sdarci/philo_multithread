/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdarci <sdarci@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 21:09:58 by sdarci            #+#    #+#             */
/*   Updated: 2022/05/18 21:45:56 by sdarci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_digits_integer(const char *str)
{
	int	i;
	int	num_digits;

	i = 0;
	num_digits = 0;
	while (str[i] == '0')
		i++;
	while (str[i])
	{
		if (!((str[i] >= 48) && (str[i] <= 57)))
			return (1);
		num_digits++;
		i++;
	}
	if (num_digits > 10)
		return (1);
	return (0);
}

static int	ft_atoi_phil(const char *str)
{
	int					i;
	int					min;
	unsigned long long	nb;

	min = 1;
	i = 0;
	nb = 0;
	if (check_digits_integer(str))
		return (-1);
	while ((str[i] == ' ') || (str[i] > 8 && str[i] < 14))
		i++;
	if (str[i] == '-')
		min = -1;
	if ((str[i] == '+') || (str[i] == '-') || str[i] == '0')
		i++;
	while ((str[i] >= '0') && (str[i] <= '9') && (str[i] != '\0'))
		nb = nb * 10 + str[i++] - '0';
	if (((nb > 2147483647) && (min == 1)) || ((min == -1) && (nb > 2147483648)))
		return (-1);
	return (min * (int)nb);
}

void	init_phil_structs(int **args, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->total_phil)
	{
		data->phil[i].num_phil = i + 1;
		data->phil[i].total_phil = (*args)[0];
		data->phil[i].time_to_eat = (*args)[2];
		data->phil[i].time_to_sleep = (*args)[3];
		data->phil[i].num_eat = 0;
		data->phil[i].last_meal_ms = data->start_ms;
		data->phil[i].ptr_data = data;
		if (i == 0)
			data->phil[i].num_left_fork = data->phil[i].total_phil - 1;
		else
			data->phil[i].num_left_fork = i - 1;
		data->phil[i].num_right_fork = i;
		i++;
	}
}

static int	atoi_input(char **argv, int **args)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		(*args)[i - 1] = ft_atoi_phil(argv[i]);
		if ((*args)[i++ - 1] <= 0)
			return (print_error("Input error!\n"));
	}
	if (i != 6)
		(*args)[i - 1] = -1;
	return (0);
}

int	input(int argc, char **argv, t_data *data)
{
	int	*args;

	args = malloc(sizeof(int) * 5);
	if (!args)
		return (print_error("Malloc error!\n"));
	if (!((argc == 5) || (argc == 6)))
	{
		free(args);
		return (print_error("Number of arguments must be 4 or 5!\n"));
	}
	else
		if (atoi_input(argv, &args))
			return (1);
	if (init_structs(&args, data))
		return (1);
	free(args);
	return (0);
}

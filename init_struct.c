/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 10:20:50 by strieste          #+#    #+#             */
/*   Updated: 2026/01/06 17:19:41 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(int ac, char **av, t_data *data)
{
	if (check_input(ac, av))
		return (1);
	if (taking_args(ac, av, data))
		return (1);
	data->forks = malloc(data->nb_philo * sizeof(pthread_mutex_t));
	if (!data->forks)
		return (printf("Error malloc\n"), 1);
	data->philos = malloc(data->nb_philo * sizeof(t_philo));
	if (!data->philos)
		return (free(data->forks), printf("Error malloc\n"), 1);
	if (init_mutex(data))
		return (printf("Error init mutex\n"), free_data(data), 1);
	init_philos_struct(data);
	return (0);
}

int	init_mutex(t_data *data)
{
	int index;
	
	index = 0;
	while (index < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[index], NULL) != 0)
			return (destroy_mutex_loop(data, index), 1);
		index++;
	}
	if (pthread_mutex_init(&data->write, NULL) != 0)
	{
		destroy_mutex_loop(data, data->nb_philo);
		return (1);
	}
	if (pthread_mutex_init(&data->die, NULL) != 0)
	{
		destroy_mutex_loop(data, data->nb_philo);
		pthread_mutex_destroy(&data->write);
		return (1);
	}
	return (0);
}

int	init_philos_struct(t_data *data)
{
	int				index;
	int				count;

	index = 0;
	while (index < data->nb_philo)
	{
		if (init_philo(&data->philos[index], index, data))
		{
			count = 0;
			while (count < index)
				pthread_mutex_destroy(&data->philos[count++].meal_mutex);
			return (1);
		}
		index++;
	}
	return (0);
}

int	init_philo(t_philo *philos, int numbers, t_data *data)
{
	philos->id = numbers;
	philos->l_fork = numbers;
	philos->r_fork = (numbers + 1) % data->nb_philo;
	philos->last_meal = 0;
	philos->nb_meal = 0;
	philos->data = data;
	if (pthread_mutex_init(&philos->meal_mutex, NULL) != 0)
		return (printf("Error init mutex\n"), 1);
	return (0);
}

int	taking_args(int ac, char **av, t_data *data)
{
	data->nb_philo = ft_atoi(av[1]);
	if (data->nb_philo < 1 || !data->nb_philo)
		return (printf("Number of philo less than 1\n"), 1);
	data->time_die = ft_atoi(av[2]);
	if (data->time_die < 0 || !data->time_die)
		return (printf("Time die without eating less than 1\n"), 1);
	data->time_eat = ft_atoi(av[3]);
	if (data->time_eat < 0 || !data->time_eat)
		return (printf("Time for eat Invalid input\n"), 1);
	data->time_sleep = ft_atoi(av[4]);
	if (data->time_sleep < 0 || !data->time_sleep)
		return (printf("Time take to sleep less than 1\n"), 1);
	if (ac == 6)
	{
		data->must_eat = ft_atoi(av[5]);
		if (data->must_eat < 0 || !data->must_eat)
			return (printf("Number of time need eat less than 1\n"), 1);
	}
	else if (ac == 5)
		data->must_eat = -1;
	return (0);
}

int	check_input(int ac, char **av)
{
	size_t	len;
	size_t	count;

	len = 1;
	while (len < ac)
	{
		count = 0;
		if (av[len][count] == '+')
			count++;
		if (av[len][count] == '+')
			return (printf("No two '+'\n"), 1);
		if (av[len][count] == '-')
			return (printf("No negative numbers\n"), 1);
		while (av[len][count])
		{
			if (!ft_isdigit(av[len][count]))
				return (printf("Function take only digit\n"), 1);
			count++;
		}
		len++;
	}
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	check_arg_number(int ac, char **av)
{
	size_t	count;

	count = 0;
	while (ac)
	{
		count = 0;
		while (av[ac][count])
		{
			if (av[ac][count] < '0' || av[ac][count] > '9')
				return (1);
			count++;
		}
		ac--;
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	i;
	int	result;

	sign = 1;
	i = 0;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - 48);
		i++;
	}
	return (result * sign);
}

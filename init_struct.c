/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 10:20:50 by strieste          #+#    #+#             */
/*   Updated: 2025/12/02 08:20:30 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_clean(t_data *philo)
{
	philo->philosophe = 0;
	philo->number_philo = 0;
	philo->id = 1;
	philo->time_sleep = 0;
	philo->time_die = 0;
	philo->time_eat = 0;
	philo->must_eat = 0;
}

int	check_argument(int ac, char **av, t_data *philo)
{
	philo->number_philo = ft_atoi(av[1]);
	if (philo->number_philo < 1 || !philo->number_philo)
		return (printf("Number of philo less than 1\n"), 1);
	philo->time_die = ft_atoi(av[2]);
	if (philo->time_die < 0 || !philo->time_die)
		return (printf("Time die without eating less than 1\n"), 1);
	philo->time_eat = ft_atoi(av[3]);
	if (philo->time_eat < 0 || !philo->time_eat)
		return (printf("Time for eat Invalid input\n"), 1);
	philo->time_sleep = ft_atoi(av[4]);
	if (philo->time_sleep < 0 || !philo->time_sleep)
		return (printf("Time take to sleep less than 1\n"), 1);
	if (ac == 5)
	{
		philo->must_eat = ft_atoi(av[5]);
		if (philo->must_eat < 0 || !philo->must_eat)
			return (printf("Number of time need eat less than 1\n"), 1);
	}
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

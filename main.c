/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 13:53:56 by strieste          #+#    #+#             */
/*   Updated: 2025/12/01 15:15:21 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *);

int	main(int ac, char **av)
{
	t_philo		philo;

	pthread_create((&philo).philo, NULL, &routine, &philo);
	(void)ac;
	(void)av;
	pthread_join(philo.philo[0], NULL);
	// ac--;
	// if (ac > 5 || ac < 4)
	// 	return (printf("Error invalide input\n"), 1);
	// set_clean(&philo);
	// if (check_arg_number(ac, av))
	// 	return (printf("Input non numeric number"), 1);
	// if (check_argument(ac, av, &philo))
	// 	return (1);
	// printf("Number of philo: %d\n", philo.number);
	// printf("Time to die: %d\n", philo.time_die);
	// printf("Time to eat: %d\n", philo.time_eat);
	// printf("Time to sleep: %d\n", philo.time_sleep);
	// printf("Number eating: %d\n", philo.must_eat);
	return (0);
}

void	*routine(void *data)
{
	size_t	count;
	t_philo	*philo;

	count = 0;
	philo = (t_philo *)data;
	while (count < 5)
		printf("%sHello from threadId:%d number_philo %ld %s\n", BYELLOW, philo->number, count++, NC);
	printf("##################################\n");
	return (NULL);
}

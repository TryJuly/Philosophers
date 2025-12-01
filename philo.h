/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 13:53:10 by strieste          #+#    #+#             */
/*   Updated: 2025/12/01 15:13:07 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>

# define NC "\e[0m"
# define YELLOW "\e[33m"
# define BYELLOW "\e[1;33m"
# define RED "\e[31m"
# define GREEN "\e[32m"

typedef struct s_philo
{
	pthread_t	**philo;
	int			number;
	int 		time_sleep;
	int			time_die;
	int			time_eat;
	int			must_eat;
	pthread_mutex_t	r_fork;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	die;
	pthread_mutex_t	write;
	
}		t_philo;

/*		Init Struct			*/

void	set_clean(t_philo *philo);
int		check_arg_number(int ac, char **av);
int		check_argument(int ac, char **av, t_philo *philo);

int	ft_atoi(const char *str);

#endif
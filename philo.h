/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 13:53:10 by strieste          #+#    #+#             */
/*   Updated: 2026/01/06 17:18:23 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>

# define NC "\e[0m"
# define YELLOW "\e[33m"
# define BYELLOW "\e[1;33m"
# define RED "\e[31m"
# define BYRED "\e[1;31m"
# define GREEN "\e[32m"
# define LGREEN "\e[102m"
# define BLUE "\e[34m"

typedef struct	s_philo t_philo;

typedef struct s_data
{
	int				nb_philo;
	int 			time_sleep;
	int				time_die;
	int				time_eat;
	int				must_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	pthread_mutex_t	die;
	t_philo			*philos;
	
}	t_data;

typedef struct	s_philo
{
	int				id;
	int				l_fork;
	int				r_fork;
	long			last_meal;
	int				nb_meal;
	pthread_mutex_t	meal_mutex;
	pthread_t		thread;
	t_data			*data;
}	t_philo;

/*		Init Struct				*/

int		check_input(int ac, char **av);
void	init_philos_struct(t_data *data);
int		check_arg_number(int ac, char **av);
int		init_data(int ac, char **av, t_data *philo);

/*		Error function			*/

void	error_input(void);

/*		Clean					*/

void	free_data(t_data *data);
void	destroy_mutex_loop(t_data *data, int numbers);

int	ft_atoi(const char *str);

#endif
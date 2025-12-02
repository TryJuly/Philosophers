/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 13:53:10 by strieste          #+#    #+#             */
/*   Updated: 2025/12/02 10:59:22 by strieste         ###   ########.fr       */
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

typedef struct s_data
{
	pthread_t		*philosophe;
	pthread_mutex_t	lock_philo;
	int				number_philo;
	int				id;
	int 			time_sleep;
	int				time_die;
	int				time_eat;
	int				must_eat;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	write;
	pthread_mutex_t	eat;
	pthread_mutex_t	die;
	
}		t_data;

/*		Init Struct			*/

void	set_clean(t_data *philo);
int		check_arg_number(int ac, char **av);
int		check_argument(int ac, char **av, t_data *philo);

int	ft_atoi(const char *str);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 13:53:10 by strieste          #+#    #+#             */
/*   Updated: 2026/01/13 14:12:59 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

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
	long			time;
	int				error;
	int				one_dead;
	int				stop;
	pthread_mutex_t	error_check;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	pthread_mutex_t	die;
	pthread_t		monitor;
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

/*		Init Struct					*/

int		check_input(int ac, char **av);
int		check_arg_number(int ac, char **av);
int		init_data(int ac, char **av, t_data *philo);

/*		Philo function				*/

int		eat(t_philo *p);
void	*routine(void *data);
int		check_dead(t_data *p);
int		join_philo(t_data *data);
int		launch_philo(t_data *data);

/*		Monitor						*/

int		creat_monitor(t_data *data);

/*		Error / Clean				*/

void	error_input(void);
void	p_error(char *str);
void	free_data(t_data *data);
void	destroy_mutex_data(t_data *data);
void	destroy_mutex_philo(t_data *data);
void	destroy_mutex_loop(t_data *data, int numbers);

/*		Utils						*/

long	get_time(void);
int		ft_isdigit(int c);
int		ft_atoi(const char *str);
int		check_arg_number(int ac, char **av);
void    smart_sleep(long time_ms, t_data *data);

#endif
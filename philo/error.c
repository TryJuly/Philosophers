/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 12:12:34 by strieste          #+#    #+#             */
/*   Updated: 2026/01/14 12:45:22 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_input(void)
{
	printf("%sError input do like this:%s\n", RED, NC);
	printf("%s1%s: Program name, ", GREEN, NC);
	printf("%s2%s: Number of philo, ", GREEN, NC);
	printf("%s3%s: Time to die, ", GREEN, NC);
	printf("%s4%s: Time to eat, ", GREEN, NC);
	printf("%s5%s: Time to sleep, ", GREEN, NC);
	printf("%s6%s: %s(Optional)%s Number must eat\n", GREEN, NC, RED, NC);
}

void	p_error(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
	return ;
}

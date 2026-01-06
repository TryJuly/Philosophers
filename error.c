/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: strieste <strieste@student.42.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 12:12:34 by strieste          #+#    #+#             */
/*   Updated: 2026/01/06 12:18:14 by strieste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_input(void)
{
	printf("%sError argument programme%s\n", RED, NC);
	printf("%sFirst%s: Numbers of philo, ", GREEN, NC);
	printf("%sSeconde%s: Time to die, ", GREEN, NC);
	printf("%sThrid%s: Time to eat, ", GREEN, NC);
	printf("%sFourth%s: Time to sleep, ", GREEN, NC);
	printf("%sFifth%s: Number of time must eat (Optional)\n", GREEN, NC);
}
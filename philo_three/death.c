/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssnowbir <ssnowbir@student.21.ru>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 18:03:59 by ssnowbir          #+#    #+#             */
/*   Updated: 2021/01/13 15:53:15 by ssnowbir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int						ft_strlen(char *str)
{
	int					i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void					print_die(t_all *all, long long int start)
{
	sem_wait(all->table->sem_print);
	ft_putnbr_fd(start, 1);
	write(1, "ms ", 3);
	all->death = 1;
	ft_putnbr_fd(all->philo->name, 1);
	write(1, " died\n", 6);
	pthread_detach(all->philo->philo);
}

void					*phil_die(void *args)
{
	long long int		start;
	t_all				*all;

	all = (t_all *)args;
	while (1)
	{
		start = get_time(all);
		if ((start - all->philo->start) > all->info->death
									|| all->full_feed == 1)
		{
			if (all->full_feed == 0)
			{
				print_die(all, start);
				exit(1);
			}
			else if (all->full_feed == 1)
			{
				pthread_detach(all->philo->philo);
				exit(2);
			}
		}
		usleep(20);
	}
	return (NULL);
}

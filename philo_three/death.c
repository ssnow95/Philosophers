/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssnowbir <ssnowbir@student.21.ru>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 18:03:59 by ssnowbir          #+#    #+#             */
/*   Updated: 2021/01/12 20:27:43 by ssnowbir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
        i++;
    return (i);
}

void *phil_die(void *args)
{
    unsigned int i;
    long long int start;
    
	t_all *all = (t_all *)args;
    while (1)
    {
		start = get_time(all);
		if ((start - all->philo->start) > all->info->death || all->full_feed == 1)
		{
			if (all->full_feed == 0)
			{
				sem_wait(all->table->sem_print);
				ft_putnbr_fd(start, 1);
				write(1, "ms ", 3);
				all->death = 1;
				write(1, all[i].philo->name2, 1);
				write(1, " died\n", 6);
				pthread_detach(all->philo->philo);
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

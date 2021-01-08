/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssnowbir <ssnowbir@student.21.ru>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 18:03:59 by ssnowbir          #+#    #+#             */
/*   Updated: 2021/01/08 18:34:35 by ssnowbir         ###   ########.fr       */
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

int check_phil_full(t_all *all)
{
	int i;

	i = 0;
	while(i < all->info->sum_phil)
	{
		if(all[i].full_feed == 0)
			return (0);
		i++;
	}
	return (1);
}

void *phil_die(void *args)
{
    unsigned int i;
    unsigned int j;
    long long int start;
    
	t_all *all = (t_all *)args;
    while (1)
    {
        i = 0;
        while (i < all->info->sum_phil)
        {
            start = get_time(all);
            if ((start - all[i].philo->start) > all->info->death)
            {
				if (all[i].full_feed == 0)
				{
                    // pthread_mutex_lock(&all->table->forks[all->info->sum_phil]);
					sem_wait(all->table->sem_print);
                    ft_putnbr_fd(start, 1);
                    write(1, "ms ", 3);
                    all->death = 1;
                    write(1, all[i].philo->name2, 1);
                    write(1, " died\n", 6);
					sem_post(all->table->sem_print);
                    //pthread_mutex_unlock(&all->table->forks[all->info->sum_phil]);
					j = 0;
                    while(j < all->info->sum_phil)
					{
						kill(all[i++].philo->pid, SIGKILL);
					}
					exit(1);
				}
				else if (all[i].full_feed == 1 && check_phil_full(all) == 1)
				{
					exit(0);
				}
            }
            i++;
        }
    }
    return (NULL);
}

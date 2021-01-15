/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssnowbir <ssnowbir@student.21.ru>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 18:03:59 by ssnowbir          #+#    #+#             */
/*   Updated: 2021/01/14 16:10:08 by ssnowbir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int					ft_strlen(char *str)
{
	int				i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int					check_phil_full(t_all *all)
{
	int				i;

	i = 0;
	while (i < all->info->sum_phil)
	{
		if (all[i].full_feed == 0)
			return (0);
		i++;
	}
	return (1);
}

void				print_die(t_all *all, int start)
{
	sem_wait(all->table->sem_print);
	ft_putnbr_fd(start, 1);
	write(1, "ms ", 3);
	all->death = 1;
	ft_putnbr_fd(all->philo->name, 1);
	write(1, " died\n", 6);
	sem_post(all->table->sem_print);
}

void				*phil_die(void *args)
{
	int				i;
	long long int	start;
	t_all			*all;

	all = (t_all *)args;
	while (1)
	{
		i = -1;
		while (++i < all->info->sum_phil)
		{
			if ((start = get_time(all) - all->philo->start)
							> all->info->death || all->full_feed == 1)
			{
				if (all->full_feed == 0)
				{
					print_die(all, start);
					return (NULL);
				}
				else if (all->full_feed == 1 && check_phil_full(all) == 1)
					return (NULL);
			}
			usleep(20);
		}
	}
	return (NULL);
}

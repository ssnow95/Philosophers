/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssnowbir <ssnowbir@student.21.ru>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 19:50:25 by ssnowbir          #+#    #+#             */
/*   Updated: 2021/01/13 20:51:25 by ssnowbir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int					first_and_second_fork(int start, t_all *all)
{
	sem_wait(all->table->forks);
	sem_wait(all->table->sem_print);
	start = get_time(all);
	ft_putnbr_fd(start, 1);
	write(1, "ms ", 3);
	ft_putnbr_fd(all->philo->name, 1);
	write(1, " has taken a right fork\n", 24);
	sem_post(all->table->sem_print);
	sem_wait(all->table->forks);
	sem_wait(all->table->sem_print);
	start = get_time(all);
	ft_putnbr_fd(start, 1);
	write(1, "ms ", 3);
	ft_putnbr_fd(all->philo->name, 1);
	write(1, " has taken a left fork\n", 23);
	sem_post(all->table->sem_print);
	return (0);
}

int					eating(t_all *all)
{
	sem_wait(all->table->sem_print);
	ft_putnbr_fd(get_time(all), 1);
	write(1, "ms ", 3);
	ft_putnbr_fd(all->philo->name, 1);
	write(1, " is eating\n", 11);
	sem_post(all->table->sem_print);
	return (0);
}

int					eat(t_all *all)
{
	long long int	start;

	start = 0;
	first_and_second_fork(start, all);
	eating(all);
	start = get_time(all);
	all->philo->start = start;
	while (get_time(all) - start < all->info->eat)
		usleep(10);
	sem_post(all->table->forks);
	sem_post(all->table->forks);
	return (0);
}

int					sleep_philo(t_all *all)
{
	long int		start;

	sem_wait(all->table->sem_print);
	ft_putnbr_fd(get_time(all), 1);
	write(1, "ms ", 3);
	ft_putnbr_fd(all->philo->name, 1);
	write(1, " is sleeping\n", 13);
	sem_post(all->table->sem_print);
	start = get_time(all);
	while (get_time(all) - start < all->info->sleep)
		usleep(10);
	return (0);
}

int					think(t_all *all)
{
	sem_wait(all->table->sem_print);
	ft_putnbr_fd(get_time(all), 1);
	write(1, "ms ", 3);
	ft_putnbr_fd(all->philo->name, 1);
	write(1, " is thinking\n", 13);
	sem_post(all->table->sem_print);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssnowbir <ssnowbir@student.21.ru>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 14:58:09 by ssnowbir          #+#    #+#             */
/*   Updated: 2021/01/08 18:54:57 by ssnowbir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
// memset-  заполняет первые n байт области памяти, на которую указывает аргумент destination, символом, код которого указывается аргументом c.
			// void *memset (void *destination, int c, size_t n);

//  malloc
//  free
//  write
//  fork
//  kill - убить процесс
//  exit
// pthread_create
// pthread_detach
// pthread_join
// usleep
// gettimeofday
// waitpid
// sem_open
// sem_close
// sem_post
// sem_wait
// sem_unlink

int			parsing(char **argv, t_info *info, int argc)
{
	if (argv != NULL)
	{
		info->sum_phil = ft_atoi(argv[1]);
		info->death = ft_atoi(argv[2]);
		info->eat = ft_atoi(argv[3]);
		info->sleep= ft_atoi(argv[4]);
		if (argc == 6)
			info->must_eat = ft_atoi(argv[5]);
		else
			info->must_eat = -1;
		if (info->sum_phil > 200 && info->sum_phil < 2)
		{
			write(2, "incorrect sum philosophers\n", 27);
			return (1);
		}
		if (argc == 6 && info->must_eat <= 0)
		{
			write(2, "incorrect sum args[5]\n", 22);
			return (1);
		}
		return (0);
	}
	else
		return (1);
	return (0);
}

int			first_fork(int start, t_all *all)
{
	sem_wait(all->table->forks);
	if ((start = get_time(all)) - all->philo->start > all->info->death)
	{
		sem_post(all->table->forks);
		all->death = 1;
		return(1);
	}
	else
	{
		sem_wait(all->table->sem_print);
		start = get_time(all);
		ft_putnbr_fd(start, 1);
		write(1, "ms ", 3);
		write(1, all->philo->name2, 1);
		write(1, " has taken a right fork\n", 24); // rm right
		sem_post(all->table->sem_print);
	}
	return (0);
}

int			second_fork(int start, t_all *all)
{
	sem_wait(all->table->forks);
	if((start = get_time(all)) - all->philo->start > all->info->death)
	{
		sem_post(all->table->forks);
		sem_post(all->table->forks);
		all->death = 1;
		return(1);
	}
	else
	{
		sem_wait(all->table->sem_print);
		start = get_time(all);
		ft_putnbr_fd(start, 1);
		write(1, "ms ", 3);
		write(1, all->philo->name2, 1);
		write(1, " has taken a left fork\n", 23); // rm left
		sem_post(all->table->sem_print);
	}
	return (0);
}

int			eating(int start, t_all *all)
{
	if((start = get_time(all)) - all->philo->start > all->info->death)
	{
		sem_post(all->table->forks);
		sem_post(all->table->forks);
		all->death = 1;
		return(1);
	}
	else
	{
		sem_wait(all->table->sem_print);
		start = get_time(all);
		ft_putnbr_fd(start, 1);
		write(1, "ms ", 3);
		write(1, all->philo->name2, 1);
		write(1, " is eating\n", 11);
		sem_post(all->table->sem_print);
	}
	return (0);
}

int			eat(t_all *all)
{
	long long int finish;
	long long int start;

	if(first_fork(start,all) == 1)
		return (1);
	if(second_fork(start,all) == 1)
		return (1);
	if(eating(start,all) == 1)
		return (1);
	start = get_time(all);
	finish = start;
	all->philo->start = finish;
	while ((finish = get_time(all)) - start < all->info->eat)
		usleep(1);
	sem_post(all->table->forks);
	sem_post(all->table->forks);
	usleep(50);
	if(all->philo->must_eat > 0)
		all->philo->must_eat--;
	if(all->philo->must_eat == 0)
		all->full_feed++;
	return (0);
}

int			sleep_philo(t_all *all)
{
    long int start;
    long int finish;

	if((start = get_time(all)) - all->philo->start > all->info->death)
	{
		all->death = 1;
		return(1);
	}
	else
	{
		sem_wait(all->table->sem_print);
		start = get_time(all);
		ft_putnbr_fd(start, 1);
		write(1, "ms ", 3);
		write(1, all->philo->name2, 1); // change
		write(1, " is sleeping\n", 13);
		sem_post(all->table->sem_print);
	}
    start = get_time(all);
    finish = start;
    while ((finish = get_time(all)) - start < all->info->sleep)
        usleep(1);
	return (0);
}

int think(t_all *all)
{
    long long int       start;

	if((start = get_time(all)) - all->philo->start > all->info->death)
	{
		all->death = 1;
		return(1);
	}
	else
	{
		sem_wait(all->table->sem_print);
		start = get_time(all);
		ft_putnbr_fd(start, 1);
		write(1, "ms ", 3);
		write(1, all->philo->name2, 1); // change
		write(1, " is thinking\n", 13);
		sem_post(all->table->sem_print);
	}
	return (0);
}

void *live(void *args)
{
	pthread_t   philo;
    t_all *all = (t_all *)args;

	philo = (pthread_t)malloc(sizeof(pthread_t));
    while (all->death == 0)
    {	
		if (all->full_feed == 1)
			return (NULL);	
        if (eat(all) == 1 || sleep_philo(all) == 1 || think(all) == 1)
		{
			printf("i'm here");
			break ;
		}
    }
	pthread_create(&philo, NULL, phil_die, (void *)(&all[0]));
    return (NULL);
}

int         main(int argc, char **argv)
{
    t_all       *all;
    t_table     *table;
    t_philo     *philo;
    t_info      info;
     pthread_t   thread;
    int         i;

    i = 0;
    if((argc == 6 || argc == 5)  && parsing(argv, &info, argc) == 0)
    {
        philo = init_philo(info.sum_phil, info.must_eat);
        table = init_table(info.sum_phil);
        all = init_all(table, philo, &info);
        while(i < all->info->sum_phil)
        {
			all[i].philo->pid = fork();
			// printf("%d|%d\n",i, all[i].philo->pid);
			if (all[i].philo->pid == 0)
				live(all);
			else if (all[i].philo->pid < 0)
			{
				write(2, "error: fatal\n", 13);
				exit(1);
			}
			i++;
            usleep(50);
        }
		while(i < all->info->sum_phil)
        {
			if(waitpid(all[i].philo->pid, NULL, WUNTRACED) == -1)
			{
				i = 0;
				while(i < all->info->sum_phil)
					kill(all[i++].philo->pid, SIGKILL);
			}
			i++;
		}
    }
    else
    {
        write(2, "incorrect sum argc\n", 19);
        return (1);
    }
    return(0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssnowbir <ssnowbir@student.21.ru>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 16:27:26 by ssnowbir          #+#    #+#             */
/*   Updated: 2021/01/08 13:52:14 by ssnowbir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_info              *init_info(int sum_phil)
{
    t_info          *info;

    if(!(info = (t_info*)malloc(sizeof(t_info))))
        return (NULL);
    info->sum_phil = 0;
    info->death = 0;
    info->sleep = 0;
    info->eat = 0;
    info->must_eat = -1;
    return (info);
}

t_philo             *init_philo(int sum, int must_eat)
{
    int    i;
    t_philo   *philo;

    i = 0;
    if (!(philo = (t_philo*)malloc(sizeof(t_philo) * sum)))
        return (NULL);
    while (i < sum)
    {
		philo[i].must_eat = must_eat;
        philo[i].name = i + 1;
        philo[i].name2 = ft_itoa(philo[i].name);
        philo[i].right_fork = i;
        if (i == (sum - 1))
            philo[i].left_fork = 0;
        else
            philo[i].left_fork = i + 1;
    i++;
    }
    
    return (philo);
}

t_table				*init_table(int sum)   
{
	sem_t			*forks;
	sem_t			*sem_print;
	t_table			*table;
	int				i;

	i = 0;
	if(!(forks = (sem_t*)malloc(sizeof(sem_t) * sum)))
		return (NULL);
	if(!(sem_print = (sem_t*)malloc(sizeof(sem_t) * 1)))
		return (NULL);
	if(!(table = (t_table*)malloc(sizeof(t_table))))
		return (NULL);
	sem_unlink("forks");
	if ((forks = sem_open("forks", O_CREAT, 0666, sum)) == SEM_FAILED)
		exit (1);
	sem_unlink("sem_print");
	if ((sem_print= sem_open("sem_print", O_CREAT, 0666, 1)) == SEM_FAILED)
		exit (1);
	table->forks = forks;
	table->sem_print = sem_print;
	return(table);
} 

t_all               *init_all(t_table *table, t_philo *philo, t_info *info)
{
    t_all *all;
    int i;
    struct timeval tv;
    
    i = 0;
    if(!(all = (t_all*)malloc(sizeof(t_all) * info->sum_phil)))
        return (NULL);
    
    while(i < info->sum_phil)
    {	
		all[i].full_feed = 0;
        all[i].philo = &philo[i];
        all[i].table = table;
        all[i].info = info;
        all[i].count = 0;
        all[i].death = 0;
        if (gettimeofday(&tv, NULL) == -1)
            return (NULL);
        all[i].start = (unsigned int)((tv.tv_sec) * 1000 + (tv.tv_usec) / 1000);
        i++;
    }
    return (all);
}



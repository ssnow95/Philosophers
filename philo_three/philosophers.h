#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
#include <signal.h>
# include <fcntl.h>
#include <semaphore.h>

typedef struct			s_info
{
	int					sum_phil;
	long int			death;
	long int			sleep;
	long int			eat;
	long int			must_eat;
}						t_info;

typedef struct			s_philo
{
	int				name;
	char			*name2;
	int				left_fork;
	int				right_fork;
	//pthread_t		pthread;
	pid_t			pid;
	int				status;
	long long int	start;
	int				must_eat;
}					t_philo;

typedef struct		s_table
{
	sem_t			*forks;
	sem_t			*sem_print;
}					t_table;

typedef struct		s_all
{
	t_info			*info;
	t_table			*table;
	t_philo			*philo;
	long long int	start;
	long long int	death;
	int				count;
	int				full_feed;
}					t_all;

int					parsing(char **argv, t_info *info, int argc);
int					main(int argc, char **argv);
t_info				*init_info(int sum_phil);
int					ft_atoi(const char *str);
t_philo				*init_philo(int sum, int must_eat);
t_all				*init_all(t_table *table, t_philo *philo, t_info *info);
t_table				*init_table(int sum);
void				*live(void *args);
char				*ft_itoa(int n);
void				ft_putnbr(long long int n);
long long int		get_time(t_all *all);
void				ft_putstr_fd(char *s, int fd);
void				ft_putchar_fd(char c, int fd);
void				ft_putnbr_fd(int n, int fd);
void				*phil_die(void *args);

#endif
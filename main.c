/*
** main.c for philo in /home/voinne_c/rendu/PSU_2014_philo
** 
** Made by Cédric Voinnet
** Login   <voinne_c@epitech.net>
** 
** Started on  Mon Feb 23 12:58:20 2015 Cédric Voinnet
** Last update Tue Feb 24 10:10:53 2015 Cédric Voinnet
*/

#include <stdio.h>
#include <pthread.h>
#include "philo.h"

void		philosopher(void *arg)
{
  t_philo	*philo;

  philo = arg;
  
}

int		create_philosophers()
{
  int		nb;
  t_philo	*philosophers;

  nb = 0;
  if (!(philosophers = malloc(sizeof(philosophers) * NB_PHILO)))
    return (-1);
  while (nb != NB_PHILO)
    {
      philosophers[nb].philo_num = nb + 1;
      if (pthread_create(&philosophers[nb].philo_thread, NULL, &philosopher, &philosophers[nb]))
	{
	  printf("Can't create threads\nAbort\n");
	  return (-1);
	}
      ++nb;
    }
  nb = 0;
  while (nb != NB_PHILO)
    {
      if (pthread_join(philosophers[nb].philo_thread, NULL))
	return (-1);
      ++nb;
    }
  return (0);
}

int	main()
{
  if (create_philosophers())
    return (-1);
  return (0);
}

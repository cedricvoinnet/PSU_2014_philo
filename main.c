/*
** main.c for philo in /home/voinne_c/rendu/PSU_2014_philo
** 
** Made by Cédric Voinnet
** Login   <voinne_c@epitech.net>
** 
** Started on  Mon Feb 23 12:58:20 2015 Cédric Voinnet
** Last update Tue Feb 24 17:50:13 2015 Cédric Voinnet
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "philo.h"

int		exit_philosophers(t_philo **philosophers)
{
  int		nb;

  nb = 0;
  while (nb != NB_PHILO)
    {
      if (pthread_join(philosophers[nb]->philo_thread, NULL))
	return (-1);
      printf("n°%d - rice remaining: %d\n", philosophers[nb]->philo_num + 1, philosophers[nb]->rice);
      free(philosophers[nb]);
      ++nb;
    }
  free(philosophers);
  return (0);
}

int		create_philosophers()
{
  int		nb;
  t_philo	**philosophers;

  nb = 0;
  if (!(philosophers = malloc(sizeof(t_philo*) * NB_PHILO)))
    return (-1);
  while (nb != NB_PHILO)
    {
      if (!(philosophers[nb] = malloc(sizeof(t_philo))))
	return (-1);
      philosophers[nb]->philo_num = nb;
      philosophers[nb]->rice = 1;
      if (pthread_create(&philosophers[nb]->philo_thread, NULL,
			 &philosopher, philosophers[nb]))
	{
	  printf("Can't create threads\nAbort\n");
	  return (-1);
	}
      ++nb;
    }
  if (exit_philosophers(philosophers))
    return (-1);
  return (0);
}

int	main()
{
  if (init_table())
    return (-1);
  if (create_philosophers())
    {
      destroy_table();
      return (-1);
    }
  destroy_table();
  return (0);
}

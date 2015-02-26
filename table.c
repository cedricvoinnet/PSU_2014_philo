/*
** rods.c for philo in /home/voinne_c/rendu/PSU_2014_philo
** 
** Made by Cédric Voinnet
** Login   <voinne_c@epitech.net>
** 
** Started on  Tue Feb 24 10:14:48 2015 Cédric Voinnet
** Last update Tue Feb 24 11:09:03 2015 Cédric Voinnet
*/

#include <stdlib.h>
#include <pthread.h>
#include "philo.h"

pthread_mutex_t	*g_table;

int	init_table()
{
  int	nb;

  nb = 0;
  if (!(g_table = malloc(sizeof(pthread_mutex_t) * NB_PHILO)))
    return (-1);
  while (nb < NB_PHILO)
    {
      pthread_mutex_init(&g_table[nb], NULL);
      ++nb;
    }
  return (0);
}

void	destroy_table()
{
  int	nb;

  nb = 0;
  while (nb < NB_PHILO)
    {
      pthread_mutex_destroy(&g_table[nb]);
      ++nb;
    }
  free(g_table);
}

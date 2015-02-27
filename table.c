/*
** rods.c for philo in /home/voinne_c/rendu/PSU_2014_philo
** 
** Made by Cédric Voinnet
** Login   <voinne_c@epitech.net>
** 
** Started on  Tue Feb 24 10:14:48 2015 Cédric Voinnet
** Last update Thu Feb 26 16:35:28 2015 Cédric Voinnet
*/

#include <stdlib.h>
#include <pthread.h>
#include "philo.h"

int		g_rice_nb;
pthread_mutex_t	*g_table;
pthread_mutex_t	g_mutex_rice;
pthread_mutex_t	g_mut_turn;
pthread_cond_t	g_cond_turn;

int	init_table()
{
  int	nb;

  nb = 0;
  g_rice_nb = NB_PHILO * NB_RICE;
  if (!(g_table = malloc(sizeof(pthread_mutex_t) * NB_PHILO)))
    return (-1);
  while (nb < NB_PHILO)
    {
      pthread_mutex_init(&g_table[nb], NULL);
      ++nb;
    }
  pthread_mutex_init(&g_mutex_rice, NULL);
  pthread_mutex_init(&g_mut_turn, NULL);
  pthread_cond_init(&g_cond_turn, NULL);
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
  pthread_mutex_destroy(&g_mutex_rice);
  pthread_mutex_destroy(&g_mut_turn);
  pthread_cond_destroy(&g_cond_turn);
}

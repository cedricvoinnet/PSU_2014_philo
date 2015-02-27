/*
** philosopher_job.c for philo in /home/voinne_c/rendu/PSU_2014_philo
** 
** Made by Cédric Voinnet
** Login   <voinne_c@epitech.net>
** 
** Started on  Tue Feb 24 13:36:16 2015 Cédric Voinnet
** Last update Fri Feb 27 15:09:06 2015 Cédric Voinnet
*/

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include "philo.h"

void	left_hand(t_philo *my)
{
  if (!my->left_rod && !pthread_mutex_trylock(&g_table[my->philo_num]))
    my->left_rod = 1;
}

void	right_hand(t_philo *my)
{
  if (!my->right_rod && !pthread_mutex_trylock(&g_table[(my->philo_num + 1) % NB_PHILO]))
    my->right_rod = 1;
}

void	eat(t_philo *philo)
{
  if (philo->left_rod && philo->right_rod)
    {
      --philo->rice;
      philo->state = SLEEPY;
      pthread_mutex_lock(&g_mutex_rice);
      --g_rice_nb;
      pthread_mutex_unlock(&g_mutex_rice);
    }
}

void	drop_rods(t_philo *philo)
{
  if (philo->left_rod)
    {
      philo->left_rod = 0;
      pthread_mutex_unlock(&g_table[philo->philo_num]);
    }
  if (philo->right_rod)
    {
      philo->right_rod = 0;
      pthread_mutex_unlock(&g_table[(philo->philo_num + 1) % NB_PHILO]);
    }
}

void	take_rods(t_philo *philo)
{
  if (philo->philo_num % 2)
    {
      right_hand(philo);
      sleep(1);
      if (philo->rice || !philo->right_rod)
	left_hand(philo);
    }
  else
    {
      left_hand(philo);
      sleep(1);
      if (philo->rice || !philo->left_rod)
	right_hand(philo);
    }
}

void		*philosopher(void *arg)
{
  t_philo	*philo;

  philo = arg;
  philo->state = HUNGRY;
  philo->aff_state = STANDBY;
  pthread_mutex_lock(&g_mut_turn);
  while (g_rice_nb)
    {
      philo->job_done = 1;
      pthread_cond_wait(&g_cond_turn, &g_mut_turn);
      philo->job_done = 0;
      drop_rods(philo);
      if (philo->state == HUNGRY)
	take_rods(philo);
      philo->state = HUNGRY;
      eat(philo);
    }
  pthread_mutex_unlock(&g_mut_turn);
  philo->job_done = 1;
  return (NULL);
}

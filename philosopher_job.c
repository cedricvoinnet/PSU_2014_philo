/*
** philosopher_job.c for philo in /home/voinne_c/rendu/PSU_2014_philo
** 
** Made by Cédric Voinnet
** Login   <voinne_c@epitech.net>
** 
** Started on  Tue Feb 24 13:36:16 2015 Cédric Voinnet
** Last update Sat Feb 28 12:07:46 2015 Cédric Voinnet
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
  if (!my->right_rod && !pthread_mutex_trylock(
					       &g_table[(my->philo_num + 1) % NB_PHILO]))
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

void		*philosopher(void *arg)
{
  t_philo	*philo;

  philo = arg;
  philo->state = HUNGRY;
  philo->aff_state = STANDBY;
  drop_rods(philo);
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
  pthread_exit(NULL);
}

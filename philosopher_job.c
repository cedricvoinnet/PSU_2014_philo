/*
** philosopher_job.c for philo in /home/voinne_c/rendu/PSU_2014_philo
** 
** Made by Cédric Voinnet
** Login   <voinne_c@epitech.net>
** 
** Started on  Tue Feb 24 13:36:16 2015 Cédric Voinnet
** Last update Tue Feb 24 17:47:39 2015 Cédric Voinnet
*/

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include "philo.h"

void	left_hand(t_philo *my)
{
  if (!pthread_mutex_trylock(&g_table[my->philo_num]) && !my->left_rod)
    my->left_rod = 1;
}

void	right_hand(t_philo *my)
{
  if (!pthread_mutex_trylock(&g_table[my->philo_num + 1 % 7]) && !my->right_rod)
    my->right_rod = 1;
}

void	eat(t_philo *philo)
{
  if (philo->left_rod && philo->right_rod)
    {
      //      printf("n°%d a 2baguettes\n", philo->philo_num);
      --philo->rice;
      philo->state = SLEEPY;
    }
  if (philo->left_rod)
    {
      philo->left_rod = 0;
      pthread_mutex_unlock(&g_table[philo->philo_num]);
    }
  if (philo->right_rod)
    {
      philo->right_rod = 0;
      pthread_mutex_unlock(&g_table[philo->philo_num + 1 % 7]);
    }    
}

void	take_rods(t_philo *philo)
{
  if (philo->philo_num % 2)
    {
      right_hand(philo);
      sleep(1);
      left_hand(philo);
    }
  else
    {
      left_hand(philo);
      sleep(1);
      right_hand(philo);
    }
}

void		*philosopher(void *arg)
{
  t_philo	*philo;

  philo = arg;
  philo->state = HUNGRY;
  /* while (philo->rice) */
  /*   { */
  /* printf("Philosopher n°%d - rice remaining: %d\n", philo->philo_num, philo->rice); */
  if (philo->state == HUNGRY)
    take_rods(philo);
  philo->state = HUNGRY;
  eat(philo);
  /* } */
  return (NULL);
}

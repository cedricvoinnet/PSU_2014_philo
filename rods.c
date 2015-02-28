/*
** rods.c for philo in /home/voinne_c/rendu/PSU_2014_philo
** 
** Made by Cédric Voinnet
** Login   <voinne_c@epitech.net>
** 
** Started on  Sat Feb 28 09:27:51 2015 Cédric Voinnet
** Last update Sat Feb 28 12:15:28 2015 Cédric Voinnet
*/

#include <unistd.h>
#include <pthread.h>
#include "philo.h"

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
      if (philo->rice || !philo->right_rod)
	left_hand(philo);
    }
  else
    {
      left_hand(philo);
      if (philo->rice || !philo->left_rod)
	right_hand(philo);
    }
}

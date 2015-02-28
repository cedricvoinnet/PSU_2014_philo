/*
** main.c for philo in /home/voinne_c/rendu/PSU_2014_philo
** 
** Made by Cédric Voinnet
** Login   <voinne_c@epitech.net>
** 
** Started on  Mon Feb 23 12:58:20 2015 Cédric Voinnet
** Last update Sat Feb 28 12:11:38 2015 Cédric Voinnet
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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
      free(philosophers[nb]);
      ++nb;
    }
  free(philosophers);
  return (0);
}

void	inspector(t_philo **philosophers, t_gui *gui)
{
  int	nb;

  nb = 0;
  while (g_rice_nb)
    {
      while (nb != NB_PHILO)
      	{
      	  if (philosophers[nb]->job_done)
      	    {
	      if (philosophers[nb]->left_rod && philosophers[nb]->right_rod)
		philosophers[nb]->aff_state = EAT;
	      else if (philosophers[nb]->left_rod || philosophers[nb]->right_rod)
		philosophers[nb]->aff_state = THINK;
	      else
		philosophers[nb]->aff_state = STANDBY;
      	      printf("Philosopher n°%d - state: %d - rice remaining: %d\n",
		     philosophers[nb]->philo_num + 1, philosophers[nb]->aff_state, philosophers[nb]->rice);
	      ++nb;
      	    }
	}
      sleep(1);
      change_status(gui, philosophers);
      printf("---------------\n");
      pthread_cond_broadcast(&g_cond_turn);
      nb = 0;
    }
}

int		create_philosophers(t_gui *gui)
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
      philosophers[nb]->rice = NB_RICE;
      if (pthread_create(&philosophers[nb]->philo_thread, NULL,
			 &philosopher, philosophers[nb]))
	return (-1);
      ++nb;
    }
  inspector(philosophers, gui);
  if (exit_philosophers(philosophers))
    return (-1);
  return (0);
}

int	main()
{
  t_gui	gui;

  init_gui(&gui);
  if (init_table())
    return (-1);
  if (create_philosophers(&gui))
    {
      destroy_table();
      exit_gui(&gui);
      return (-1);
    }
  destroy_table();
  exit_gui(&gui);
  return (0);
}

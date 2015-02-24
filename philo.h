/*
** philo.h for philo in /home/voinne_c/rendu/PSU_2014_philo
** 
** Made by Cédric Voinnet
** Login   <voinne_c@epitech.net>
** 
** Started on  Tue Feb 24 08:38:46 2015 Cédric Voinnet
** Last update Tue Feb 24 09:57:10 2015 Cédric Voinnet
*/

#ifndef PHILO_H_
# define PHILO_H_

# define NB_PHILO	7

typedef struct		s_philo
{
  pthread_t		philo_thread;
  unsigned int		philo_num;
  pthread_mutex_t	*left_rod;
  pthread_mutex_t	*right_rod;
}			t_philo;

#endif	/* !PHILO_H_ */

/*
** philo.h for philo in /home/voinne_c/rendu/PSU_2014_philo
** 
** Made by Cédric Voinnet
** Login   <voinne_c@epitech.net>
** 
** Started on  Tue Feb 24 08:38:46 2015 Cédric Voinnet
** Last update Tue Feb 24 14:58:59 2015 Cédric Voinnet
*/

#ifndef PHILO_H_
# define PHILO_H_

# define NB_PHILO	7

extern pthread_mutex_t	*g_table;

typedef enum		e_state
  {
    HUNGRY,
    SLEEPY
  }			t_state;

typedef struct		s_philo
{
  pthread_t		philo_thread;
  unsigned int		philo_num;
  unsigned int		rice;
  char			left_rod;
  char			right_rod;
  t_state		state;
}			t_philo;

int	init_table();
void	destroy_table();
void	*philosopher(void *);

#endif	/* !PHILO_H_ */

/*
** philo.h for philo in /home/voinne_c/rendu/PSU_2014_philo
** 
** Made by Cédric Voinnet
** Login   <voinne_c@epitech.net>
** 
** Started on  Tue Feb 24 08:38:46 2015 Cédric Voinnet
** Last update Fri Feb 27 15:27:29 2015 Cédric Voinnet
*/

#ifndef PHILO_H_
# define PHILO_H_

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

# define NB_PHILO	7
# define NB_RICE	3

extern int		g_rice_nb;
extern pthread_mutex_t	*g_table;
extern pthread_mutex_t	g_mutex_rice;
extern pthread_mutex_t	g_mut_turn;
extern pthread_cond_t	g_cond_turn;

typedef enum		e_state
  {
    HUNGRY,
    SLEEPY
  }			t_state;

typedef enum		e_aff_state
  {
    STANDBY,
    THINK,
    EAT
  }			t_aff_state;

typedef struct	s_gui
{
  SDL_Surface	*screen;
  SDL_Rect	*pos;
  SDL_Surface	**philos;
}		t_gui;

typedef struct		s_philo
{
  pthread_t		philo_thread;
  unsigned int		philo_num;
  unsigned int		rice;
  char			left_rod;
  char			right_rod;
  t_state		state;
  t_aff_state		aff_state;
  char			job_done;
}			t_philo;

int		init_table();
void		destroy_table();
void		*philosopher(void *);

SDL_Surface	**init_philos(SDL_Rect *, SDL_Surface *);
SDL_Rect	*init_pos();
int		init_gui(t_gui *);
void		change_status(t_gui *, t_philo **);
void		exit_gui(t_gui *);

#endif	/* !PHILO_H_ */

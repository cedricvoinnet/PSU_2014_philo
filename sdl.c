#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "philo.h"

int	init_gui(t_gui *gui)
{
  if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
      printf("Erreur dans le chargement de la SDL %s\n", SDL_GetError());
      return (-1);
    }
  gui->screen =  SDL_SetVideoMode(1500, 900, 32, SDL_HWSURFACE);
  if (gui->screen == NULL)
    {
      puts("Error");
      return (-1);
    }
  SDL_WM_SetCaption("Philosophons un peu, voulez vous  ...", NULL);
  SDL_FillRect(gui->screen, NULL, SDL_MapRGB(gui->screen->format,
					     17, 206, 112));
  SDL_Flip(gui->screen);
  if (!(gui->pos = init_pos()))
    return (-1);
  if (!(gui->philos = init_philos(gui->pos, gui->screen)))
    return (-1);
  return (0);
}

SDL_Rect	*init_pos()
{
  SDL_Rect	*pos;

  if ((pos = malloc(sizeof(SDL_Rect) * 7)) == NULL)
    {
      puts("Malloc fail");
      return (NULL);
    }
  pos[0].x = 650;
  pos[0].y = 0;
  pos[1].x = 950;
  pos[1].y = 100;
  pos[2].x = 1150;
  pos[2].y = 400;
  pos[3].x = 850;
  pos[3].y = 600;
  pos[4].x = 450;
  pos[4].y = 600;
  pos[5].x = 150;
  pos[5].y = 400;
  pos[6].x = 350;
  pos[6].y = 100;
  return (pos);
}

SDL_Surface	**init_philos(SDL_Rect *pos, SDL_Surface *screen)
{
  SDL_Surface	**philos;
  int		i;

  i = 0;
  if ((philos = malloc(sizeof(SDL_Surface*) * 7)) == NULL)
    {
      puts("Malloc fail");
      return (NULL);
    }
  while (i != 7)
    {
      philos[i] = IMG_Load("./png/philo.png");
      SDL_BlitSurface(philos[i], NULL, screen, &pos[i]);
      i++;
    }
  SDL_Flip(screen);
  return (philos);
}

void	change_status(t_gui *gui, t_philo **philo)
{
  int	i;

  i = 0;
  while (i != 7)
    {
      SDL_FreeSurface(gui->philos[philo[i]->philo_num]);
      if (philo[i]->aff_state == STANDBY)
	gui->philos[philo[i]->philo_num] = IMG_Load("./png/philo.png");
      if (philo[i]->aff_state == EAT)
	gui->philos[philo[i]->philo_num] = IMG_Load("./png/philo_bag.png");
      if (philo[i]->aff_state == THINK)
	gui->philos[philo[i]->philo_num] = IMG_Load("./png/philo_think.png");
      SDL_BlitSurface(gui->philos[philo[i]->philo_num], NULL, gui->screen, &(gui->pos[philo[i]->philo_num]));
      ++i;
    }
  SDL_Flip(gui->screen);
}

void	exit_gui(t_gui *gui)
{
  int	i;

  i = 0;
  while (i != 7)
    SDL_FreeSurface(gui->philos[i++]);
  free(gui->philos);
  free(gui->pos);
  SDL_Quit();
}

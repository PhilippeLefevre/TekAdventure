/*
** event_key.c for tekadventure in /home/sousa_v/rendu/lapin/TekAdventure_temp
** 
** Made by victor sousa
** Login   <sousa_v@epitech.net>
** 
** Started on  Wed Apr  6 21:04:44 2016 victor sousa
** Last update Wed Apr  6 21:07:23 2016 victor sousa
*/

#include		"main.h"

t_bunny_response event_key(t_bunny_event_state state,
		     t_bunny_keysym      key,
		     void                *data)
{
  (void)state;
  (void)data;
  if (key == BKS_ESCAPE)
    return (EXIT_ON_SUCCESS);
  return (GO_ON);
}

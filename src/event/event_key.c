/*
** event_key.c for tekadventure in /home/sousa_v/rendu/lapin/TekAdventure_temp
**
** Made by victor sousa
** Login   <sousa_v@epitech.net>
**
** Started on  Wed Apr  6 21:04:44 2016 victor sousa
** Last update Sat Apr  9 16:54:32 2016 Victor Sousa
*/

#include		"main.h"

t_bunny_response	event_key(t_bunny_event_state state,
				  t_bunny_keysym      key,
				  void                *data)
{
  t_prog		*prog;

  prog = data;
  if (key == BKS_ESCAPE)
    return (EXIT_ON_SUCCESS);
  if (key == BKS_E && state == GO_DOWN)
    {
      if (prog->player->inventory_open == 0)
	prog->player->inventory_open = 1;
      else
	{
	  prog->player->inventory_open = 0;
	  prog->player->inv_selected = -1;
	}
    }
  return (GO_ON);
}

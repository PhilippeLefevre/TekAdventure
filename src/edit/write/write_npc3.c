/*
** write_npc3.c for tekadventure in /Users/leandr_g/Documents/Shared folder/TekAdventure/src/edit/write/
**
** Made by Gaëtan Léandre
** Login   <leandr_g@epitech.eu>
**
** Started on  Sat Apr 16 19:31:52 2016 Gaëtan Léandre
** Last update Sat Apr 16 22:59:18 2016 Gaëtan Léandre
*/

#include		"main.h"

void			write_npc_sprite_hitbox_h(t_npc *npc, int fd,
						  int size)
{
  t_npc			*tmp;
  int			i;

  i = 0;
  tmp = npc;
  my_printf(fd, "npc_sprite_hitbox_height=");
  while (tmp != NULL)
    {
      if (i != size - 1)
	my_printf(fd, "\"%d\", ", tmp->texture_hitbox->height);
      else
	my_printf(fd, "\"%d\"\n", tmp->texture_hitbox->height);
      tmp = tmp->next;
      i++;
    }
  if (size == 0)
    my_printf(fd, "\n");
}

void			write_npc_sprite_hitbox_w(t_npc *npc, int fd,
						  int size)
{
  t_npc			*tmp;
  int			i;

  i = 0;
  tmp = npc;
  my_printf(fd, "npc_sprite_hitbox_width=");
  while (tmp != NULL)
    {
      if (i != size - 1)
	my_printf(fd, "\"%d\", ", tmp->texture_hitbox->width);
      else
	my_printf(fd, "\"%d\"\n", tmp->texture_hitbox->width);
      tmp = tmp->next;
      i++;
    }
  if (size == 0)
    my_printf(fd, "\n");
}

void			write_npc_sprite_hitbox_y(t_npc *npc, int fd,
						  int size)
{
  t_npc			*tmp;
  int			i;

  i = 0;
  tmp = npc;
  my_printf(fd, "npc_sprite_hitbox_y=");
  while (tmp != NULL)
    {
      if (i != size - 1)
	my_printf(fd, "\"%d\", ", tmp->texture_hitbox->y);
      else
	my_printf(fd, "\"%d\"\n", tmp->texture_hitbox->y);
      tmp = tmp->next;
      i++;
    }
  if (size == 0)
    my_printf(fd, "\n");
}

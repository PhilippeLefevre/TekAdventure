/*
** npc.h for  in /Users/ethankerdelhue/Documents/Shared/TekAdventure/inc/
**
** Made by Ethan Kerdelhue
** Login   <kerdel_e@epitech.eu>
**
** Started on  Wed Apr  6 23:24:51 2016 Ethan Kerdelhue
** Last update Wed Apr 13 00:33:54 2016 Philippe Lefevre
*/

#ifndef 		NPC_H_
# define 		NPC_H_

# include 		"main.h"

typedef struct		s_trade
{
  t_item		*needed;
  t_item		*given;
}			t_trade;

typedef struct 		s_npc
{
  int			npc_id;
  char 			*name;
  char			*text;
  t_trade		*trade;
  int			sprite_id;
  t_hitbox		*texture_hitbox;
  t_texture		*texture;
  int			life;
  int			damage_min;
  int			damage_max;
  struct s_npc 		*next;
  struct s_npc		*prev;
} 			t_npc;

#endif			/* !NPC_H_ */

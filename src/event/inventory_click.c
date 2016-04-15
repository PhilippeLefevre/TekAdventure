/*
** inventory_click.c for  in /home/sousa_v/rendu/lapin/TekAdventure_temp/src/event/
**
** Made by Victor Sousa
** Login   <sousa_v@epitech.eu>
**
** Started on  Sat Apr  9 09:11:28 2016 Victor Sousa
** Last update Fri Apr 15 08:42:16 2016 Victor Sousa
*/

#include		"main.h"

void			handle_inventory_click(t_prog *prog)
{
  t_bunny_position	*click_pos;
  int			need_to_move;

  need_to_move = -1;
  click_pos = (t_bunny_position *)bunny_get_mouse_position();
  if (prog->player->inv_selected != -1)
    {
      need_to_move = prog->player->inv_selected;
      place_image(create_hitbox(click_pos->x, click_pos->y, 36, 30),
		  *prog->player->inventory[need_to_move].object->texture_hitbox,
		  prog->player->inventory[need_to_move].object->texture, prog->pix);
    }
  prog->player->inv_selected = get_click_place_hotbar(prog, click_pos);
  if (prog->player->inv_selected == -1 && prog->player->inventory_open == 1)
    prog->player->inv_selected = get_click_place_inventory(prog, click_pos);
  if (prog->player->inv_selected == -1 && prog->player->inventory_open == 1)
    prog->player->inv_selected = get_click_place_equip(prog, click_pos);
  if (prog->player->inv_selected != 1 &&
      prog->player->inventory[(int)prog->player->inv_selected].id == -1 &&
      need_to_move == -1)
    prog->player->inv_selected = -1;
  if (need_to_move != -1 && prog->player->inv_selected != -1)
    {
      if (prog->player->inv_selected >= 48 && need_to_move < 48)
      	{
	  /* on depose un equip */
      	}
      else if (prog->player->inv_selected < 48 && need_to_move >= 48)
      	{
	  /* on retire un equip */
      	}
      else if (prog->player->inventory[need_to_move].id ==
	       prog->player->inventory[(int)prog->player->inv_selected].id &&
	       need_to_move != prog->player->inv_selected)
	{
	  prog->player->inventory[(int)prog->player->inv_selected].amount +=
	  prog->player->inventory[need_to_move].amount;
	  prog->player->inventory[need_to_move].id = -1;
	  prog->player->inventory[need_to_move].amount = 0;
	  prog->player->inventory[need_to_move].object = NULL;
	}
      else
	my_swap_item(&prog->player->inventory[need_to_move],
		     &prog->player->inventory[(int)prog->player->inv_selected]);
      prog->player->inv_selected = -1;
    }
}

void			handle_inventory_click_npc(t_prog *prog)
{
  t_bunny_position	*click_pos;
  int			need_to_move;

  need_to_move = -1;
  click_pos = (t_bunny_position *)bunny_get_mouse_position();
  handle_red_cross(prog, click_pos);
  need_to_move = get_click_value(prog, need_to_move, click_pos);
  if (need_to_move != -1 && prog->player->inv_selected != -1)
    {
      if (need_to_move >= 0 && prog->player->inv_selected >= 0)
	move_in_hotbar(prog, need_to_move);
      else if (need_to_move == -3 &&
	       prog->player->inventory[(int)prog->player->inv_selected].id
	       == -1)
	pull_out_item(prog);
      else
	put_in_item(prog, need_to_move);
      prog->player->inv_selected = -1;
    }
}

/*
** inventory_click.c for  in /home/sousa_v/rendu/lapin/TekAdventure_temp/src/event/
**
** Made by Victor Sousa
** Login   <sousa_v@epitech.eu>
**
** Started on  Sat Apr  9 09:11:28 2016 Victor Sousa
** Last update Mon Apr 11 01:24:55 2016 Victor Sousa
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
      place_image(create_hitbox_ptr(*click_pos, 36, 30, prog->ptr_list),
		  prog->player->inventory[need_to_move].object->texture_hitbox,
		  prog->player->inventory[need_to_move].object->texture, prog->pix);
    }
  prog->player->inv_selected = get_click_place_hotbar(prog, click_pos);
  if (prog->player->inv_selected == -1 && prog->player->inventory_open == 1)
    prog->player->inv_selected = get_click_place_inventory(prog, click_pos);
  if (prog->player->inventory[(int)prog->player->inv_selected].id == -1 &&
      need_to_move == -1)
    prog->player->inv_selected = -1;
  if (need_to_move != -1 && prog->player->inv_selected != -1)
    {
      my_swap_item(&prog->player->inventory[need_to_move],
		   &prog->player->inventory[(int)prog->player->inv_selected]);
      prog->player->inv_selected = -1;
    }
}

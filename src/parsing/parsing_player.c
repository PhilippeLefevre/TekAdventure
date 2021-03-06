/*
** parsing_player.c for TekAdventure in /media/storage/my_files/Repository/Epitech/Year_1/Infographie/gfx_tekadventure/src/parsing/
**
** Made by Philippe Lefevre
** Login   <lefevr_h@epitech.net>
**
** Started on  Sat Apr 16 06:51:47 2016 Philippe Lefevre
** Last update Sun Apr 17 11:03:07 2016 Philippe Lefevre
*/

#include		"main.h"

t_hitbox		*player_hitbox_x(int id, t_bunny_ini *ini, char *name,
					 t_hitbox *hitbox)
{
  char			*str;

  if ((str = (char *)bunny_ini_get_field(ini, name,
					 "player_sprite_hitbox_x", id))
      == NULL)
    {
      my_puterror_hitbox("Error: ", -1, name);
      return (my_puterror_hitbox(":player_sprite_hitbox_x field ",
				 id, " not found\n"));
    }
  if ((hitbox->x = my_getnbr(str)) < 0)
    {
      my_puterror_hitbox("Error: ", -1, name);
      return (my_puterror_hitbox(":player_sprite_hitbox_x field ", id,
				 " should not be negative and only number\n"));
    }
  return (hitbox);
}

t_hitbox		*player_hitbox_y(int id, t_bunny_ini *ini, char *name,
					 t_hitbox *hitbox)
{
  char			*str;

  if ((str = (char *)bunny_ini_get_field(ini, name,
					 "player_sprite_hitbox_y", id))
      == NULL)
    {
      my_puterror_hitbox("Error: ", -1, name);
      return (my_puterror_hitbox(":player_sprite_hitbox_y field ",
				 id, " not found\n"));
    }
  if ((hitbox->y = my_getnbr(str)) < 0)
    {
      my_puterror_hitbox("Error: ", -1, name);
      return (my_puterror_hitbox(":player_sprite_hitbox_y field ", id,
				 " should not be negative and only number\n"));
    }
  return (hitbox);
}

t_hitbox		*player_hitbox_width(int id, t_bunny_ini *ini,
					     char *name, t_hitbox *hitbox)
{
  char			*str;

  if ((str = (char *)bunny_ini_get_field(ini, name,
					 "player_sprite_hitbox_width", id))
      == NULL)
    {
      my_puterror_hitbox("Error: ", -1, name);
      return (my_puterror_hitbox(":player_sprite_hitbox_width field ",
				 id, " not found\n"));
    }
  if ((hitbox->width = my_getnbr(str)) < 0)
    {
      my_puterror_hitbox("Error: ", -1, name);
      return (my_puterror_hitbox(":player_sprite_hitbox_width field ", id,
				 " should not be negative and only number\n"));
    }
  return (hitbox);
}

t_hitbox		*player_hitbox_height(int id, t_bunny_ini *ini,
					      char *name, t_hitbox *hitbox)
{
  char		*str;

  if ((str = (char *)bunny_ini_get_field(ini, name,
					 "player_sprite_hitbox_height", id))
      == NULL)
    {
      my_puterror_hitbox("Error: ", -1, name);
      return (my_puterror_hitbox(":player_sprite_hitbox_height field ",
				 id, " not found\n"));
    }
  if ((hitbox->height = my_getnbr(str)) < 0)
    {
      my_puterror_hitbox("Error: ", -1, name);
      return (my_puterror_hitbox(":player_sprite_hitbox_height field ", id,
				 " should not be negative and only number\n"));
    }
  return (hitbox);
}

t_hitbox		*create_player_hitbox(int id, t_bunny_ini *ini,
					      t_ptr_list **ptr_list)
{
  t_hitbox		*hitbox;

  if ((hitbox = xmalloc(sizeof(*hitbox), ptr_list)) == NULL)
    return (my_puterror_hitbox("Error: hitbox:xmalloc ", -1,
			       "failed in create_player_hitbox\n"));
  if ((hitbox = player_hitbox_x(id, ini, "player", hitbox)) == NULL)
    return (NULL);
  if ((hitbox = player_hitbox_y(id, ini, "player", hitbox)) == NULL)
    return (NULL);
  if ((hitbox = player_hitbox_width(id, ini, "player", hitbox)) == NULL)
    return (NULL);
  if ((hitbox = player_hitbox_height(id, ini, "player", hitbox)) == NULL)
    return (NULL);
  return (hitbox);
}

char			*fill_inventory_slot(char *tmp, t_bunny_ini *ini,
					     int i)
{
  if ((tmp = (char *)bunny_ini_get_field(ini, "player",
					 "player_inventory_slot",
					 i)) == NULL)
    {
      my_puterror_item("Error: player:player_inventory_slot ", -1,
		       "field not found\n");
      return (NULL);
    }
  return (tmp);
}

char			*fill_inventory_item(char *tmp, t_bunny_ini *ini,
					     int i)
{
  if ((tmp = (char *)bunny_ini_get_field(ini, "player",
					 "player_inventory_item", i)) == NULL)
    {
      my_puterror_item("Error: player:player_inventory_item ", -1,
		       "field not found\n");
      return (NULL);
    }
  return (tmp);
}

char			*fill_inventory_amount(char *tmp, t_bunny_ini *ini,
					       int i)
{
  if ((tmp = (char *)bunny_ini_get_field(ini, "player",
					 "player_inventory_amount",
					 i)) == NULL)
    {
      my_puterror_item("Error: player:player_inventory_amount ", -1,
		       "field not found\n");
      return (NULL);
    }
  return (tmp);
}

t_item			*fill_inventory(int i, int inventory_count,
					t_bunny_ini *ini, t_item *inventory)
{
  char			*tmp;
  int			slot;

  while (++i < inventory_count)
    {
      if ((tmp = fill_inventory_slot(tmp, ini, i)) == NULL)
      	return (NULL);
      if (((slot = my_getnbr(tmp)) < 0) || (slot > SIZE_INVENTORY))
	return (my_puterror_item("Error: player:player_inventory field ", i,
				 " should not be negative or greater \
than the size of the inventory\n"));
      if ((tmp = fill_inventory_item(tmp, ini, i)) == NULL)
	return (NULL);
      if ((inventory[slot].id = my_getnbr(tmp)) < 0)
	return (my_puterror_item("Error: player:player_inventory_count field ",
				 i, " object id should not be negative\n"));
      if ((tmp = fill_inventory_amount(tmp, ini, i)) == NULL)
	return (NULL);
      if ((inventory[slot].amount = my_getnbr(tmp)) < 0)
	return (my_puterror_item("Error: player:player_inventory_count field ",
				 i, " object amount should not be negative\n"));
    }
  return (inventory);
}

t_item			*load_player_inventory(t_item *inventory,
					       t_bunny_ini *ini,
					       t_ptr_list **ptr_list,
					       char *tmp)
{
  int			inventory_count;
  int			i;

  inventory = NULL;
  if ((inventory = xmalloc(sizeof(t_item)
			   * (SIZE_INVENTORY + 5), ptr_list)) == NULL)
    return (NULL);
  i = -1;
  while (++i != (SIZE_INVENTORY + 1))
    {
      inventory[i].id = -1;
      inventory[i].amount = -1;
    }
  if ((tmp = (char *)bunny_ini_get_field(ini, "player",
					 "player_inventory_count", 0)) == NULL)
    return (my_puterror_item("Error: player:player_inventory_count ", -1,
			     "field not found\n"));
  if ((inventory_count = my_getnbr(tmp)) < 0)
    return (my_puterror_item("Error: player:player_inventory_count ", -1,
			     "should not be negative\n"));
  else
    if ((fill_inventory(-1, inventory_count, ini, inventory)) == NULL)
      return (NULL);
  return (inventory);
}

t_item			*load_player_equiped(t_item *equiped, t_bunny_ini *ini,
					     t_ptr_list **ptr_list, char *tmp)
{
  int			i;

  (void)ini;
  (void)tmp;
  (void)ptr_list;
  i = 47;
  while (++i < 52)
    {
      equiped[i].id = -1;
      equiped[i].amount = -1;
      equiped[i].object = NULL;
    }
  return (equiped);
}

t_player		*load_player_texture(t_ptr_list **ptr_list,
					     t_player *player)
{
  if ((player->inv_open_sprite =
       load_image(T_INVENTORY, ptr_list)) == NULL)
    return (my_puterror_player("Error: player:inv_open_sprite \
	  			       failed load_image ", -1, T_INVENTORY));
  if ((player->sprite =
       load_image(T_PLAYER, ptr_list)) == NULL)
    return (my_puterror_player("Error: player:texture failed load_image ",
			       -1, T_PLAYER));
  if ((player->sprite->width != 210) || (player->sprite->height != 136))
    return (my_puterror_player("Error: player:texture authorized value width:\
			       210 height:136, size is out of range of:",
			       -1, T_PLAYER));
  if ((player->hotbar_sprite = load_image(T_HOTBAR, ptr_list)) == NULL)
    return (my_puterror_player("Error: player:inv_open_sprite \
	  				 failed load_image ", -1, T_HOTBAR));
  return (player);
}

t_player		*load_player_init(t_ptr_list **ptr_list, char *tmp,
					  t_bunny_ini *ini, t_player *player)
{
  if ((player = xmalloc(sizeof(t_player), ptr_list)) == NULL)
    return (my_puterror_player("Error: player:xmalloc ", -1,
			       "failed in load_player_init\n"));
  if ((tmp = (char *)bunny_ini_get_field(ini, "player",
					 "player_life", 0)) == NULL)
    return (my_puterror_player("Error: balise player or player:life ",
			       -1, "field not found\n"));
  if ((player->life = my_getnbr(tmp)) < 0)
    return (my_puterror_player("Error: player:player_life ", -1,
			       "should not be negative\n"));
  if ((tmp = (char *)bunny_ini_get_field(ini, "player",
					 "player_name", 0)) == NULL)
    return (my_puterror_player("Error: player:player_name ",
			       -1, "field not found\n"));
  if ((player->name = my_strdup(tmp, ptr_list)) == NULL)
    return (my_puterror_player("Error: player->name:my_strdup ",
			       -1, "failed in load_player_init\n"));
  if ((player = load_player_texture(ptr_list, player)) == NULL)
    return (my_puterror_player("\n", -1, ""));
  return (player);
}

t_player		*load_player_setting(t_player *player,
					     t_ptr_list **ptr_list)
{
  if ((player->caract = xmalloc(sizeof(t_caract), ptr_list)) == NULL)
    return (NULL);
  player->caract->stamina = 0;
  player->caract->strength = 0;
  player->caract->critical = 0;
  player->caract->agility = 0;
  player->caract->armor = 0;
  player->caract->intellect = 0;
  player->inventory_open = 0;
  player->inv_selected = -1;
  player->item_selected = -1;
  player->move.select_move = 0;
  player->move.depla = NULL;
  player->life = player->caract->stamina * 2 + player->life;
  return (player);
}

t_player		*load_player(t_bunny_ini *ini, t_ptr_list **ptr_list)
{
  t_player		*player;

  if ((player = load_player_init(ptr_list, NULL, ini, NULL)) == NULL)
    return (NULL);
  if ((player->inventory = load_player_inventory(player->inventory,
						 ini, ptr_list, NULL)) == NULL)
    return (NULL);
  if ((player->inventory = load_player_equiped(player->inventory,
					       ini, ptr_list, NULL)) == NULL)
    return (NULL);
  if ((player = load_player_setting(player, ptr_list)) == NULL)
    return (my_puterror_player("Error: player:xmalloc ", -1,
			       "failed in load_player_setting\n"));
  return (player);
}

/*
** parsing_gate.c for TekAdventure in /media/storage/my_files/Repository/Epitech/Year_1/Infographie/gfx_tekadventure/src/parsing/
**
** Made by Philippe Lefevre
** Login   <lefevr_h@epitech.net>
**
** Started on  Fri Apr 15 22:44:02 2016 Philippe Lefevre
** Last update Sat Apr 16 05:03:57 2016 Philippe Lefevre
*/

#include		"main.h"

t_hitbox		*create_gate_hitbox(int id, t_bunny_ini *ini,
					   t_ptr_list **ptr_list, char *name)
{
  t_hitbox		*hitbox;
  char			*str;

  if ((hitbox = xmalloc(sizeof(*hitbox), ptr_list)) == NULL)
    return (my_puterror_hitbox("Error: hitbox:xmalloc ", -1, "failed in create_gate_hitbox\n"));
  if ((str = (char *)bunny_ini_get_field(ini, name, "scene_gate_sprite_hitbox_x", id)) == NULL)
    {
      my_puterror_hitbox("Error: ", -1, name);
      return (my_puterror_hitbox(":scene_gate_sprite_hitbox_x field ", id, " not found\n"));
    }
  if ((hitbox->x = my_getnbr(str)) < 0)
      {
        my_puterror_hitbox("Error: ", -1, name);
        return (my_puterror_hitbox(":scene_gate_sprite_hitbox_x field ", id, " should not be negative and only number\n"));
      }
  if ((str = (char *)bunny_ini_get_field(ini, name, "scene_gate_sprite_hitbox_y", id)) == NULL)
    {
      my_puterror_hitbox("Error: ", -1, name);
      return (my_puterror_hitbox(":scene_gate_sprite_hitbox_y field ", id, " not found\n"));
    }
  if ((hitbox->y = my_getnbr(str)) < 0)
    {
      my_puterror_hitbox("Error: ", -1, name);
      return (my_puterror_hitbox(":scene_gate_sprite_hitbox_y field ", id, " should not be negative and only number\n"));
    }
  if ((str = (char *)bunny_ini_get_field(ini, name, "scene_gate_sprite_hitbox_width", id)) == NULL)
    {
      my_puterror_hitbox("Error: ", -1, name);
      return (my_puterror_hitbox(":scene_gate_sprite_hitbox_width field ", id, " not found\n"));
    }
  if ((hitbox->width = my_getnbr(str)) < 0)
    {
      my_puterror_hitbox("Error: ", -1, name);
      return (my_puterror_hitbox(":scene_gate_sprite_hitbox_width field ", id, " should not be negative and only number\n"));
    }
  if ((str = (char *)bunny_ini_get_field(ini, name, "scene_gate_sprite_hitbox_height", id)) == NULL)
    {
      my_puterror_hitbox("Error: ", -1, name);
      return (my_puterror_hitbox(":scene_gate_sprite_hitbox_height field ", id, " not found\n"));
    }
  if ((hitbox->height = my_getnbr(str)) < 0)
    {
      my_puterror_hitbox("Error: ", -1, name);
      return (my_puterror_hitbox(":scene_gate_sprite_hitbox_height field ", id, " should not be negative and only number\n"));
    }
  return (hitbox);
}

t_gate			*create_gate_node(int id, t_bunny_ini *ini,
					 t_ptr_list **ptr_list, char *name)
{
  t_gate		*gate;
  char			*str;

  if ((gate = xmalloc(sizeof(t_gate), ptr_list)) == NULL)
    return (my_puterror_gate("Error: ", "gate", ":xmalloc ", -1, "failed in create_gate_node\n"));
  if ((str = (char *)bunny_ini_get_field(ini, name, "scene_gate_sprite_id", id)) == NULL)
    return (my_puterror_gate("Error: ", name, ":scene_gate_sprite_id field ", id, " not found\n"));
  if ((gate->sprite_id = my_getnbr(str)) < 0)
    return (my_puterror_gate("Error ", name, "gate_sprite_id field ", id, " should not be negative\n"));

  if ((str = (char *)bunny_ini_get_field(ini, name, "scene_gate_name", id)) == NULL)
    return (my_puterror_gate("Error: ", name, ":scene_gate_name field ", id, " not found\n"));
  if ((gate->name = my_strdup(str, ptr_list)) == NULL)
    return (my_puterror_gate("Error: ", "gate->name", ":my_strdup ", -1, "failed in create_gate_node\n"));

  if ((str = (char *)bunny_ini_get_field(ini, name, "scene_gate_pos_x", id)) == NULL)
    return (my_puterror_gate("Error: ", name, ":scene_gate_pos_x field ", id, " not found\n"));
  if ((gate->pos.x = my_getnbr(str)) < 0)
    return (my_puterror_gate("Error: ", name, ":scene_gate_pos_x ", id, "should not be negative\n"));
  if ((str = (char *)bunny_ini_get_field(ini, name, "scene_gate_pos_y", id)) == NULL)
    return (my_puterror_gate("Error: ", name, ":scene_gate_pos_y field ", id, " not found\n"));
  if ((gate->pos.y = my_getnbr(str)) < 0)
    return (my_puterror_gate("Error: ", name, ":scene_gate_pos_y ", id, "should not be negative\n"));


  if ((gate->texture_hitbox = create_gate_hitbox(id, ini, ptr_list, name)) == NULL)
    return (NULL);
  gate->next = NULL;
  gate->prev = NULL;
  return (gate);
}

t_gate			*list_add_gate(int id, t_gate *list, char *name, t_bunny_ini *ini,
				      t_ptr_list **ptr_list)
{
  t_gate		*new;
  t_gate		*tmp;

  if ((new = create_gate_node(id, ini, ptr_list, name)) == NULL)
    return (NULL);
  if (list == NULL)
    return (new);
  tmp = list;
  while (tmp->next != NULL)
    tmp = tmp->next;
  new->prev = tmp;
  new->next = NULL;
  tmp->next = new;
  return (list);
}

t_gate			*load_gate(char *name, t_bunny_ini *ini,
				   t_ptr_list **ptr_list)
{
  t_gate		*list;
  char			*str;
  int			nb_gate;
  int			i;

  if ((str = (char *)bunny_ini_get_field(ini, name, "scene_gate_count", 0)) == NULL)
    return (my_puterror_gate("Error: balise scene or ", name, ":scene_gate_count ", -1, "field not found\n"));
  if ((nb_gate = my_getnbr(str)) < 0)
    return (my_puterror_gate("Error: ", name, ":gate_count ", -1, "should not be negative\n"));
  list = NULL;
  i = -1;
  while (++i != nb_gate)
    {
      if ((list = list_add_gate(i, list, name, ini, ptr_list)) == NULL)
	return (NULL);
    }
  return (list);
}

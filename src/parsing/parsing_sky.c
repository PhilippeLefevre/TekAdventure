/*
** parsing_sky.c for TekAdventure in /media/storage/my_files/Repository/Epitech/Year_1/Infographie/gfx_tekadventure/src/parsing/
**
** Made by Philippe Lefevre
** Login   <lefevr_h@epitech.net>
**
** Started on  Thu Apr 14 02:52:33 2016 Philippe Lefevre
** Last update Sun Apr 17 04:03:03 2016 Philippe Lefevre
*/

#include		"main.h"

t_hitbox		*sky_hitbox_x(int id, t_bunny_ini *ini, char *name,
				      t_hitbox *hitbox)
{
  char			*str;

  if ((str = (char *)bunny_ini_get_field(ini, name,
					 "scene_sky_sprite_hitbox_x", id))
      == NULL)
    {
      my_puterror_hitbox("Error: ", -1, name);
      return (my_puterror_hitbox(":scene_sky_sprite_hitbox_x field ",
				 id, " not found\n"));
    }
  if ((hitbox->x = my_getnbr(str)) < 0)
    {
      my_puterror_hitbox("Error: ", -1, name);
      return (my_puterror_hitbox(":scene_sky_sprite_hitbox_x field ", id,
				 " should not be negative and only number\n"));
    }
  return (hitbox);
}

t_hitbox		*sky_hitbox_y(int id, t_bunny_ini *ini, char *name,
				      t_hitbox *hitbox)
{
  char			*str;

  if ((str = (char *)bunny_ini_get_field(ini, name,
					 "scene_sky_sprite_hitbox_y", id))
      == NULL)
    {
      my_puterror_hitbox("Error: ", -1, name);
      return (my_puterror_hitbox(":scene_sky_sprite_hitbox_y field ",
				 id, " not found\n"));
    }
  if ((hitbox->y = my_getnbr(str)) < 0)
    {
      my_puterror_hitbox("Error: ", -1, name);
      return (my_puterror_hitbox(":scene_sky_sprite_hitbox_y field ", id,
				 " should not be negative and only number\n"));
    }
  return (hitbox);
}

t_hitbox		*sky_hitbox_width(int id, t_bunny_ini *ini,
					  char *name, t_hitbox *hitbox)
{
  char			*str;

  if ((str = (char *)bunny_ini_get_field(ini, name,
					 "scene_sky_sprite_hitbox_width",
					 id))
      == NULL)
    {
      my_puterror_hitbox("Error: ", -1, name);
      return (my_puterror_hitbox(":scene_sky_sprite_hitbox_width field ",
				 id, " not found\n"));
    }
  if ((hitbox->width = my_getnbr(str)) < 0)
    {
      my_puterror_hitbox("Error: ", -1, name);
      return (my_puterror_hitbox(":scene_sky_sprite_hitbox_width field ",
				 id,
				 " should not be negative and only number\n"));
    }
  return (hitbox);
}

t_hitbox		*sky_hitbox_height(int id, t_bunny_ini *ini,
					   char *name, t_hitbox *hitbox)
{
  char		*str;

  if ((str = (char *)bunny_ini_get_field(ini, name,
					 "scene_sky_sprite_hitbox_height",
					 id))
      == NULL)
    {
      my_puterror_hitbox("Error: ", -1, name);
      return (my_puterror_hitbox(":scene_sky_sprite_hitbox_height field ",
				 id, " not found\n"));
    }
  if ((hitbox->height = my_getnbr(str)) < 0)
    {
      my_puterror_hitbox("Error: ", -1, name);
      return (my_puterror_hitbox(":scene_sky_sprite_hitbox_height field ",
				 id,
				 " should not be negative and only number\n"));
    }
  return (hitbox);
}

t_hitbox		*create_sky_hitbox(int id, t_bunny_ini *ini,
					   t_ptr_list **ptr_list,
					   char *name)
{
  t_hitbox		*hitbox;

  if ((hitbox = xmalloc(sizeof(*hitbox), ptr_list)) == NULL)
    return (my_puterror_hitbox("Error: hitbox:xmalloc ", -1,
			       "failed in create_sky_hitbox\n"));
  if ((hitbox = sky_hitbox_x(id, ini, name, hitbox)) == NULL)
    return (NULL);
  if ((hitbox = sky_hitbox_y(id, ini, name, hitbox)) == NULL)
    return (NULL);
  if ((hitbox = sky_hitbox_width(id, ini, name, hitbox)) == NULL)
    return (NULL);
  if ((hitbox = sky_hitbox_height(id, ini, name, hitbox)) == NULL)
    return (NULL);
  return (hitbox);
}

t_sky			*create_sky_node_id(int id, t_bunny_ini *ini,
					    t_sky *sky, char *name)
{
  char		*str;
  if ((str = (char *)bunny_ini_get_field(ini, name,
					 "scene_sky_sprite_id", id)) == NULL)
    return (my_puterror_sky("Error: ", name,
			    ":scene_sky_sprite_id field ", id,
			    " not found\n"));
  if ((sky->sky_sprite_id = my_getnbr(str)) < 0)
    return (my_puterror_sky("Error ", name, "sky_sprite_id field ",
			    id, " should not be negative\n"));
  return (sky);
}

t_sky			*create_sky_node(int id, t_bunny_ini *ini,
					 t_ptr_list **ptr_list, char *name)
{
  t_sky			*sky;
  char			*str;

  if ((sky = xmalloc(sizeof(t_sky), ptr_list)) == NULL)
    return (my_puterror_sky("Error: ", "sky", ":xmalloc ",
			    -1, "failed in create_sky_node\n"));
  if ((create_sky_node_id(id, ini, sky, name)) == NULL)
    return (NULL);
  if ((str = (char *)bunny_ini_get_field(ini, name,
					 "scene_sky_sprite_distance",
					 id)) == NULL)
    return (my_puterror_sky("Error: ", name,
			    ":scene_sky_sprite_distance field ",
			    id, " not found\n"));
  if ((sky->distance = my_getnbr(str)) < 0)
    return (my_puterror_sky("Error ", name, "scene_sky_sprite_distance field ",
			    id, " should not be negative\n"));
  if ((sky->hitbox = create_sky_hitbox(id, ini, ptr_list, name)) == NULL)
    return (NULL);
  sky->next = NULL;
  sky->prev = NULL;
  return (sky);
}

t_sky			*list_add_sky(int id, t_sky *list, char *name,
				      t_bunny_ini *ini,
				      t_ptr_list **ptr_list)
{
  t_sky			*new;
  t_sky			*tmp;

  if ((new = create_sky_node(id, ini, ptr_list, name)) == NULL)
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

t_sky			*load_sky( char *name, t_bunny_ini *ini,
				   t_ptr_list **ptr_list)
{
  t_sky			*list;
  char			*str;
  int			nb_sky;
  int			i;

  if ((str = (char *)bunny_ini_get_field(ini, name,
					 "scene_sky_count", 0)) == NULL)
    return (my_puterror_sky("Error: balise scene or ", name,
			    ":scene_sky_count ", -1, "field not found\n"));
  if ((nb_sky = my_getnbr(str)) < 0)
    return (my_puterror_sky("Error: ", name, ":sky_count ",
			    -1, "should not be negative\n"));
  list = NULL;
  i = -1;
  while (++i != nb_sky)
    {
      if ((list = list_add_sky(i, list, name, ini, ptr_list)) == NULL)
	return (NULL);
    }
  return (list);
}

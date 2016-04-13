/*
** parsing_scene.c for TekAdventure in /home/lefevr_h/Repository/Epitech/Year_1/Infographie/gfx_tekadventure/src/parsing
**
** Made by Philippe Lefevre
** Login   <lefevr_h@epitech.net>
**
** Started on  Thu Apr  7 01:13:52 2016 Philippe Lefevre
** Last update Wed Apr 13 06:26:45 2016 Philippe Lefevre
*/

#include		"main.h"

static t_scene		*my_puterror_s(char *str)
{
  t_scene		*ret;

  write(2, str, my_strlen(str));
  ret = NULL;
  return (ret);
}

static t_ground		*my_puterror_g(char *str)
{
  t_ground		*ret;

  write(2, str, my_strlen(str));
  ret = NULL;
  return (ret);
}

static t_sky		*my_puterror_n(char *str)
{
  t_sky 	*tmp;

  tmp = NULL;
  write(2, str, my_strlen(str));
  return (tmp);
}

t_object		*link_object(t_object *object, t_sprite *sprite)
{
  t_object		*tmp_object;
  t_sprite		*tmp_sprite;

  tmp_object = object;
  while (tmp_object != NULL)
    {
      tmp_sprite = sprite;
      while (tmp_sprite != NULL)
	{
	  if (tmp_sprite->id == tmp_object->sprite_id)
	    tmp_object->texture = tmp_sprite->sprite;
	  tmp_sprite = tmp_sprite->next;
	}
      tmp_object = tmp_object->next;
    }
  return (object);
}

t_decors		*link_decors(t_decors *decors, t_sprite *sprite)
{
  t_decors		*tmp_decors;
  t_sprite		*tmp_sprite;

  tmp_decors = decors;
  while (tmp_decors != NULL)
    {
      tmp_sprite = sprite;
      while (tmp_sprite != NULL)
	{
	  if (tmp_sprite->id == tmp_decors->sprite_id)
	    tmp_decors->texture = tmp_sprite->sprite;
	  tmp_sprite = tmp_sprite->next;
	}
      tmp_decors = tmp_decors->next;
    }
  return (decors);
}

t_npc			*link_npc(t_npc *npc, t_sprite *sprite,
				  t_object *object)
{
  t_npc			*tmp_npc;
  t_object		*tmp_object;
  t_sprite		*tmp_sprite;

  tmp_npc = npc;
  while (tmp_npc != NULL)
    {
      tmp_sprite = sprite;
      while (tmp_sprite != NULL)
	{
	  if (tmp_sprite->id == tmp_npc->sprite_id)
	    tmp_npc->texture = tmp_sprite->sprite;
	  tmp_sprite = tmp_sprite->next;
	}
      tmp_object = object;
      while (tmp_object != NULL)
	{
	  if (tmp_object->object_id == tmp_npc->trade->needed->id)
	    tmp_npc->trade->needed->object = tmp_object;
	  tmp_object = tmp_object->next;
	}
      tmp_npc = tmp_npc->next;
    }
  return (npc);
}

t_player		*link_player(t_player *player, t_sprite *sprite)
{
  t_player		*tmp_player;
  t_sprite		*tmp_sprite;

  tmp_player = player;
  sprite = sprite;
  while (tmp_sprite != NULL)
    {
      if (tmp_sprite->id == tmp_player->sprite_id)
	tmp_player->sprite = tmp_sprite->sprite;
      tmp_sprite = tmp_sprite->next;
    }
  return (player);
}

t_item			*link_inventory_item(t_item *inventory, t_object *object)
{
  t_object		*tmp_object;
 int			i;

  i = -1;
  while (++i != SIZE_INVENTORY)
    {
      tmp_object = object;
      while (tmp_object != NULL)
	{
	  if (tmp_object->object_id == inventory[i].id)
	    inventory[i].object = tmp_object;
	  tmp_object = tmp_object->next;
	}
    }
  return (inventory);
}

t_ground		*ground_fill(t_bunny_ini *ini, t_scene *scene)
{
  t_npc			*npc;
  t_decors		*decors;
  int			tab[3];
  char			*str;
  int			i;
  int			j;
  int			k;

  i = -1;
  while (++i != (scene->size.x * scene->size.y))
    {
      scene->ground[i].npc = NULL;
      scene->ground[i].decors = NULL;
    }
  scene->ground[i].npc = NULL;
  scene->ground[i].decors = NULL;
  if ((str = (char *)bunny_ini_get_field(ini, "count", "scene_npc_count", 0)) == NULL)
    return (NULL);
  i = my_getnbr(str);
  j = 0;
  while (j < i)
    {
      if ((str = (char *)bunny_ini_get_field(ini, "scene", "npc_id", j)) == NULL)
	return (my_puterror_g("Error: scene or scene:npc_id not set\n"));
      tab[0] = my_getnbr(str);
      if ((str = (char *)bunny_ini_get_field(ini, "scene", "npc_pos", j)) == NULL)
	return (my_puterror_g("Error: scene or scene:npc_pos not set\n"));
      tab[1] = my_getnbr(str);
      k = -1;
      while (str[++k] && str[k] != ';');
      tab[2] = my_getnbr(str + k + 1);
      npc = scene->npc;
      while (npc != NULL)
	{
	  if (npc->npc_id == tab[0])
	    scene->ground[(tab[1] + (tab[2] * scene->size.x))].npc = npc;
	  npc = npc->next;
	}
      j++;
    }
  if ((str = (char *)bunny_ini_get_field(ini, "count", "scene_decors_count", 0)) == NULL)
    return (NULL);
  i = my_getnbr(str);
  j = 0;
  while (j < i)
    {
      if ((str = (char *)bunny_ini_get_field(ini, "scene", "decors_id", j)) == NULL)
	return (my_puterror_g("Error: scene or scene:decors_id not set\n"));
      tab[0] = my_getnbr(str);
      if ((str = (char *)bunny_ini_get_field(ini, "scene", "decors_pos", j)) == NULL)
	return (my_puterror_g("Error: scene or scene:decors_pos not set\n"));
      tab[1] = my_getnbr(str);
      k = -1;
      while (str[++k] && str[k] != ';');
      tab[2] = my_getnbr(str + k + 1);
      decors = scene->decors;
      while (decors != NULL)
      {
	if (decors->decors_id == tab[0])
	    scene->ground[(tab[1] + (tab[2] * scene->size.x))].decors = decors;
	  decors = decors->next;
      }
      j++;
    }
  return (scene->ground);
}

t_hitbox		*create_sol_hitbox(int id, t_bunny_ini *ini,
						 t_ptr_list **ptr_list)
{
  t_hitbox		*hitbox;
  char			*str;
  int			i;

  if ((hitbox = xmalloc(sizeof(*hitbox), ptr_list)) == NULL)
    return (NULL);
  if ((str = (char *)bunny_ini_get_field(ini, "scene", "ground_sprite_hitbox", id)) == NULL)
    return (NULL);
  i = -1;
  hitbox->x = my_getnbr(str);
  while (str[++i] && str[i] != ';');
  hitbox->y = my_getnbr(str + i + 1);
  while (str[++i] && str[i] != ';');
  hitbox->width = my_getnbr(str + i + 1);
  while (str[++i] && str[i] != ';');
  hitbox->height = my_getnbr(str + i + 1);
  return (hitbox);
}

t_scene			*link_ground(t_bunny_ini *ini, t_scene *scene,
				    t_ptr_list **ptr_list)
{
  t_sprite		*tmp_sprite;
  t_ground		*ground;
  char			*str;
  int			i;

  ground = NULL;
  if ((str = (char *)bunny_ini_get_field(ini, "scene", "nb_x_case", 0)) == NULL)
    return (my_puterror_s("Error: scene or scene:nb_x_case not set\n"));
  scene->size.x = my_getnbr(str);
  if ((str = (char *)bunny_ini_get_field(ini, "scene", "nb_y_case", 0)) == NULL)
    return (my_puterror_s("Error: scene or scene:nb_y_case not set\n"));
  scene->size.y = my_getnbr(str);
  if ((ground = xmalloc((sizeof(*ground) * ((scene->size.x * scene->size.y) + 1)), ptr_list)) == NULL)
    return (my_puterror_s("Error: Malloc failed ground.c:t_ground\n"));
  scene->ground = ground;
  if ((scene->ground = ground_fill(ini, scene)) == NULL)
    return (NULL);
  if ((str = (char *)bunny_ini_get_field(ini, "scene", "ground_sprite_id", 0)) == NULL)
    return (my_puterror_s("Error: scene or scene:nb_y_case not set\n"));
  scene->sol_id = my_getnbr(str);
  scene->sol_hitbox = create_sol_hitbox(0, ini, ptr_list);
  scene->height = 300;
  tmp_sprite = scene->sprite;
  while (tmp_sprite != NULL)
    {
      if (tmp_sprite->id == scene->sol_id)
	scene->sol = tmp_sprite->sprite;
      tmp_sprite = tmp_sprite->next;
    }
  if ((str = (char *)bunny_ini_get_field(ini, "scene", "start_pos", 0)) == NULL)
    return (my_puterror_s("Error: scene or scene:start_pos not set"));
  scene->start_pos = xmalloc(sizeof(*scene->start_pos), ptr_list);
  scene->start_pos->x = my_getnbr(str);
  i = -1;
  while (str[++i] && str[i] != ';');
  scene->start_pos->y = my_getnbr(str + i + 1);
  return (scene);
}

t_hitbox		*create_sky_hitbox(int id, t_bunny_ini *ini,
					   t_ptr_list **ptr_list)
{
  t_hitbox		*hitbox;
  char			*str;
  int			i;

  if ((hitbox = xmalloc(sizeof(*hitbox), ptr_list)) == NULL)
    return (NULL);
  if ((str = (char *)bunny_ini_get_field(ini, "scene", "sky_sprite_hitbox", id)) == NULL)
    return (NULL);
  i = -1;
  hitbox->x = my_getnbr(str);
  while (str[++i] && str[i] != ';');
  hitbox->y = my_getnbr(str + i + 1);
  while (str[++i] && str[i] != ';');
  hitbox->width = my_getnbr(str + i + 1);
  while (str[++i] && str[i] != ';');
  hitbox->height = my_getnbr(str + i + 1);
  return (hitbox);
}

t_sky			*create_sky_node(int id, t_bunny_ini *ini,
					 t_ptr_list **ptr_list)
{
  t_sky			*sky;
  char			*str;

  if ((sky = xmalloc(sizeof(t_sky), ptr_list)) == NULL)
    return (my_puterror_n("Error: failed malloc sky node\n"));
  if ((str = (char *)bunny_ini_get_field(ini, "scene", "sky_sprite_id", id)) == NULL)
    return (my_puterror_n("Error: sky or sky:sky_sprite_id not set\n"));
  sky->sky_sprite_id = my_getnbr(str);
  if ((str = (char *)bunny_ini_get_field(ini, "scene", "sky_sprite_distance", id)) == NULL)
    return (my_puterror_n("Error: sky or sky:sky_sprite_distance not set\n"));
  sky->distance = my_getnbr(str);
  sky->hitbox = create_sky_hitbox(id, ini, ptr_list);
  sky->next = NULL;
  sky->prev = NULL;
  return (sky);
}

t_sky			*list_add_sky(t_sky *list, int id, t_bunny_ini *ini,
				      t_ptr_list **ptr_list)
{
  t_sky			*new;
  t_sky			*tmp;

  if ((new = create_sky_node(id, ini, ptr_list)) == NULL)
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

t_sky			*load_sky(t_bunny_ini *ini, t_ptr_list **ptr_list)
{
  t_sky			*list;
  char			*str;
  int			nb_sky;
  int			i;

  i = 0;
  if ((str = (char *)bunny_ini_get_field(ini, "scene", "sky_count", 0)) == NULL)
    return (my_puterror_n("Error: scene or scene:sky_count not set\n"));
  nb_sky = my_getnbr(str);
  list = NULL;
  while (i != nb_sky)
    {
      if ((list = list_add_sky(list, i, ini, ptr_list)) == NULL)
	return (my_puterror_n("Error: invalid sky_count or previous error"));
      i++;
    }
  return (list);
}

t_sky			*link_sky(t_sky *sky, t_sprite *sprite)
{
  t_sprite		*tmp_sprite;
  t_sky			*tmp_sky;

  tmp_sprite = sprite;
  while (tmp_sprite != NULL)
    {
      tmp_sky = sky;
      while (tmp_sky != NULL)
	{
	  if (tmp_sky->sky_sprite_id == tmp_sprite->id)
	    tmp_sky->texture = tmp_sprite->sprite;
	  tmp_sky = tmp_sky->next;
	}
      tmp_sprite = tmp_sprite->next;
    }
  return (sky);
}

t_sky			*order_sky(t_sky *sky)
{
  t_sky  		*tmp_sky;
  int			id_swap;
  t_texture		*texture_swap;
  t_hitbox		*hitbox_swap;
  int			distance_swap;

  tmp_sky = sky;
  while (tmp_sky != NULL)
    {
      if ((tmp_sky->next != NULL)
	  && (tmp_sky->distance < tmp_sky->next->distance))
	{
	  id_swap = tmp_sky->sky_sprite_id;
	  tmp_sky->sky_sprite_id = tmp_sky->next->sky_sprite_id;
	  tmp_sky->next->sky_sprite_id = id_swap;

          texture_swap = tmp_sky->texture;
	  tmp_sky->texture = tmp_sky->next->texture;
	  tmp_sky->next->texture = texture_swap;

          hitbox_swap = tmp_sky->hitbox;
          tmp_sky->hitbox = tmp_sky->next->hitbox;
          tmp_sky->next->hitbox = hitbox_swap;

          distance_swap = tmp_sky->distance;
          tmp_sky->distance = tmp_sky->next->distance;
          tmp_sky->next->distance = distance_swap;
	}
      tmp_sky = tmp_sky->next;
    }
  return (sky);
}

t_scene			*load_scene(t_bunny_ini *ini, t_scene *scene,
				    t_ptr_list **ptr_list)
{
  /* Penser gestion d'erreur id deja existant ou inexistant sur toute les list, sprite objet ... */
  /* Penser verifé taille image, image 25cm, hibox 26cms */
  scene->sky = load_sky(ini, ptr_list);
  scene->sky = link_sky(scene->sky, scene->sprite);
  scene->sky = order_sky(scene->sky);
  scene->object = link_object(scene->object, scene->sprite);
  scene->player->inventory = link_inventory_item(scene->player->inventory, scene->object);
  scene->decors = link_decors(scene->decors, scene->sprite);
  scene->npc = link_npc(scene->npc, scene->sprite, scene->object);
  scene = link_ground(ini, scene, ptr_list);
  set_hitbox_ground(scene, (*ptr_list));
  return (scene);
}

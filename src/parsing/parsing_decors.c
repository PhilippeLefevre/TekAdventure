/*
** parsing_decors.c for TekAdventure in /home/lefevr_h/Repository/Epitech/Year_1/Infographie/gfx_tekadventure/src/parsing
**
** Made by Philippe Lefevre
** Login   <lefevr_h@epitech.net>
**
** Started on  Thu Apr  7 01:13:52 2016 Philippe Lefevre
** Last update Sat Apr  9 05:59:28 2016 Philippe Lefevre
*/

#include		"main.h"

static t_player		*my_puterror_p(char *str)
{
  t_player 	*tmp;

  tmp = NULL;
  write(2, str, my_strlen(str));
  return (tmp);
}

static t_breakable	*my_puterror_b(char *str)
{
  t_breakable 	*tmp;

  tmp = NULL;
  write(2, str, my_strlen(str));
  return (tmp);
}

static t_decors		*my_puterror_d(char *str)
{
  t_decors 	*tmp;

  tmp = NULL;
  write(2, str, my_strlen(str));
  return (tmp);
}

int 			fill_loot_table(char *str, unsigned int tab[2])
{
  int			i;

  tab[0] = my_getnbr(str);
  i = -1;
  while (str[++i] && str[i] != ';');
  tab[1] = my_getnbr(str + i + 1);
  return (0);
}

t_breakable		*create_decors_breakable(int id, t_bunny_ini *ini,
						 t_ptr_list **ptr_list)
{
  t_breakable		*breakable;
  char			*str;

  if ((breakable = xmalloc(sizeof(*breakable), ptr_list)) == NULL)
    return (my_puterror_b("Error: Malloc failed parsing_decors.c:40\n"));
  if ((str = (char *)bunny_ini_get_field(ini, "decors", "breakable", id)) == NULL)
    return (my_puterror_b("Error: field decors or decors:breakable not set\n"));
  breakable->is_breakable = my_getnbr(str);
  if ((breakable->is_breakable != 0) && (breakable->is_breakable != 1))
    return (my_puterror_b("Error: decors breakable must be 0 or 1\n"));
  if ((str = (char *)bunny_ini_get_field(ini, "decors", "breakable_life", id)) == NULL)
    return (my_puterror_b("Error: field decors or decors:breakable_life not set\n"));
  breakable->life = my_getnbr(str);
  if ((str = (char *)bunny_ini_get_field(ini, "decors", "breakable_by", id)) == NULL)
    return (my_puterror_b("Error: field decors or decors:breakable_by not set\n"));
  breakable->breakable_by = my_getnbr(str);
  if ((str = (char *)bunny_ini_get_field(ini, "decors", "lootable", id)) == NULL)
    return (my_puterror_b("Error: field decors or decors:lootable not set\n"));
  breakable->lootable = my_getnbr(str);
  if ((str = (char *)bunny_ini_get_field(ini, "decors", "loot", id)) == NULL)
    return (my_puterror_b("Error: field decors or decors:loot not set\n"));
  fill_loot_table(str, breakable->loot);
  return (breakable);
}

t_hitbox		*create_decors_hitbox(int id, t_bunny_ini *ini,
						 t_ptr_list **ptr_list)
{
  t_hitbox		*hitbox;
  char			*str;
  int			i;

  if ((hitbox = xmalloc(sizeof(*hitbox), ptr_list)) == NULL)
    return (NULL);
  if ((str = (char *)bunny_ini_get_field(ini, "decors", "sprite_hitbox", id)) == NULL)
    {
      my_puterror_p("Error: field decors or decors:sprite_hitbox not set\n");
      return (NULL);
    }
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

t_decors		*create_decors_node(int id,
					    t_bunny_ini *ini,
					    t_ptr_list **ptr_list)
{
  t_decors		*decors;
  char			*str;

  if ((decors = xmalloc(sizeof(*decors), ptr_list)) == NULL)
    return (my_puterror_d("Error: field decors or decors:breakable not set\n"));
  if ((str = (char *)bunny_ini_get_field(ini, "decors", "decors_id", id)) == NULL)
    return (my_puterror_d("Error: field decors or decors:decors_id not set\n"));
  decors->decors_id = my_getnbr(str);
  if ((str = (char *)bunny_ini_get_field(ini, "decors", "name", id)) == NULL)
    return (my_puterror_d("Error: field decors or decors:name not set\n"));
  if ((decors->name = my_strdup(str, ptr_list)) == NULL)
    return (NULL);
  if ((str = (char *)bunny_ini_get_field(ini, "decors", "sprite_id", id)) == NULL)
    return (my_puterror_d("Error: field decors or decors:sprite_id not set\n"));
  decors->sprite_id = my_getnbr(str);
  if ((decors->decors_breakable =
       create_decors_breakable(id, ini, ptr_list)) == NULL)
    return (NULL);
  if ((decors->texture_hitbox = create_decors_hitbox(id, ini, ptr_list)) == NULL)
    return (NULL);
  decors->next = NULL;
  decors->prev = NULL;
  return (decors);
}

t_decors		*list_add_decors(t_decors *list, int id,
					 t_bunny_ini *ini,
					 t_ptr_list **ptr_list)
{
  t_decors		*new;
  t_decors		*tmp;

  if ((new = create_decors_node(id, ini, ptr_list)) == NULL)
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

t_decors		*load_decors(t_bunny_ini *ini, t_ptr_list **ptr_list)
{
  t_decors		*list;
  char			*str;
  int			nb_decors;
  int			i;

  i = 0;
  if ((str = (char *)bunny_ini_get_field(ini, "count", "decors_count", 0)) == NULL)
    return (NULL);
  nb_decors = my_getnbr(str);
  list = NULL;
  while (i < nb_decors)
    {
      if ((list = list_add_decors(list, i, ini, ptr_list)) == NULL)
	return (NULL);
      i++;
    }
  return (list);
}

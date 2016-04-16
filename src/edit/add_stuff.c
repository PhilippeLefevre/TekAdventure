/*
** add_stuff.c for  in /home/sousa_v/rendu/lapin/TekAdventure_temp/src/edit/
**
** Made by Victor Sousa
** Login   <sousa_v@epitech.eu>
**
** Started on  Sat Apr 16 19:20:47 2016 Victor Sousa
** Last update Sat Apr 16 19:43:18 2016 Victor Sousa
*/

#include		"main.h"

void			pick_what_to_add(char *str, t_ini *ini)
{
  (void)ini;
  if (my_strcmp(str, "1") == 0)
    my_printf(1, "Add sprite\n");
  if (my_strcmp(str, "2") == 0)
    my_printf(1, "Add object\n");
  if (my_strcmp(str, "3") == 0)
    my_printf(1, "Add decors\n");
  if (my_strcmp(str, "4") == 0)
    my_printf(1, "Add npc\n");
  if (my_strcmp(str, "5") == 0)
    my_printf(1, "Add scene\n");
}

void			add_all(t_ini *ini)
{
  char			*str;

  my_printf(1, "What do you want to add?\n1: sprite\n2: object\n3: decors\n");
  my_printf(1, "4: npc\n5: scene\n");
  if ((str = get_next_line(0)) == NULL)
    return;
  while (my_strcmp(str, "1") && my_strcmp(str, "2") && my_strcmp(str, "3") &&
	 my_strcmp(str, "4") && my_strcmp(str, "5"))
    {
      free(str);
      my_printf(1, "\nWrong input, choose between 1, 2, 3, 4, 5\n");
      if ((str = get_next_line(0)) == NULL)
	return;
    }
  pick_what_to_add(str, ini);
}

void			add_stuff(int ac, char **av, t_ini *ini)
{
  if (ac == 1)
    add_all(ini);
  if (ac == 2 && my_strcmp(av[1], "player") == 0)
    write_player(ini->player, 1);
}

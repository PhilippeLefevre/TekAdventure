/*
** edit.h for  in /home/sousa_v/rendu/lapin/TekAdventure_temp/inc/
**
** Made by Victor Sousa
** Login   <sousa_v@epitech.eu>
**
** Started on  Sat Apr 16 05:51:56 2016 Victor Sousa
** Last update Sat Apr 16 09:43:43 2016 Victor Sousa
*/

#ifndef			EDIT_H_
# define		EDIT_H_

# include		"main.h"

typedef struct		s_ini
{
  t_player		*player;
  t_scene		*scene;
  t_ptr_list		*ptr_list;
  char			has_been_loaded;
}			t_ini;

int			load_ini(char *path, t_ini *ini);
void			close_ini(t_ini *ini);
void			aff_stuff(int ac, char **av, t_ini *ini);
void			aff_all(int fd, t_ini *ini);

/* write */
int			write_ini(char *path, t_ini *ini);
void			write_player(t_player *player, int fd);
void			write_sprite(t_sprite *sprite, int fd);

char			*get_next_line(const int fd);
void			start_shell();
void			free_tab(char **tab);
char			**str_to_wordtab(char *str, char *separate);

#endif			/* !EDIT_H_ */

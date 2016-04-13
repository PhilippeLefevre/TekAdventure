/*
** main.h for TekAdventure in /home/lefevr_h/Repository/Epitech/Year_1/Infographie/gfx_tekadventure/inc
**
** Made by Philippe Lefevre
** Login   <lefevr_h@epitech.net>
**
** Started on  Mon Mar 28 20:02:40 2016 Philippe Lefevre
** Last update Wed Apr 13 06:24:16 2016 Victor Sousa
*/

#ifndef			MAIN_H_
# define		MAIN_H_

# include		<lapin.h>
# include		<stdlib.h>
# include		<time.h>
# include		<unistd.h>

# include		"utils.h"
# include		"image.h"
# include		"object.h"
# include		"astar.h"
# include		"player.h"
# include		"npc.h"
# include		"decors.h"
# include		"sprite.h"
# include		"scene.h"
# include		"prog.h"
# include		"event.h"
# include		"parsing.h"
# include		"disp.h"

# ifndef		WIN_SETTING
#  define		WIN_SETTING
#  define		WIN_NAME	"TEKADVENTURE"
#  define		WIN_HEIGHT	768
#  define		WIN_WIDTH	1024
# endif			/* !WIN_SETTING */

t_bunny_response	mainloop(void *p);

int			clean(t_prog *prog, int out);

# define		SUCCESS	0
# define		ERROR	-1

#endif			/* !MAIN_H_ */

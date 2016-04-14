/*
** tektext_center.c for image in /Users/leandr_g/Documents/Shared folder/TekAdventure/src/image/
**
** Made by Gaëtan Léandre
** Login   <leandr_g@epitech.eu>
**
** Started on  Fri Apr 15 00:46:50 2016 Gaëtan Léandre
** Last update Fri Apr 15 00:57:20 2016 Gaëtan Léandre
*/

#include	"main.h"

static int	count_space(const char *str, int font_size, int i)
{
  int		size;

  size = 0;
  while (str[i] && str[i] != '\n')
    i++;
  if (i > 1)
    size = (i - 1) * (font_size / 4);
  size += i * font_size;
  return (size / 2);
}

static int	count_line(const char *str, int font_size)
{
  int		i;

  i = 0;
  while (str[i])
    if (str[i] == '\n')
	i++;
  return (((font_size + font_size / 4) * i) / 2);
}

void		tektextcenter(const char *str,
			      const t_bunny_position *pos,
			      t_bunny_pixelarray *out,
			      t_font *font)
{
  int			i;
  int			j;
  t_bunny_position	pix;
  int			sp;

  pix.y = pos->y - count_line(str, font->font_size);
  sp = count_space(str, font->font_size, 0);
  i = 0;
  j = 0;
  while (str[i])
    {
      if (str[i] == '\n')
	{
	  pix.y += font->font_size + font->font_size / 4;
	  j = 0;
	  sp = count_space(str, font->font_size, ++i);
	}
      else
	{
	  pix.x = pos->x + j * font->font_size + (font->font_size / 4) * j - sp;
	  tekchar(out, font, &pix, str[i++]);
	  j++;
	}
    }
}

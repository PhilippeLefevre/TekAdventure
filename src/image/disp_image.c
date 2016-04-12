/*
** disp_image.c for image in /Users/leandr_g/Documents/Shared folder/TekAdventure/src/image/
**
** Made by Gaëtan Léandre
** Login   <leandr_g@epitech.eu>
**
** Started on  Wed Apr  6 23:28:22 2016 Gaëtan Léandre
** Last update Wed Apr 13 00:35:21 2016 Victor Sousa
*/

#include 		"main.h"

void			fill_image(t_bunny_pixelarray *pix, unsigned int col)
{
  t_bunny_position	tmp;
  t_color		color;

  tmp.y = 0;
  color.full = col;
  while (tmp.y < pix->clipable.clip_height)
    {
      tmp.x = 0;
      while (tmp.x < pix->clipable.clip_width)
	{
	  tekpixel(pix, &tmp, &color);
	  tmp.x++;
	}
      tmp.y++;
    }
}

void			put_image(t_texture *bmp,
				  t_bunny_pixelarray *pix,
				  t_bunny_position *pos)
{
  t_bunny_position	tmp;
  int			i;
  int			j;

  i = 0;
  tmp.y = pos->y;
  while (i < bmp->height)
    {
      j = 0;
      tmp.x = pos->x;
      while (j < bmp->width)
	{
	  tektranspa(pix, &tmp, &bmp->color[i][j]);
	  tmp.x++;
	  j++;
	}
      tmp.y++;
      i++;
    }
}

void			place_image(t_hitbox pos,
				    t_hitbox fetch,
				    t_texture *tex,
				    t_bunny_pixelarray *pix)
{
  t_bunny_position	tmp;
  int			i;
  int			j;

  i = 0;
  tmp.y = pos.y;
  while (i < pos.height)
    {
      j = 0;
      tmp.x = pos.x;
      while (j < pos.width)
	{
	  tektranspa(pix, &tmp,
		     &tex->color[(int)(((float)i / (float)pos.height) *
				  (float)(fetch.height) + (float)fetch.y)]
		     [(int)(((float)j / (float)pos.width)
		       * (float)(fetch.width) + (float)fetch.x)]);
	  tmp.x++;
	  j++;
	}
      tmp.y++;
      i++;
    }
}

void			place_image_transpa(t_hitbox *pos,
					    t_hitbox *fetch,
					    t_texture *tex,
					    t_bunny_pixelarray *pix)
{
  t_bunny_position	tmp;
  int			i;
  int			j;
  t_color		col;

  if (fetch == NULL || pos == NULL)
    return;
  tmp.y = (i = -1) * 0 + pos->y;
  while (++i < pos->height)
    {
      j = -1;
      tmp.x = pos->x;
      while (++j < pos->width)
	{
	  col = tex->color[(int)(((float)i / (float)pos->height) *
			    (float)(fetch->height) + (float)fetch->y)]
	  [(int)(((float)j / (float)pos->width)
	    * (float)(fetch->width) + (float)fetch->x)];
	  if (col.argb[ALPHA_CMP] != 0)
	    col.argb[ALPHA_CMP] = PLACE_IMG_ALPHA;
	  tektranspa(pix, &tmp, &col);
	  tmp.x++;
	}
      tmp.y++;
    }
}

void			redim_image(t_hitbox *pos,
				    t_texture *tex,
				    t_bunny_pixelarray *pix)
{
  t_bunny_position	tmp;
  int			i;
  int			j;

  if (pos == NULL)
    return;
  i = 0;
  tmp.y = pos->y;
  while (i < pos->height)
    {
      j = 0;
      tmp.x = pos->x;
      while (j < pos->width)
	{
	  tektranspa(pix, &tmp,
		     &tex->color[(int)(((float)i / (float)pos->height) *
				  (float)(tex->height))]
				  [(int)(((float)j / (float)pos->width)
				    * (float)(tex->width))]);
	  tmp.x++;
	  j++;
	}
      tmp.y++;
      i++;
    }
}

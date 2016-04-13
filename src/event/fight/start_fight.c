/*
** start_fight.c for  in /Users/ethankerdelhue/Documents/Shared/TekAdventure/src/event/fight/
**
** Made by Ethan Kerdelhue
** Login   <kerdel_e@epitech.eu>
**
** Started on  Sun Apr 10 23:41:37 2016 Ethan Kerdelhue
** Last update Wed Apr 13 02:24:23 2016 Ethan Kerdelhue
*/

#include		"main.h"

void	my_putchar(char c)
{
  write(1, &c, 1);
}

void	my_putstr(char *str)
{
  write(1, str, my_strlen(str));
}

int	my_putnbr(int nb)
{
  int	mod;

  mod = 0;
  if (nb < 0)
    {
      my_putchar('-');
      nb = nb * (-1);
    }
  if (nb >= 0)
    {
      if (nb >= 10)
	{
	  mod = (nb % 10);
          nb = (nb - mod) / 10;
	  my_putnbr(nb);
	  my_putchar(48 + mod);
        }
      else
        my_putchar(48 + nb % 10);
    }
  return (0);
}


int			my_puts(char *str, int nb, int flag)
{
  my_putstr(str);
  my_putnbr(nb);
  if (flag == 1)
    my_putchar('\n');
  return (0);
}

int			get_life_player(t_player *player)
{
  int			life_player;

  life_player = player->caract->stamina * 10 + 100;
  return (life_player);
}

int			get_player_magic_damage(t_player *player, t_prog *prog)
{
  int			player_magic_damage;

  player_magic_damage = prog->scene->object->damage *
      (1 + player->caract->intellect / 10);
  return (player_magic_damage);
}

int			get_player_damage(t_player *player, t_prog *prog)
{
  int			player_damage;

  player_damage = prog->scene->object->damage *
      (1 + player->caract->strength / 10);
  return (player_damage);
}

int 			npc_damage(t_npc *npc)
{
  int			damage;
  int			max;
  int			min;

  max = npc->damage * 1200;
  min = npc->damage * 800;
  damage = ((rand() % (max - min)) + min);
  if (((rand() % (100 - 0)) + 0) <= 5)
    {
      damage = damage * 1.5;
      my_putstr("It's critical !\n");
    }
  my_puts("Damage : ", damage / 1000, 1);
  return (damage / 1000);
}

int 			player_damage(t_player *player)
{
  int			damage;
  int			max;
  int			min;

  min = player->damage * 1200;
  max = player->damage * 800;
  damage = ((rand() % (max - min )) + min);
  if (((rand() % (100 - 0)) + 0) <= player->caract->critical)
    {
      damage = damage * 1.5;
      my_putstr("It's critical !\n");
    }
  my_puts("Damage : ", damage / 1000, 1);
  return (damage / 1000);
}

int			prepare_fight(t_prog *prog, t_npc *npc)
{
  if ((prog->fight = xmalloc(sizeof(t_fight), &prog->ptr_list)) == NULL)
    return (-1);
  prog->fight->player = prog->player;
  prog->fight->npc = npc;
  prog->fight->npc->life = 100;
  prog->fight->nb_round = 1;
  prog->fight->round_state = 1;
  prog->fight->player->caract = malloc(sizeof(t_caract));
  prog->fight->player->caract->strength = 5;
  prog->fight->player->caract->critical = 20;
  prog->fight->player->damage = get_player_damage(prog->fight->player, prog);
  prog->fight->npc->damage = 20; /* A INTEGRER AU PARSING DES NPC */
  return (0);
}

void			draw_fight(t_prog *prog)
{
  t_bunny_position	player_pos;

  player_pos.x = prog->player->sprite->width / 2;
  player_pos.y = WIN_HEIGHT / 2 - (prog->player->sprite->height / 2);
  put_image(prog->fight_img, prog->pix, &prog->blit_pos);
  put_image(prog->player->sprite, prog->pix, &player_pos);
}

int			loop_fight(t_prog *prog)
{
  my_puts("Round -> ", prog->fight->nb_round, 1);
  if (prog->fight->round_state == 1)
    {
      prog->fight->npc->life -= npc_damage(prog->fight->npc);
      my_puts("Npc life : ", prog->fight->npc->life, 1);
      prog->fight->nb_round += 1;
      prog->fight->round_state = 2;
    }
  if (prog->fight->round_state == 2)
    {
      prog->fight->player->life -= player_damage(prog->fight->player);
      my_puts("Player life : ", prog->fight->player->life, 1);
      prog->fight->round_state = 1;
    }
  if (prog->player->life <= 0)
    {
      my_puts("npc win\n", 0, 0);
      prog->need_init_fight = 0;
      prog->state = STATE_GAME;
    }
  if  (prog->fight->npc->life <= 0)
    {
      my_puts("player win\n", 0, 0);
      prog->need_init_fight = 0;
      prog->state = STATE_GAME;
    }
  return (0);
}

int			start_fight(t_prog *prog, t_npc *npc)
{
  if (prog->need_init_fight == 1)
    {
      if (prepare_fight(prog, npc) == -1)
	return (-1);
      prog->need_init_fight = 0;
    }
  loop_fight(prog);
  return (0);
}

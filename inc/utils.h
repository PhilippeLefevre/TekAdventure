/*
** utils.h for  in /home/sousa_v/rendu/lapin/TekAdventure_temp
** 
** Made by victor sousa
** Login   <sousa_v@epitech.net>
** 
** Started on  Wed Apr  6 23:08:25 2016 victor sousa
** Last update Wed Apr  6 23:13:33 2016 victor sousa
*/

#ifndef                 UTILS_H_
# define                UTILS_H_

#include		"main.h"

/* PTR LIST */
typedef	struct		s_ptr_list
{
  void			*ptr;
  struct s_ptr_list	*next;
}			t_ptr_list;
t_ptr_list              *push_ptr(t_ptr_list *prev, void *ptr);

#endif                  /* !UTILS_H_ */

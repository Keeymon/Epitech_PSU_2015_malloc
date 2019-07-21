/*
** show_alloc_mem.c for  in /home/picher_y/rendu/PSU_2015_malloc/lib/my
** 
** Made by Yann Pichereau
** Login   <picher_y@epitech.net>
** 
** Started on  Sun Jan 31 16:14:04 2016 Yann Pichereau
** Last update Sun Feb 14 17:09:42 2016 tony truong
*/

#include <stdio.h>
#include "my_malloc.h"

void		show_alloc_mem()
{
  t_block	*tmp;

  tmp = mem.block;
  printf("break: %p\n", sbrk(0));
  while (tmp->n_ptr != NULL)
    tmp = tmp->n_ptr;
  while (tmp != NULL)
    {
      if (tmp->free == FALSE)
	printf("%p - %p : %d bytes\n", tmp,(tmp + tmp->size),
	       (int)(tmp->size + HEADER_SIZE));
      tmp = tmp->p_ptr;
    }
}

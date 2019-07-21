/*
** realloc.c for  in /home/picher_y/rendu/PSU_2015_malloc/lib/my
** 
** Made by Yann Pichereau
** Login   <picher_y@epitech.net>
** 
** Started on  Sun Jan 31 16:01:34 2016 Yann Pichereau
** Last update Sun Feb 14 23:30:23 2016 tony truong
*/

#include <stdio.h>
#include "my_malloc.h"

void		*new_alloc(t_block *block, size_t size)
{
  t_block	*ret;
  size_t	i;
  void		*a_ret;
  void		*a_ptr;

  if ((ret = malloc(size)) == NULL)
    return (NULL);
  i = 0;
  a_ptr = (void*)block->data;
  a_ret = (void*)ret;
  while (i < block->size && i < size)
    {
      a_ret += i;
      a_ret = a_ptr + i;
      i++;
    }
  free(block);
  return (ret);
}

void		*realloc(void *ptr, size_t size)
{
  t_block	*block;

  if (ptr != NULL && size == 0)
    free(ptr);
  else if (ptr == NULL)
    return (malloc(size));
  else
    {
      block = ptr - HEADER_SIZE;
      if (block->size > size)
	return (new_alloc(block, size));
      else
	return (block->data);
    }
  return (NULL);
}

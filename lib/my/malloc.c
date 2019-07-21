/*
** malloc.c for  in /home/picher_y/rendu/PSU_2015_malloc/lib/my
** 
** Made by Yann Pichereau
** Login   <picher_y@epitech.net>
** 
** Started on  Sun Jan 31 16:00:44 2016 Yann Pichereau
** Last update Sun Feb 14 23:22:25 2016 tony truong
*/

#include <stdio.h>
#include "my_malloc.h"

t_mem	mem = {NULL, NULL, 0, NULL, SIZE, {NULL}};

void		*split_assign(size_t size, t_block *block, t_block *new)
{
  new->size = block->size - size - HEADER_SIZE;
  new->pow = pmax(new->size);
  new->free = TRUE;
  new->data = (void*)new + HEADER_SIZE;
  block->p_ptr = new;
  block->n_size = NULL;
  block->p_size = NULL;
  block->size = size;
  block->pow = pmax(block->size);
  block->free = FALSE;
  pos_block(new);
  return (block->data);
}

void		*split_block(size_t size, t_block *block)
{
  t_block	*new;

  if (mem.hashtab[block->pow - 1] == block)
    {
      if (block->n_size != NULL && block->n_size->pow == block->pow)
	mem.hashtab[block->pow - 1] = block->n_size;
      else
	mem.hashtab[block->pow - 1] = NULL;
    }
  if (mem.empty == block)
    mem.empty = block->n_size;
  new = (void*)block + size + HEADER_SIZE;
  new->n_ptr = block;
  new->p_ptr = block->p_ptr;
  new->n_size = NULL;
  new->p_size = NULL;
  if (block->n_size != NULL)
    block->n_size->p_size = block->p_size;
  if (block->p_size != NULL)
    block->p_size->n_size = block->n_size;
  return (split_assign(size, block, new));
}

void		*available_block(size_t size, size_t i)
{
  t_block	*tmp;

  tmp = mem.hashtab[i];
  while (tmp != NULL)
    {
      if (tmp->size >= size)
	{
	  if (tmp->size >= size + HEADER_SIZE + ALIGNEMENT)
	    return (split_block(size, tmp));
	  if (tmp->p_size != NULL)
	    tmp->p_size->n_size = tmp->n_size;
	  if (tmp->n_size != NULL)
	    tmp->n_size->p_size = tmp->p_size;
	  tmp->free = FALSE;
	  return (tmp->data);
	}
      tmp = tmp->n_size;
    }
  return (NULL);
}

void		*brow_hashtab(size_t size, size_t pow)
{
  size_t	i;
  void		*ptr;

  i = pow - 2;
  while (++i < mem.size_tab)
    {
      if (mem.hashtab[i] != NULL)
	{
	  if ((ptr = available_block(size, i)) != NULL)
	    return (ptr);
	}
    }
  return (NULL);
}

void		*malloc(size_t size)
{
  int		pow;
  void		*ptr;

  size = get_realsize(size, &pow);
  if (mem.empty != NULL)
    {
      if ((ptr = brow_hashtab(size, pow)) != NULL)
	return (ptr);
    }
  if (up_sbrk(size + HEADER_SIZE) == (void*)-1)
    return (NULL);
  return (add_block(size, pow));
}

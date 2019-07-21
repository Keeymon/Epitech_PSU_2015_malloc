/*
** alloc_funct.c for  in /home/picher_y/rendu/PSU_2015_malloc/lib/my
** 
** Made by Yann Pichereau
** Login   <picher_y@epitech.net>
** 
** Started on  Sun Jan 31 22:52:29 2016 Yann Pichereau
** Last update Sun Feb 14 23:22:27 2016 tony truong
*/

#include "my_malloc.h"

void	*up_sbrk(size_t size)
{
  if (mem.last_ptr == NULL)
    {
      if ((mem.last_ptr = sbrk(0)) == (void*)-1)
	return (mem.last_ptr);
    }
  if (size > mem.available)
    {
      if (size < PAGESIZE)
	{
	  mem.available += (PAGESIZE - size);
	  return (sbrk(PAGESIZE));
	}
      mem.available += PAGESIZE;
      return (sbrk(size + PAGESIZE));
    }
  else
    {
      mem.available -= size;
      return (0);
    }
}

void		*add_block(size_t size, size_t pow)
{
  t_block	*new;

  if (mem.block == NULL)
    {
      mem.block = mem.last_ptr;
      mem.block->n_ptr = NULL;
      mem.block->p_ptr = NULL;
    }
  else
    {
      new = mem.last_ptr;
      new->n_ptr = mem.block;
      new->p_ptr = NULL;
      mem.block->p_ptr = new;
      mem.block = new;
    }
  mem.block->n_size = NULL;
  mem.block->p_size = NULL;
  mem.block->size = size;
  mem.block->pow = pow;
  mem.block->free = FALSE;
  mem.block->data = mem.last_ptr + HEADER_SIZE;
  mem.last_ptr += size + HEADER_SIZE;
  return (mem.block->data);
}

int	pmax(size_t size)
{
  int	i;

  i = 0;
  while (size > ((size_t)1 << i))
    i++;
  return (i);
}

size_t		get_realsize(size_t size, int *pow)
{
  size_t	i;

  if (size <= ALIGNEMENT)
    {
      *pow = pmax(ALIGNEMENT);
      return (ALIGNEMENT);
    }
  i = (((size - 1) >> D_BIN) << D_BIN) + ALIGNEMENT;
  *pow = pmax(i);
  return (i);
}

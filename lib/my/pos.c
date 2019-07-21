/*
** pos.c for  in /home/truong_g/rendu/PSU_2015_malloc/lib/my
** 
** Made by tony truong
** Login   <truong_g@epitech.net>
** 
** Started on  Sun Feb 14 22:30:16 2016 tony truong
** Last update Sun Feb 14 23:39:39 2016 tony truong
*/

#include <stdio.h>
#include "my_malloc.h"

int		pow_sup(t_block *tmp)
{
  size_t        pow;

  pow = tmp->pow - 1;
  while (mem.hashtab[pow] == NULL && pow > 0)
    pow = pow - 1;
  return (pow);
}

int		fdn_block(t_block *block)
{
  t_block	*tmp;
  size_t	pow;

  pow = block->pow - 1;
  while (mem.hashtab[pow] == NULL && pow < SIZE)
    pow = pow + 1;
  if (pow == SIZE)
    return (FALSE);
  tmp = mem.hashtab[pow];
  block->n_size = tmp;
  block->p_size = tmp->p_size;
  if (tmp->p_size != NULL)
    tmp->p_size->n_size = block;
  tmp->p_size = block;
  if (mem.empty == tmp && tmp->size < block->size)
    mem.empty = block;
  mem.hashtab[block->pow - 1] = block;
  return (TRUE);
}

int		fdp_block(t_block *block)
{
  t_block	*tmp;
  size_t	p;

  if ((p = pow_sup(block)) == 0)
    return (FALSE);
  tmp = mem.hashtab[p];
  while (tmp->n_size != NULL && tmp->size <= block->size)
    tmp = tmp->n_size;
  if (tmp->n_size == NULL)
    {
      tmp->n_size = block;
      block->p_size = tmp;
    }
  else
    {
      block->n_size = tmp;
      block->p_size = tmp->p_size;
      tmp->p_size = block;
      mem.empty = (mem.empty = tmp) ? block : mem.empty;
    }
  if (mem.hashtab[block->pow - 1] == NULL)
    mem.hashtab[block->pow - 1] = block;
  else if (mem.hashtab[p] == block->n_size && block->n_size->size < block->size)
    mem.hashtab[block->pow - 1] = block;
  return (TRUE);
}

void	        pos_block(t_block *block)
{
  if (mem.empty == NULL)
    {
      mem.empty = block;
      mem.hashtab[block->pow - 1] = block;
    }
  else if (fdp_block(block) == FALSE)
    fdn_block(block);
}

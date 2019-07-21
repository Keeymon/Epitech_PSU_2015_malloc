/*
** free.c for  in /home/picher_y/rendu/PSU_2015_malloc/lib/my
** 
** Made by Yann Pichereau
** Login   <picher_y@epitech.net>
** 
** Started on  Sun Jan 31 16:00:06 2016 Yann Pichereau
** Last update Sun Feb 14 22:48:49 2016 tony truong
*/

#include <stdio.h>
#include "my_malloc.h"

t_block		*ctp_block(t_block *tmp)
{
  if (mem.empty == tmp->p_ptr)
    mem.empty = tmp;
  if (mem.hashtab[tmp->p_ptr->pow - 1] == tmp->p_ptr)
    {
      if (tmp->p_ptr->n_size != NULL &&
	  tmp->p_ptr->n_size->pow == tmp->p_ptr->pow)
	mem.hashtab[tmp->p_ptr->pow - 1] = tmp->p_ptr->n_size;
      else
	mem.hashtab[tmp->p_ptr->pow - 1] = NULL;
    }
  if (tmp->p_ptr->p_size != NULL)
    tmp->p_ptr->p_size->n_size = tmp->p_ptr->n_size;
  if (tmp->p_ptr->n_size != NULL)
    tmp->p_ptr->n_size->p_size = tmp->p_ptr->p_size;
  tmp->size += tmp->p_ptr->size + HEADER_SIZE;
  tmp->p_ptr = tmp->p_ptr->p_ptr;
  return (tmp);
}

t_block	        *ctn_block(t_block *tmp)
{
  if (mem.block == tmp)
    mem.block = tmp->n_ptr;
  if (mem.hashtab[tmp->n_ptr->pow - 1] == tmp->n_ptr)
    {
      if (tmp->n_ptr->n_size != NULL &&
	  tmp->n_ptr->n_size->pow == tmp->n_ptr->pow)
	mem.hashtab[tmp->n_ptr->pow - 1] = tmp->n_ptr->n_size;
      else
	mem.hashtab[tmp->n_ptr->pow - 1] = NULL;
    }
  if (tmp->n_ptr->p_size != NULL)
    tmp->n_ptr->p_size->n_size = tmp->n_ptr->n_size;
  if (tmp->n_ptr->n_size != NULL)
    tmp->n_ptr->n_size->p_size = tmp->n_ptr->p_size;
  tmp->n_ptr->size += tmp->size + HEADER_SIZE;
  tmp->n_ptr->p_ptr = tmp->p_ptr;
  tmp = tmp->n_ptr;
  return (tmp);
}

t_block		*cat_block(t_block *tmp)
{
  if (tmp->p_ptr != NULL && tmp->p_ptr->free == TRUE)
    tmp = ctp_block(tmp);
  if (tmp->n_ptr != NULL && tmp->n_ptr->free == TRUE)
    tmp = ctn_block(tmp);
  if (mem.empty == tmp)
    mem.empty = tmp->n_size;
  tmp->n_size = NULL;
  tmp->p_size = NULL;
  get_realsize(tmp->size, &(tmp->pow));
  return (tmp);
}

void		free(void *ptr)
{
  t_block	*block;

  block = ptr - HEADER_SIZE;
  if (ptr == NULL || block->free == TRUE)
    {
      ptr = NULL;
      return ;
    }
  block->free = TRUE;
  block = cat_block(block);
  pos_block(block);
  ptr = NULL;
}

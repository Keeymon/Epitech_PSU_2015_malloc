/*
** calloc.c for  in /home/truong_g/rendu/PSU_2015_malloc/lib/my
** 
** Made by tony truong
** Login   <truong_g@epitech.net>
** 
** Started on  Sun Feb 14 17:56:50 2016 tony truong
** Last update Sun Feb 14 18:02:21 2016 tony truong
*/

#include <stdio.h>
#include "my_malloc.h"

void	*calloc(size_t nmemb, size_t size)
{
  if (nmemb == 0)
    return (NULL);
  if (size == 0)
    return (malloc(0));
  (void)size;
  return (NULL);
}

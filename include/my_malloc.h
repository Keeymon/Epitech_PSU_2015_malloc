/*
** my_malloc.h for  in /home/picher_y/rendu/PSU_2015_malloc/lib/my
** 
** Made by Yann Pichereau
** Login   <picher_y@epitech.net>
** 
** Started on  Sun Jan 31 15:55:57 2016 Yann Pichereau
** Last update Sun Feb 14 23:22:17 2016 tony truong
*/

#ifndef MY_MALLOC_H_
# define MY_MALLOC_H_

# include <pthread.h>
# include <unistd.h>

# ifndef __X86_64__
#  define ALIGNEMENT (16)
#  define SIZE (64)
#  define D_BIN (4)
# else
#  define ALIGNEMENT (8)
#  define SIZE (32)
#  define D_BIN (2)
# endif /* !__X86_64__ */

# define PAGESIZE ((size_t)getpagesize())
# define TRUE (42)
# define FALSE (21)

typedef struct		s_block
{
  struct s_block	*n_ptr;
  struct s_block	*p_ptr;
  struct s_block	*n_size;
  struct s_block	*p_size;
  void			*data;
  size_t		size;
  int			pow;
  int			free;
}			t_block;

# define HEADER_SIZE (sizeof(t_block))

typedef struct	s_mem
{
  t_block	*block;
  t_block	*empty;
  size_t	available;
  void		*last_ptr;
  size_t	size_tab;
  t_block	*hashtab[SIZE];
}		t_mem;

extern t_mem	mem;

void	*malloc(size_t size);
void	*realloc(void *ptr, size_t szie);
void	free(void *ptr);
void	show_alloc_mem();
int	pmax(size_t size);
size_t	get_realsize(size_t size, int *pow);
void	*up_sbrk(size_t size);
void	*add_block(size_t size, size_t pow);
void	pos_block(t_block *tmp);

#endif /* !MY_MALLOC_H_ */

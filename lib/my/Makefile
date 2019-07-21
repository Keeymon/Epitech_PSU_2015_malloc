##
## Makefile for  in /home/picher_y/rendu/PJ10/lib/my
## 
## Made by Yann Pichereau
## Login   <picher_y@epitech.net>
## 
## Started on  Mon Oct 12 10:10:26 2015 Yann Pichereau
## Last update Mon Feb 15 00:23:56 2016 Yann Pichereau
##

NAME	=	libmy_malloc.so

INCLUDE =	my_malloc.h

CC	=	gcc

CP	=	cp

RM	=	rm -rf

CFLAGS	+=      -W -Wall -Wextra -Werror
CFLAGS	+=	-I.
CFLAGS	+=	-c -fPIC

LDFLAGS	+=	-shared

SRCS	=	malloc.c	\
		realloc.c	\
		free.c		\
		show_alloc_mem.c\
		alloc_funct.c	\
		pos.c

OBJS	=       $(SRCS:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CC) $(LDFLAGS) -lm -o $(NAME) $(OBJS)
		$(CP) $(INCLUDE) ../../include
		$(CP) $(NAME) ..
		$(CP) $(INCLUDE) ../..
		$(CP) $(NAME) ../..
		export LD_LIBRARY_PATH=..

clean:
		$(RM) $(OBJS)

fclean:
		$(RM) $(OBJS)
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re

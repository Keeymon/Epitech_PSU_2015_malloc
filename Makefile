##
## Makefile for  in /home/truong_g/rendu/PSU_2015_malloc
## 
## Made by tony truong
## Login   <truong_g@epitech.net>
## 
## Started on  Fri Feb  5 20:30:38 2016 tony truong
## Last update Sun Feb 14 17:07:41 2016 tony truong
##

NAME	=	malloc

CC	=	gcc

RM	=	rm -rf

CFLAGS	+=	-W -Wall -Werror -Wextra
CFLAGS	+=	-lmy_malloc -L./lib/ -I./include/

SRCS	=	main.c

OBJS	=	$(SRCS:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
		make -C ./lib/my/
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
		make clean -C ./lib/my/
		$(RM) $(OBJS)

fclean:
		make fclean -C ./lib/my/
		$(RM) $(OBJS)
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re

##
## Makefile for  in /home/thomas/Documents/epitech/CPE_2015_Pushswap
## 
## Made by Thomas Henon
## Login   <thomas.henon@epitech.eu>
## 
## Started on  Mon Nov 16 11:18:58 2015 Thomas Henon
## Last update Fri Jan 29 12:47:22 2016 Thomas HENON
##

NAME	= navy

GCC	= gcc

RM	= rm -f

SRCS	=	main.c \
		util.c \
		linked_lists.c \
		file.c \
		navy_positions.c \
		parsing.c \
		signal.c \
		game.c \
		packets.c

CFLAGS = -l my -L ./my -I ./my

OBJS	= $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(GCC) $(OBJS) -o $(NAME) $(CFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

all: $(NAME)

re: fclean all

.PHONY: all clean fclean re

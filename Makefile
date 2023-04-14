# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/11 16:04:53 by mogawa            #+#    #+#              #
#    Updated: 2023/04/14 14:21:52 by mogawa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	pipex
CC			=	cc
#CFLAGS		=	-Wall -Wextra -Werror
CFLAGS		=	-Wall
AR			=	ar rcs
RM			=	rm -f
FILES		=	pipex
SRCS_DIR	=	./
SRCS		=	$(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))
SRCS_B		=	$(addprefix $(SRCS_DIR), $(addsuffix .c, $(BONUS_FILES)))

OBJS		=	$(SRCS:.c=.o)
OBJS_B		=	$(SRCS_B:.c=.o)

ifdef WITH_DEBUG
CFLAGS += -g3 -O0 -fsanitize=address -fno-omit-frame-pointer
endif

%.o : %.c 
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	make -C ./libft
	$(CC) $(CFLAGS) $(OBJS) ./libft/libft.a -o $(NAME)

debug: fclean
	make $(NAME) WITH_DEBUG=1

all: $(NAME)

clean:
	$(RM) $(OBJS) $(OBJS_B)
	make -C ./libft clean

fclean: clean
	$(RM) $(NAME)
	make -C ./libft fclean

re: fclean all

.PHONY: debug all clean fclean re




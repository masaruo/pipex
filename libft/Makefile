# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/11 16:04:53 by mogawa            #+#    #+#              #
#    Updated: 2023/04/25 12:42:45 by mogawa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libft.a
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
AR			=	ar rcs
RM			=	rm -f
FILES		=	ft_isalpha ft_isdigit ft_isalnum ft_isascii ft_isprint ft_strlen ft_memset \
				ft_bzero ft_memcpy ft_memmove ft_strlcpy ft_toupper ft_tolower ft_strlcat \
				ft_strchr ft_strrchr ft_strcmp ft_memchr ft_memcmp ft_atoi \
				ft_calloc ft_strdup \
				ft_substr ft_strjoin ft_strtrim ft_split ft_itoa ft_strmapi ft_striteri \
				ft_putchar_fd ft_putstr_fd ft_putendl_fd ft_putnbr_fd
BONUS_FILES	=	ft_lstnew ft_lstadd_front ft_lstsize ft_lstlast ft_lstadd_back ft_lstdelone \
				ft_lstclear ft_lstiter ft_lstmap

SRCS_DIR	=	./
SRCS		=	$(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))
SRCS_B		=	$(addprefix $(SRCS_DIR), $(addsuffix .c, $(BONUS_FILES)))

OBJS		=	$(SRCS:.c=.o)
OBJS_B		=	$(SRCS_B:.c=.o)

ifdef WITH_BONUS
OBJS += $(OBJS_B)
endif

ifdef WITH_DEBUG
CFLAGS += -g3 -O0 -fsanitize=address -fno-omit-frame-pointer
endif

%.o : %.c 
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	$(AR) $@ $^

bonus:
	make $(NAME) WITH_BONUS=1

debug: fclean
	make $(NAME) WITH_DEBUG=1

all: $(NAME)

clean:
	$(RM) $(OBJS) $(OBJS_B)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: bonus debug all clean fclean re




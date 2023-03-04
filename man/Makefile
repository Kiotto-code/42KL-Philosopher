# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yichan <yichan@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/05 18:29:34 by yichan            #+#    #+#              #
#    Updated: 2023/02/05 18:29:34 by yichan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
 
NAME    =   philo
CC		=	gcc
RM		=	rm -rf
CFLAGS	=	-Wall -Werror -Wextra -g3
CFLAGS	+=	-pthread
# CFLAGS	+=	-fsanitize=thread
CFLAGS	+=	-fsanitize=address
INCLUDES	= ./includes
SRC_PATH	= ./srcs
OBJ_PATH	= ./obj

SRCS	= $(wildcard ./*/pl_*.c)
OBJS	= ${SRCS:./srcs/%.c=${OBJ_PATH}/%.o}

all				:	$(NAME)

$(NAME)			:	$(OBJS)
					$(CC) $(CFLAGS) $^ -I $(INCLUDES) -o $@

$(OBJ_PATH)/%.o	:	$(SRC_PATH)/%.c* ./includes/*.h ./Makefile | $(OBJ_PATH)
					$(CC) $(CFLAGS) -c -I$(INCLUDES) $< -o $@

$(OBJ_PATH)		:
					mkdir -p $(OBJ_PATH)

clean			:
					rm -rf $(OBJ_PATH)

fclean			:	clean
					rm -rf $(NAME)

re				:	fclean all

.PHONY			: all clean fclean re
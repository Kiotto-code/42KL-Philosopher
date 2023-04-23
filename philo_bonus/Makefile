# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yichan <yichan@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/15 16:27:06 by yichan            #+#    #+#              #
#    Updated: 2023/04/23 21:51:24 by yichan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= philo_bonus
CC	 		= gcc
RM	 		= rm -rf
CFLAGS		= -Wall -Werror -Wextra -g3 
# CFLAGS		+= -pthread
CFLAGS		+= 	-g -fsanitize=thread
INCLUDE 	= ./include
SRC_PATH 	= ./srcs
OBJ_PATH	= ./obj

SRCS	= $(wildcard $(SRC_PATH)/*.c )
# OBJS	= $(patsubst %.c,$(OBJ_PATH)/%.o,$(notdir $(SRCS)))
OBJS 	= $(patsubst $(SRC_PATH)/%.c, $(OBJ_PATH)/%.o, $(SRCS))

all		:	$(NAME)

$(NAME)	:	$(OBJS)
			$(CC) $(CFLAGS) $^ -I$(INCLUDE) -o $@

$(OBJ_PATH)/%.o	:	$(SRC_PATH)/%.c* $(INCLUDE)/*.h ./Makefile | $(OBJ_PATH)
					$(CC) $(CFLAGS) -c -I$(INCLUDE) $< -o $@

$(OBJ_PATH)		:
					mkdir -p $(OBJ_PATH)

clean			:	
					$(RM) $(OBJ_PATH)


fclean			:	clean
					$(RM) $(NAME)

re				:	fclean all

.PHONY			:	all clean fclean re
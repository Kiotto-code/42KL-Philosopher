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
# CFLAGS	+=	-pthread
# CFLAGS	+=	-fsanitize=thread
# CFLAGS	+=	-fsanitize=address
INCLUDES	= ./includes
SRC_PATH	= ./srcs
OBJ_PATH	= ./obj

SRCS	= $(wildcard ./*/pl_*.c)
OBJS 	= $(patsubst $(SRC_PATH)/%.c, $(OBJ_PATH)/%.o, $(SRCS))


all				:	$(NAME)

$(NAME)			:	$(OBJS)
					$(CC) $(CFLAGS) $^ -I$(INCLUDES) -o $@

$(OBJ_PATH)/%.o	:	$(SRC_PATH)/%.c* $(INCLUDES)/*.h ./Makefile | $(OBJ_PATH)
					$(CC) -c -I$(INCLUDES) $< -o $@

$(OBJ_PATH)		:
					mkdir -p $(OBJ_PATH)

clean			:
# $(MAKE) -C $(LIBFT_PATH) $@
					$(RM) $(OBJ_PATH)

fclean			:	clean
# $(MAKE) -C $(LIBFT_PATH) $@
					$(RM) $(NAME)

re				:	fclean all

.PHONY			: all clean fclean re
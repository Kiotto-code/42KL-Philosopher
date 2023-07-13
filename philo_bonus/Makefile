# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yichan <yichan@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/05 18:29:34 by yichan            #+#    #+#              #
#    Updated: 2023/07/13 10:23:29 by yichan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    =   philo_bonus
CC		=	cc
RM		=	rm -rf
CFLAGS	=	-Wall -Werror -Wextra -g3
# CFLAGS	+=	-pthread
SANT	=	-fsanitize=thread
# CFLAGS	+=	-fsanitize=address
INCLUDES	= ./includes
SRC_PATH	= ./srcs
OBJ_PATH	= ./obj

SRCS	= $(wildcard ./*/*.c)
OBJS 	= $(patsubst $(SRC_PATH)/%.c, $(OBJ_PATH)/%.o, $(SRCS))


all				:	$(NAME)

$(NAME)			:	$(OBJS)
					$(CC) $(CFLAGS) $(SANT) $^ -I$(INCLUDES) -o $@

# $(OBJ_PATH)/%.o	:	$(SRC_PATH)/%.c* $(INCLUDES)/*.h ./Makefile | $(OBJ_PATH)
# 					$(CC) $(CFLAGS) -c -I$(INCLUDES) $< -o $@
$(OBJ_PATH)/%.o	:	$(SRC_PATH)/%.c $(INCLUDES) Makefile
					mkdir -p $(@D)
					$(CC) $(CFLAGS) $(SANT) -c -I$(INCLUDES) $< -o $@

# $(OBJ_PATH)		:
# 					mkdir -p $(OBJ_PATH)

clean			:
# $(MAKE) -C $(LIBFT_PATH) $@
					$(RM) $(OBJ_PATH)

fclean			:	clean
# $(MAKE) -C $(LIBFT_PATH) $@
					$(RM) $(NAME)

re				:	fclean all

.PHONY			:	all clean fclean re

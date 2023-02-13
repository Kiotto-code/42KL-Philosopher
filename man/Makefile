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
CFLAGS	=	-Wall -Werror -Wextra #-fsanitize=thread -g
# CFLAGS	=	-Wall -Werror -Wextra -fsanitize=address -g
INCLUDES	= ./includes
SRC_PATH	= ./srcs
OBJ_PATH	= ./obj

# SRCS	= $(foreach x, $(SRC_PATH), $(wildcard $(addprefix $(x)/*,.c*)))
SRCS	= $(wildcard ./*/pl_*.c)
# OBJS	= $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRCS)))))
# OBJS	= $(patsubst %$(OBJ_PATH)/*, %$(SRC_PATH)/*, $(patsubst %.o, %.c, ${SRCS}))
OBJS	= $(addprefix $(OBJ_PATH)/, $(patsubst %.c, %.o, $(notdir ${SRCS})))
# OBJS	= $(patsubst %$(SRC_PATH)/*.c, %$(OBJ_PATH)/*.o, ${SRCS})

all				:	$(NAME)

$(NAME)			:	$(OBJS)
					$(CC) $(CFLAGS) $^ -I $(INCLUDES) -o $@

$(OBJ_PATH)/%.o	:	$(SRC_PATH)/%.c* | $(OBJ_PATH)
					$(CC) $(CFLAGS) -c -I$(INCLUDES) $< -o $@

$(OBJ_PATH)		:
					mkdir -p $(OBJ_PATH)

clean			:
					rm -rf $(OBJ_PATH)

fclean			:	clean
					rm -rf $(NAME)

re				:	fclean all

.PHONY			: all clean fclean re
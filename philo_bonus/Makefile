NAME = philo
CC	 = gcc
RM	 = rm -rf
CFLAGS	= -Wall -Werror -Wextra -g3
INCLUDE = ./includes
SRCS_DIR = ./srcs
OBJ_DIR	 = ./obj

SRCS	= $(wildcard $(SRCS_DIR)/*.c )
OBJS 	= $(patsubst $(SRCS_DIR)/%.c , $(OBJ_DIR)/%.o, $(SRCS))

all		:	$(NAME)

$(NAME)	:	$(OBJS)
			$(CC) $(CFLAGS) $^ -I$(INCLUDE) -o $@

$(OBJ_PATH)/%.o	:	$(SRC_PATH)/%.c $(INCLUDE)/*.h ./Makefile | $(OBJ_PATH)
					$(CC) $(CFLAGS) -c -I$(INCLUDE) $< -o $@

$(OBJ_PATH)		:
					mkdir -p $(OBJ_PATH)

clean			:	
					$(RM) $(OBJ_PATH)


fclean			:	clean
					$(RM) $(NAME)

re				:	fclean all

.PHONY			:	all clean fclean re
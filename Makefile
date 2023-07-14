
SOURCE_DIR	= srcs/
SOURCES		= vector_utils/basic_op.c \
		  	  vector_utils/utils.c \
			  parsing/ft_atof.c \
			  parsing/parsing_utils.c \
			  parsing/set_infos.c \
			  parsing/add_shape.c \
			  parsing/add_infos.c \
			  parsing/count_nb_shapes.c \
			  parsing/parsing.c \
		  	  equation_shapes.c \
		  	  geometry.c \
		  	  main.c \
		  	  utils.c \
		  	  strategy.c

OBJ_DIR		= objs/
OBJS		= ${SOURCES:.c=.o}
OBJS		:= $(addprefix ${OBJ_DIR}, ${OBJS})

NAME	= miniRT

MLX_DIR	= lib/mlx
CC		= gcc #-g3 -fsanitize=address
CFLAGS	= -Wall -Wextra -Werror -Ilib/mlx
RM		= rm -f
AR		= ar rc

define libft_make
	cd lib/libft && ${MAKE} $(1) && cd ..
endef

${OBJ_DIR}%.o: ${SOURCE_DIR}%.c
		mkdir -p ${OBJ_DIR}
		mkdir -p ${OBJ_DIR}/vector_utils
		mkdir -p ${OBJ_DIR}/parsing
		${CC} ${CFLAGS} -Imlx -c $< -o $@

all:	${NAME}

${NAME}:	${OBJS}
			$(call libft_make, libft.a)
			@echo "\033[95m\nCompiling mlx...\033[0m"
			make -C ${MLX_DIR}
			@echo "\033[95m\nGenerating miniRT file...\033[0m"
			#${CC} ${OBJS} -Llib/libft -lft -Llib/mlx -lmlx -lXext -lX11 -lm -o $@
			${CC} -Llib/libft -lft -Llib/mlx -lmlx -framework OpenGL -framework Appkit -o ${NAME} ${OBJS}

clean:		only_clean
			$(call libft_make, clean)

only_clean:
			@echo "\033[91mclean mlx\033[0m"
			make -C ${MLX_DIR} clean
			${RM} ${OBJS}
			rm -rf ${OBJ_DIR}

fclean:		only_clean
			$(call libft_make, fclean)
	   		${RM} ${NAME}
			${RM} libmlx.dylib

re:		fclean all

.PHONY:	all clean fclean re


CC = cc

NAME = cub3D

SRCS = main.c draw_buffer.c execution_main.c fill_buffer_util.c init_structs.c \
		init_screen_util.c key_press.c floor_and_ceiling.c
		

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror -fsanitize=address

MLXFLAGS =  -L./minilibx -lmlx -framework OpenGL -framework AppKit

all : $(NAME)

LIBFTA = ./libft/libft.a
MLXA = ./minilibx/libmlx.a

$(NAME) : $(OBJS)
	$(MAKE) bonus -C ./libft
	$(MAKE) -C ./minilibx
	$(CC) $(CFLAGS) ${LIBFTA} ${MLXA} $(MLXFLAGS) $^ -o ${NAME}
	
%.o : %.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -f ${OBJS}
	rm -f ${B_OBJS}
	$(MAKE) -C libft clean
	$(MAKE) -C minilibx clean

fclean : clean
	rm -f ${NAME}
	rm -f ${B_NAME}
	$(MAKE) -C libft clean
	$(MAKE) -C minilibx clean

re : 
	$(MAKE) fclean 
	$(MAKE) all

.PHONY : all
.PHONY : clean
.PHONY : fclean
.PHONY : re
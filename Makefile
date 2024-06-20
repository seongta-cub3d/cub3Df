CC = cc

NAME = cub3D

SRCS = main.c init_structs.c

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
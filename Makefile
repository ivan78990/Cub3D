SRCDIR	= ./src

SRC = ./src/bmp.c \
./src/check_map.c \
./src/cub3d.c \
./src/draw.c \
./src/draw_more.c \
./src/drawsprite.c \
./src/freewin.c \
./src/getsprite.c \
./src/key.c \
./src/move.c \
./src/parse.c \
./src/parseparams.c \
./src/parsing_utils.c \
./src/parsingmap.c \
./src/screen.c \
./src/screen_more.c \
./src/splitmap.c \
./src/tools.c \


MLXDIR		=	./minilibx_mms/
MNAME		=	libmlx.dylib

LIBFTDIR	=	libft

LMLX	=	-L$(MLXDIR) -lmlx -framework OpenGL -framework AppKit

OBJS	=	$(SRC:.c=.o)


HEAD	=	./src/cub3d.h $(MLXDIR)/mlx.h

NAME    =   cub3D

RM		= 	rm -f

CC     =   gcc -g -Wall -Wextra -Werror

NORM   =   norminettev2

$(NAME):	$(OBJS) $(HEAD)
			make -C $(MLXDIR)
			make bonus -C $(LIBFTDIR)
			@cp $(MLXDIR)$(MNAME) $(MNAME)
			$(CC) $(OBJS) ./libft/libft.a $(LMLX) -o $(NAME)

all:		$(NAME)

clean:
			$(RM) $(OBJS)
			make clean -C $(LIBFTDIR)
			make clean -C $(MLXDIR)

mlx:
			make -C $(MLXDIR)


fclean:		clean
			$(RM) $(NAME)
			make fclean -C $(LIBFTDIR)
			$(RM) $(MNAME)

re:			fclean all




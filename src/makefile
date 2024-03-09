
CC = cc
CFLAGS = -Wall -Wextra -g -fsanitize=leak
LIB_DIR = /home/abdellah/Desktop/project/fdf/lib
LIBS = -lXext -lX11 -lm -lbsd -lft -lftgnl -lftprintf -lmlx_Linux
SOURCES = rendering_engine.c map_parser.c fdf.c hex_to_dec.c map_parser_utils.c fdf_utils.c engine_utils.c draw_sides.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = fdf
all: $(EXECUTABLE)
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -L$(LIB_DIR) $(LIBS) -o $@
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJECTS)
fclean: clean
	rm -f $(EXECUTABLE)
re: fclean all
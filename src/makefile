CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=leak
LIB_DIR = /home/abdo1/Desktop/projects/fdf/lib
LIBS = -lXext -lX11 -lm -lbsd -lft -lftgnl -lftprintf -lmlx_Linux
SOURCES = rendering_engine.c map_parser.c fdf.c hex_to_dec.c map_parser_utils.c nodes_utils.c engine_utils.c draw_sides.c define_scal.c
OBJECTS = rendering_engine.o map_parser.o fdf.o hex_to_dec.o map_parser_utils.o nodes_utils.o engine_utils.o draw_sides.o define_scal.o
EXECUTABLE = fdf

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -L$(LIB_DIR) $(LIBS) -o $@

rendering_engine.o: rendering_engine.c
	$(CC) $(CFLAGS) -c rendering_engine.c -o rendering_engine.o

map_parser.o: map_parser.c
	$(CC) $(CFLAGS) -c map_parser.c -o map_parser.o

fdf.o: fdf.c
	$(CC) $(CFLAGS) -c fdf.c -o fdf.o

hex_to_dec.o: hex_to_dec.c
	$(CC) $(CFLAGS) -c hex_to_dec.c -o hex_to_dec.o

map_parser_utils.o: map_parser_utils.c
	$(CC) $(CFLAGS) -c map_parser_utils.c -o map_parser_utils.o

nodes_utils.o: nodes_utils.c
	$(CC) $(CFLAGS) -c nodes_utils.c -o nodes_utils.o

engine_utils.o: engine_utils.c
	$(CC) $(CFLAGS) -c engine_utils.c -o engine_utils.o

draw_sides.o: draw_sides.c
	$(CC) $(CFLAGS) -c draw_sides.c -o draw_sides.o

define_scal.o: define_scal.c
	$(CC) $(CFLAGS) -c define_scal.c -o define_scal.o

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(EXECUTABLE)

re: fclean all

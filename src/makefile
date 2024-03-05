# Compiler
CC = cc

# Compiler flags
CFLAGS = -Wall -Wextra -Werror -fsanitize=leak

# Directories
LIB_DIR = /home/abdellah/Desktop/project/fdf/lib

# Libraries
LIBS = -lXext -lX11 -lm -lbsd -lft -lftgnl -lftprintf -lmlx_Linux

# Source files
SOURCES = rendering_engine.c map_parser.c fdf.c hex_to_dec.c

# Object files
OBJECTS = $(SOURCES:.c=.o)

# Executable name
EXECUTABLE = fdf

# Default target
all: $(EXECUTABLE)

# Compile and link
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -L$(LIB_DIR) $(LIBS) -o $@

# Compile source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean objects
clean:
	rm -f $(OBJECTS)

# Clean objects and executable
fclean: clean
	rm -f $(EXECUTABLE)

# Rebuild
re: fclean all

# Phony targets
.PHONY: all clean fclean re


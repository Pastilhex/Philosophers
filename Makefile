# Define variables
NAME = philo
GDB = -g
PT = -pthread
CC = cc
FLAGS = -Wall -Wextra -Werror #-fsanitize=thread

# List of source files
SRC = ./src/create_philos.c\
	./src/philo.c\
	./src/utils/time.c\
	./src/utils/ft_bzero.c\
	./src/utils/ft_calloc.c\
	./src/utils/ft_is_numeric.c\
	./src/utils/ft_atoi.c\
	./src/check_dead_philos.c\
	./src/input_args.c\
	./src/routine.c\
	./src/threads.c\


# Create a list of object files by replacing .c extension with .o
OBJ = $(SRC:.c=.o)

# Default target
all: $(NAME)

# Rule to build object files from source files
%.o: %.c
	$(CC) $(GDB) $(FLAGS) $(PT) -c $< -o $@

# Rule to build the executable
$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(GDB) $(FLAGS) $(PT)

# Clean rule
clean:
	rm -f $(NAME) $(OBJ)

# Rebuild rule
re: clean all

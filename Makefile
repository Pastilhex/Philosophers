# Define variables
NAME = philo
GDB = -g
PT = -pthread
SRC = $(wildcard ./src/*.c)
OBJ = $(SRC:.c=.o)
CC = gcc

# Default target
all: $(NAME)

# Rule to build the executable
$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(GDB) $(PT)

# Rule to build object files from source files
%.o: %.c
	$(CC) $(GDB) $(PT) -c $< -o $@

# Clean rule
clean:
	rm -f $(NAME) $(OBJ)

re: clean all
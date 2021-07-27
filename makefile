# Name of the project
PROJ_NAME=app

C_SOURCE=$(wildcard *.c */*.c */*/*.c */*/*/*.c)
H_SOURCE=$(wildcard *.h */*.c */*/*.h */*/*/*.h)
OBJ=$(C_SOURCE:.c=.o)
CC=gcc

# Flags for compiler
CC_FLAGS= -Wall -lm

# Compilation and linking
all: $(PROJ_NAME)

$(PROJ_NAME): $(OBJ)
	$(CC) -o $@ $^ $(CC_FLAGS)

%.o: %.c %.h
	$(CC) -o $@  $< -c $(CC_FLAGS)

main.o: main.c $(H_SOURCE)
	$(CC) -o $@ $< -c $(CC_FLAGS)

clean:
	find . -type f -name '*.o' -delete

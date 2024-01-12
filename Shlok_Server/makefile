# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -pthread -pedantic -std=c99

# Source file settings
SRC_DIR = .
SOURCES = chat_node.c client_handler.c main.c message.c misc.c properties.c
OBJECTS = $(SOURCES:.c=.o)

# Target settings
TARGET = chat_app

# Default rule
all: $(TARGET)

# Build rule
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

# Object file rule
%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f $(OBJECTS) $(TARGET)

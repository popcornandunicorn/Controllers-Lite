CC       = gcc
CFLAGS   = -Wall -Wextra -O2 -Iinclude
LDFLAGS  = -framework IOKit -framework CoreFoundation

SRC_DIR  = src
OBJ_DIR  = obj
BIN_DIR  = bin

SRCS     = $(wildcard $(SRC_DIR)/*.c)
OBJS     = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
TARGET   = $(BIN_DIR)/controllers_lite

all: $(TARGET)

$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

run: all
	./$(TARGET)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all run clean
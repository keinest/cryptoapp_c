CC = gcc

CFLAGS = -Wall -Werror -Wextra -pedantic -std=c11 -Iheaders -g

LDFLAGS = -lncurses -lssl -lcrypto -lm

SRCS = main.c Users.c helps.c decrypt.c crypto.c crypto1.c crypto2.c

OBJS = $(SRCS:.c=.o)

TARGET = CryptoApp

.PHONY: all install run clean mrproper tern

all: $(TARGET)

install: $(TARGET)

$(TARGET): $(OBJS)
	@echo "Linking $(TARGET)..."
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

-include $(OBJS:.o=.d)

run: $(TARGET)
	@echo "Running $(TARGET)..."
	./$(TARGET)

clean:
	@echo "Cleaning object files..."
	rm -f $(OBJS) $(SRCS:.c=.d)

mrproper: clean
	@echo "Cleaning executable..."
	rm -f $(TARGET)

tern:
	@echo "Clearing terminal..."
	clear 
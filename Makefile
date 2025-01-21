CC := clang
CFLAGS := -std=c23 -Wall -Wextra -pedantic -O2 -g
CFLAGS += -Wshadow -Wformat=2 -Wfloat-equal -Wconversion
CFLAGS += -Wunreachable-code -Wundef -Wcast-align -Wpointer-arith
CFLAGS += -Wwrite-strings -Wredundant-decls -Wimplicit-fallthrough
CFLAGS += -Wstrict-overflow -Wswitch-default -Wswitch-enum
CFLAGS += -Winit-self -Wmissing-include-dirs -Winline
CFLAGS += -Wstack-protector -fstack-protector-strong
CFLAGS += -fsanitize=undefined,address
LDFLAGS := -fsanitize=undefined,address

# Project settings
TARGET := bin/main
SRCS := $(wildcard src/*.c)
OBJS := $(patsubst src/%.c, bin/%.o, $(SRCS))

# Rules
.PHONY: all clean run dirs

all: dirs $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

bin/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf bin

dirs:
	mkdir -p bin

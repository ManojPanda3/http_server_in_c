CC = gcc
CFLAGS = -Werror -Iincludes -Llib
SRC_CODE = src/*
OUTPUT = builds/http

all:build run

build:
	$(CC) $(SRC_CODE) -o $(OUTPUT) $(CFLAGS)

run:
	./$(OUTPUT)

clean:
	rm -rf $(OUTPUT)


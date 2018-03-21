go: static

CC = g++
FLAGS = -std=c++11 -std=gnu++11 -c -Wall
INCLUDES = -Iincludes
LIBRARIES = -lm -lpthread
NAME = crypto
OBJS = src/utils.o src/uint256.o src/sha256.o src/rsa.o src/base64.o

prepare:
	mkdir -p include lib
	cp src/*.hpp include/

static: prepare $(OBJS)
	ar rcs lib/lib$(NAME).a $(OBJS)

%.o: %.cpp
	$(CC) $(FLAGS) $(INCLUDES) $< -o $@


install:
	mv include /usr/include/crypto
	mv lib/lib$(NAME).a /usr/lib/lib$(NAME).a

clean:
	rm -rf include lib src/*.o

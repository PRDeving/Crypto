CC = g++
FLAGS = -std=c++11 -std=gnu++11 -Wall
INCLUDES = -I../src
LIBRARIES = -lgtest -lm -lpthread
NAME = runTests

FILES = ../src/utils.cpp ../src/uint256.cpp ../src/sha256.cpp ../src/rsa.cpp ../src/base64.cpp
TESTS = sha256Test.cpp uint256Test.cpp rsaTest.cpp base64Test.cpp run.cpp

compile:
	$(CC) $(FLAGS) $(INCLUDES) $(FILES) $(TESTS) $(LIBRARIES) -o $(NAME)

lib:
	$(CC) $(FLAGS) -I../include $(TESTS) -L../lib $(LIBRARIES) -lcrypto -o $(NAME)

clean:
	rm $(NAME)


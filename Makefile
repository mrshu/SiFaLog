CC=$(CROSS_COMPILE)g++ -Wall -g
CVFLAG=`pkg-config --libs --cflags opencv`

TARGET=example

example: example.cc
	$(CC) lib/sifalog.cc example.cc -o example $(CVFLAG)

all: $(TARGET)
	@echo "Making all"

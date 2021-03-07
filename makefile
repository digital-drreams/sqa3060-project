CC = g++
CFLAGS = -Wall -c

HEADER = frontend.h
CPP = Account.cpp Database.cpp Session.cpp Main.cpp

PROGNAME = front-end

OBJ = $(CPP:.cpp=.o)

all: $(PROGNAME)

$(PROGNAME): $(OBJ)
	$(CC) -o $@ $(OBJ)

%.o : %.cpp $(HEADER)
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: clean

clean:
	rm -rf $(PROGNAME) $(OBJ)

#all : Account Session Database Main
#	cc -g -o atm Account.o Session.o Database.o Main.o
#
#clean : 
#	rm atm Account.o Session.o Database.o Main.o
#
#Account : Account.o
#	cc -g -o Account Account.o -lstdc++
#
#Session : Session.o
#	cc -g -o Session Session.o -lstdc++
#
#Database : Database.o
#	cc -g -o Database Database.o -lstdc++
#
#Main : Main.o
#	cc -g -o Main Main.o -lstdc++
	
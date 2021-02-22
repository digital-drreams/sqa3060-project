CFLAGS = -g++ -Wall

all : Account Session Database Main

Account : Account.o
	cc -o Account Account.o

Session : Session.o
	cc -o Session Session.o

Database : Database.o
	cc -o Database Database.o

Main : Main.o
	cc -o Main Main.o
	

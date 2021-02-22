CFLAGS = -g++ -Wall

all : Account Session Database Main

Account : Account.o
	cc -g -o Account Account.o -lstdc++

Session : Session.o
	cc -g -o Session Session.o -lstdc++

Database : Database.o
	cc -g -o Database Database.o -lstdc++

Main : Main.o
	cc -g -o Main Main.o -lstdc++
	

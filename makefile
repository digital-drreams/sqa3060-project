CFLAGS = -g++ -Wall

all : Account Session Database Main
	cc -g -o atm Account.o Session.o Database.o Main.o

clean : 
	rm atm Account.o Session.o Database.o Main.o

Account : Account.o
	cc -g -o Account Account.o -lstdc++

Session : Session.o
	cc -g -o Session Session.o -lstdc++

Database : Database.o
	cc -g -o Database Database.o -lstdc++

Main : Main.o
	cc -g -o Main Main.o -lstdc++
	

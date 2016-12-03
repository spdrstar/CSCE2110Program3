all: zae0008

zae0008: main.o
		g++ main.o -o zae0008
		
main.o: main.cpp main.h
		g++ -c main.cpp
clean:
		rm -rf *.o zae0008
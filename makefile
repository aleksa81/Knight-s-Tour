program: functions.o main.o
	gcc -o program functions.o main.o
functions.o: functions.c declarations.h
	gcc -o functions.o -c functions.c -I.
main.o: main.c declarations.h
	gcc -o main.o -c main.c -I.
.PHONY: clean all
clean:
	rm -f *.o
	rm -f program
	rm -f *.c~
	rm -f *.h~


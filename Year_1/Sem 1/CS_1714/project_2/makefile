Airlines.exe: main.o route-records.o
	gcc main.o route-records.o -o Airlines.exe
main.o: main.c route-records.h route-records.c
	gcc -c main.c
route-records.o: route-records.c route-records.h
	gcc -c route-records.c
clean:
	rm *.o Airlines.exe
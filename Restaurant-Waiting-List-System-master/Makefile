proj4: UI.o Action.o List.o
	gcc -o proj4 UI.o Action.o List.o

UI.o: UI.c head.h
	gcc -c UI.c

Action.o: Action.c head.h
	gcc -c Action.c

List.o: List.c head.h
	gcc -c List.c

clean:
	rm UI.o Action.o List.o proj4

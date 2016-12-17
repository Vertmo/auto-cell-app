all : auto_cell_app

app.o : app.c
	gcc -c -o app.o app.c `pkg-config --cflags gtk+-3.0`

app_callback.o : app_callback.c app_callback.h
	gcc -c -o app_callback.o app_callback.c `pkg-config --cflags gtk+-3.0`

rules.o : rules.c rules.h
	gcc -c -o rules.o rules.c

automatonIO.o : automatonIO.c automatonIO.h
	gcc -c -o automatonIO.o automatonIO.c `pkg-config --cflags gtk+-3.0`

auto_cell_app : app.o app_callback.o rules.o automatonIO.o
	gcc -o auto_cell_app app.o app_callback.o rules.o automatonIO.o `pkg-config --libs gtk+-3.0`

clean : 
	rm *.o auto_cell_app

all : auto_cell_app

app.o : app.c
	gcc -c -o app.o app.c `pkg-config --cflags gtk+-3.0`

app_callback.o : app_callback.c app_callback.h
	gcc -c -o app_callback.o app_callback.c `pkg-config --cflags gtk+-3.0`

auto_cell_app : app.o app_callback.o
	gcc -o auto_cell_app app.o app_callback.o `pkg-config --libs gtk+-3.0`

clean : 
	rm *.o auto_cell_app

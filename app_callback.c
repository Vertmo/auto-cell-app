#include <stdlib.h>
#include "app_callback.h"
#include "rules.h"

extern int delay;
extern int SIZE_X; extern int SIZE_Y;
extern int **world;
extern int **playWorld;
extern Rule *rule;

extern GtkWidget *dA;
extern guint timeoutTag;

void on_new(GtkWidget *widget, gpointer data) {
	gtk_widget_set_size_request(dA, SIZE_X*20, SIZE_Y*20);
	//g_source_remove(timeoutTag);
	int i; int j;
	if(world) {
		for(i=0;i<SIZE_Y;i++) free(world[i]);
		free(world);
	}
	world = (int **) malloc(SIZE_Y * sizeof(int *));
	for(i=0;i<SIZE_Y;i++) {
		world[i] = (int *) malloc(SIZE_X * sizeof(int));
		for(j=0;j<SIZE_X;j++) world[i][j] = 0;
	}
	gtk_widget_queue_draw(dA);
}

void on_open(GtkWidget *widget, gpointer data) {

}

void on_save(GtkWidget *widget, gpointer data) {

}

void on_conway(GtkWidget *widget, gpointer data) {
	free_rule(rule);
	rule = allocate_rule(rule, 2);
	rule->colors[0][0] = 1; rule->colors[0][1] = 1; rule->colors[0][2] = 1;
	rule->colors[1][0] = 0; rule->colors[1][1] = 0; rule->colors[1][2] = 0;
	on_new(NULL, NULL);
}

void on_help(GtkWidget *widget, gpointer data) {

}

void on_about(GtkWidget *widget, gpointer data) {

}

void on_buttonpress_da(GtkWidget *widget, GdkEventButton *event, gpointer data) {
	if(delay != -1) return;
	int nbStates = 2; //A effacer quand les regles seront programmees !
	int x = (int) event->x / 20; int y = (int) event->y / 20;
	world[y][x]++;
	if (world[y][x] >= nbStates) world[y][x] = 0;
	gtk_widget_queue_draw(dA);
}

void on_draw(GtkWidget *widget, cairo_t *cr, gpointer data) {
	int i; int j;
	cairo_set_line_width(cr, 1);
	for(i=0;i<SIZE_Y;i++) {
		for(j=0;j<SIZE_X;j++) {
			cairo_set_source_rgb(cr, rule->colors[world[i][j]][0], rule->colors[world[i][j]][1], rule->colors[world[i][j]][2]);
			cairo_rectangle(cr, j*20, i*20, 20, 20);
			cairo_fill(cr);
		}
	}
}

GSourceFunc on_timeout(GtkWidget *widget, gpointer data) {
	gtk_widget_queue_draw(dA);
	return (gpointer) TRUE;
}

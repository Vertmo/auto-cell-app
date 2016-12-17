#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>
#include "automatonIO.h"
#include "rules.h"

extern int SIZE_X; extern int SIZE_Y;
extern int **world;

extern Rule *rule;

extern GtkEntryBuffer *sizeXBuffer;
extern GtkEntryBuffer *sizeYBuffer;

void open_automaton(char *filename) {
	FILE *f = fopen(filename, "r");
	on_stop(NULL, NULL);
	free_world(world, SIZE_X, SIZE_Y);
	world = NULL;
	fscanf(f, "%d %d\n", &SIZE_X, &SIZE_Y);
	char strX[15]; char strY[15];
	sprintf(strX, "%d", SIZE_X); sprintf(strY, "%d", SIZE_Y);
	gtk_entry_buffer_set_text (sizeXBuffer, strX, -1);
	gtk_entry_buffer_set_text (sizeYBuffer, strY, -1);
	char ruleName[40];
	fscanf(f, "%s\n", ruleName);
	if(strcmp(ruleName, "conway")==0) on_conway();

	int i; int j;
	for(i=0;i<SIZE_Y;i++) {
		for(j=0;j<SIZE_X;j++) {
			int nb;
			fscanf(f, "%d", &nb);
			world[i][j] = nb;
		}
	}
	fclose(f);
}

void save_automaton(char *filename) {
	on_stop(NULL, NULL);
	FILE *f = fopen(filename, "w");
	fprintf(f, "%d %d\n", SIZE_X, SIZE_Y);
	fprintf(f, "%s\n", rule->name);
	int i; int j;
	for(i=0;i<SIZE_Y;i++) {
		for(j=0;j<SIZE_X;j++) fprintf(f, "%d ", world[i][j]);
		fprintf(f, "\n");
	}
	fclose(f);
}


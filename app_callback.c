#include <stdlib.h>
#include <string.h>
#include "app_callback.h"
#include "rules.h"

extern int delay;
extern int SIZE_X; extern int SIZE_Y;
extern int drawGrid;
extern int **world;
extern int **worldSave;

extern Rule *rule;
extern int **(*rule_function)(int **, int, int);

extern GtkWidget *dA;
extern GtkWidget *ruleLabel;
extern GtkEntryBuffer *sizeXBuffer;
extern GtkEntryBuffer *sizeYBuffer;
extern guint timeoutTag;

void on_new(GtkWidget *widget, gpointer data) {
	on_stop(NULL, NULL);
	gtk_widget_set_size_request(dA, SIZE_X*20, SIZE_Y*20);
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
	GtkWidget *dialog;
	GtkFileFilter *txt_filter;
	gint res;

	txt_filter = gtk_file_filter_new ();
	gtk_file_filter_set_name(txt_filter, "*.txt");
	gtk_file_filter_add_pattern (txt_filter, "*.txt");
	dialog = gtk_file_chooser_dialog_new ("Open Automaton (.txt)",
				      NULL,
				      GTK_FILE_CHOOSER_ACTION_OPEN,
				      ("_Cancel"), GTK_RESPONSE_CANCEL,
				      ("_Open"), GTK_RESPONSE_ACCEPT,
				      NULL);

	gtk_file_chooser_add_filter(GTK_FILE_CHOOSER (dialog), txt_filter);

	res = gtk_dialog_run (GTK_DIALOG (dialog));
	if (res == GTK_RESPONSE_ACCEPT) {
    		char *filename;
    		GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
    		filename = gtk_file_chooser_get_filename (chooser);
    		open_automaton(filename);
    		g_free (filename);
  	}

	gtk_widget_destroy (dialog);
}

void on_save(GtkWidget *widget, gpointer data) {
	GtkWidget *dialog;
	GtkFileChooser *chooser;
	gint res;

	dialog = gtk_file_chooser_dialog_new ("Save Automaton (.txt)",
				      NULL,
				      GTK_FILE_CHOOSER_ACTION_SAVE,
				      ("_Cancel"), GTK_RESPONSE_CANCEL,
				      ("_Save"), GTK_RESPONSE_ACCEPT,
				      NULL);

	chooser = GTK_FILE_CHOOSER(dialog);

	gtk_file_chooser_set_do_overwrite_confirmation (chooser, TRUE);

	/*if (user_edited_a_new_document) gtk_file_chooser_set_current_name (chooser, _("Untitled document"));
	else gtk_file_chooser_set_filename (chooser, existing_filename);*/

	gtk_file_chooser_set_current_name (chooser, "Untitled document");

	res = gtk_dialog_run (GTK_DIALOG (dialog));
	if (res == GTK_RESPONSE_ACCEPT) {
    		char *filename;
    		filename = gtk_file_chooser_get_filename(chooser);
    		save_automaton(filename);
    		g_free(filename);
	}

	gtk_widget_destroy (dialog);
}

void on_conway(GtkWidget *widget, gpointer data) {
	free_rule(rule);
	rule = allocate_rule(rule, 2);
	strcpy(rule->name, "conway");
	rule->colors[0][0] = 1; rule->colors[0][1] = 1; rule->colors[0][2] = 1;
	rule->colors[1][0] = 0; rule->colors[1][1] = 0; rule->colors[1][2] = 0;
	rule_function = &conway;
	gtk_label_set_text(GTK_LABEL(ruleLabel), "Conway's Game of Life");
	on_new(NULL, NULL);
}

void on_wireworld(GtkWidget *widget, gpointer data) {
	free_rule(rule);
	rule = allocate_rule(rule, 4);
	strcpy(rule->name, "wireworld");
	rule->colors[0][0] = 0; rule->colors[0][1] = 0; rule->colors[0][2] = 0;
	rule->colors[1][0] = 1; rule->colors[1][1] = 1; rule->colors[1][2] = 0;
	rule->colors[2][0] = 1; rule->colors[2][1] = 0; rule->colors[2][2] = 0;
	rule->colors[3][0] = 0; rule->colors[3][1] = 0; rule->colors[3][2] = 1;
	rule_function = &wireworld;
	gtk_label_set_text(GTK_LABEL(ruleLabel), "Wireworld");
	on_new(NULL, NULL);
}

void on_help(GtkWidget *widget, gpointer data) {

}

void on_about(GtkWidget *widget, gpointer data) {

}

void on_play(GtkWidget *widget, gpointer data) {
	if(worldSave) return;
	worldSave = (int **) malloc(SIZE_Y*sizeof(int *));
	int i; int j;
	for(i=0;i<SIZE_Y;i++) {
		worldSave[i] = (int *) malloc(SIZE_X*sizeof(int));
		for(j=0;j<SIZE_X;j++) worldSave[i][j] = world[i][j];
	}

	g_source_remove(timeoutTag);
	delay = 100;
	timeoutTag = g_timeout_add(delay, (GSourceFunc) on_timeout, NULL);
}

void on_stop(GtkWidget *widget, gpointer data) {
	if(worldSave == NULL) return;
	int i; int j;
	for(i=0;i<SIZE_Y;i++) {
		for(j=0;j<SIZE_X;j++) world[i][j] = worldSave[i][j];
		free(worldSave[i]);
	}
	free(worldSave); worldSave = NULL;
	
	g_source_remove(timeoutTag);
	delay = -1;
	timeoutTag = g_timeout_add(delay, (GSourceFunc) on_timeout, NULL);
	gtk_widget_queue_draw(dA);
}

void on_size_change(GtkWidget *widget, gpointer data) {
	int newSizeX = atoi(gtk_entry_buffer_get_text(sizeXBuffer));
	int newSizeY = atoi(gtk_entry_buffer_get_text(sizeYBuffer));
	if(newSizeX == 0 || newSizeY == 0 || (newSizeX == SIZE_X && newSizeY == SIZE_Y)) return;
	on_stop(NULL, NULL);
	free_world(world, SIZE_X, SIZE_Y);
	world = NULL;
	SIZE_X = newSizeX; SIZE_Y = newSizeY;
	on_new(NULL, NULL);
}

void on_buttonpress_da(GtkWidget *widget, GdkEventButton *event, gpointer data) {
	if(delay != -1) return;
	int x = (int) event->x / 20; int y = (int) event->y / 20;
	world[y][x]++;
	if (world[y][x] >= rule->nbStates) world[y][x] = 0;
	gtk_widget_queue_draw(dA);
}

void on_draw(GtkWidget *widget, cairo_t *cr, gpointer data) {
	int i; int j;
	cairo_set_line_width(cr, 0.3);

	for(i=0;i<SIZE_Y;i++) {
		for(j=0;j<SIZE_X;j++) {
			cairo_set_source_rgb(cr, rule->colors[world[i][j]][0], rule->colors[world[i][j]][1], rule->colors[world[i][j]][2]);
			cairo_rectangle(cr, j*20, i*20, 20, 20);
			cairo_fill(cr);
		}
	}

	if(drawGrid) {
		cairo_set_source_rgb(cr, 0.5, 0.5, 0.5);
		for(i=1;i<SIZE_Y;i++) {
			cairo_move_to(cr, 0, i*20);
			cairo_line_to(cr, SIZE_X*20, i*20);
		}
		for(j=1;j<SIZE_X;j++) {
			cairo_move_to(cr, j*20, 0);
			cairo_line_to(cr, j*20, SIZE_Y*20);
		}
		cairo_stroke(cr);
		cairo_move_to(cr, 0, 0);
	}
}

GSourceFunc on_timeout(GtkWidget *widget, gpointer data) {
	world = (*rule_function)(world, SIZE_X, SIZE_Y);
	gtk_widget_queue_draw(dA);
	return (gpointer) TRUE;
}

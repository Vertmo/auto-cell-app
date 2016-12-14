#ifndef _APP_CALLBACK_H_
#define _APP_CALLBACK_H_

#include <gtk/gtk.h>

void on_new(GtkWidget *widget, gpointer data);
void on_open(GtkWidget *widget, gpointer data);
void on_save(GtkWidget *widget, gpointer data);

void on_conway(GtkWidget *widget, gpointer data);

void on_help(GtkWidget *widget, gpointer data);
void on_about(GtkWidget *widget, gpointer data);

void on_play(GtkWidget *widget, gpointer data);
void on_stop(GtkWidget *widget, gpointer data);

void on_buttonpress_da(GtkWidget *widget, GdkEventButton *event, gpointer data);
void on_draw(GtkWidget *widget, cairo_t *cr, gpointer data);

GSourceFunc on_timeout(GtkWidget *widget, gpointer data);

#endif

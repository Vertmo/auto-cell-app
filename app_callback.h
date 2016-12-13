#ifndef _APP_CALLBACK_H_
#define _APP_CALLBACK_H_

#include <gtk/gtk.h>

void OnNew(GtkWidget *widget, gpointer data);
void OnOpen(GtkWidget *widget, gpointer data);
void OnSave(GtkWidget *widget, gpointer data);

void OnHelp(GtkWidget *widget, gpointer data);
void OnAbout(GtkWidget *widget, gpointer data);

#endif

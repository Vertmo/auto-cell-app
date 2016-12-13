#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>

#include "app_callback.h"
#include "rules.h"

int delay = -1;
int SIZE_X = 20; int SIZE_Y = 20;
int **world = NULL;
int **playWorld = NULL;
Rule *rule;

GtkWidget *dA;
guint timeoutTag;

int main(int argc, char *argv[]) {
	GtkWidget *window;
	GtkWidget *mainBox;
	GtkWidget *menuBar;
	GtkWidget *menu;
	GtkWidget *menuItem;
	GtkWidget *hBox;

	gtk_init(&argc, &argv);

	/* Creating Window */
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Auto-Cell");
	gtk_window_set_default_size(GTK_WINDOW(window), -1, -1);
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

	/* Creating main box (vertical) */
	mainBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add(GTK_CONTAINER(window), mainBox);

	/* Creating menu */
	menuBar = gtk_menu_bar_new(); //Main menu bar
	
	/* Automaton menu */
	menu = gtk_menu_new();

	menuItem = gtk_menu_item_new_with_mnemonic("_New");
	g_signal_connect(G_OBJECT(menuItem), "activate", G_CALLBACK(on_new), (GtkWidget*) window);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), menuItem);

	menuItem = gtk_menu_item_new_with_mnemonic("_Open");
	g_signal_connect(G_OBJECT(menuItem), "activate", G_CALLBACK(on_open), (GtkWidget*) window);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), menuItem);

	menuItem = gtk_menu_item_new_with_mnemonic("_Save");
	g_signal_connect(G_OBJECT(menuItem), "activate", G_CALLBACK(on_save), (GtkWidget*) window);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), menuItem);

	menuItem = gtk_menu_item_new_with_mnemonic("_Automaton");
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuItem), menu);
	gtk_menu_shell_append(GTK_MENU_SHELL(menuBar), menuItem);

	/* Rule menu */
	menu = gtk_menu_new();

	menuItem = gtk_menu_item_new_with_mnemonic("_Conway");
	g_signal_connect(G_OBJECT(menuItem), "activate", G_CALLBACK(on_conway), (GtkWidget*) window);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), menuItem);

	menuItem = gtk_menu_item_new_with_mnemonic("_Rule");
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuItem), menu);
	gtk_menu_shell_append(GTK_MENU_SHELL(menuBar), menuItem);

	/* Help menu */
	menu = gtk_menu_new();

	menuItem = gtk_menu_item_new_with_mnemonic("_Help");
	g_signal_connect(G_OBJECT(menuItem), "activate", G_CALLBACK(on_help), (GtkWidget*) window);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), menuItem);

	menuItem = gtk_menu_item_new_with_mnemonic("_About");
	g_signal_connect(G_OBJECT(menuItem), "activate", G_CALLBACK(on_about), (GtkWidget*) window);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), menuItem);

	menuItem = gtk_menu_item_new_with_mnemonic("?");
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuItem), menu);
	gtk_menu_shell_append(GTK_MENU_SHELL(menuBar), menuItem);

	gtk_box_pack_start(GTK_BOX(mainBox), menuBar, FALSE, FALSE, 0);

	/* Horizontal Box (containing view of world and options) */
	hBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_box_pack_start(GTK_BOX(mainBox), hBox, FALSE, FALSE, 0);

	/* Drawing Area (view of world) */
	dA = gtk_drawing_area_new ();
	g_signal_connect(dA, "button_press_event", G_CALLBACK(on_buttonpress_da), NULL);
	g_signal_connect(dA, "draw", G_CALLBACK(on_draw), NULL);
	gtk_widget_set_events(dA, GDK_BUTTON_PRESS_MASK);
	
	gtk_box_pack_start(GTK_BOX(hBox), dA, FALSE, FALSE, 0);

	gtk_widget_show_all(window);
	timeoutTag = g_timeout_add(delay, (GSourceFunc) on_timeout, NULL);

	/* Initializing rule to Conway Game of life */
	on_conway(NULL, NULL);

	gtk_main();

	return 0;
}

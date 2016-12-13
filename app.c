#include <stdlib.h>
#include <gtk/gtk.h>

#include "app_callback.h"

int main(int argc, char *argv[]) {
	GtkWidget *window;
	GtkWidget *mainBox;
	GtkWidget *menuBar;
	GtkWidget *menu;
	GtkWidget *menuItem;
	GtkWidget *hBox;
	GtkWidget *pDA;

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
	g_signal_connect(G_OBJECT(menuItem), "activate", G_CALLBACK(OnNew), (GtkWidget*) window);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), menuItem);

	menuItem = gtk_menu_item_new_with_mnemonic("_Open");
	g_signal_connect(G_OBJECT(menuItem), "activate", G_CALLBACK(OnOpen), (GtkWidget*) window);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), menuItem);

	menuItem = gtk_menu_item_new_with_mnemonic("_Save");
	g_signal_connect(G_OBJECT(menuItem), "activate", G_CALLBACK(OnSave), (GtkWidget*) window);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), menuItem);

	menuItem = gtk_menu_item_new_with_mnemonic("_Automaton");
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuItem), menu);
	gtk_menu_shell_append(GTK_MENU_SHELL(menuBar), menuItem);

	/* Rule menu */
	menu = gtk_menu_new();

	menuItem = gtk_menu_item_new_with_mnemonic("_Rule");
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuItem), menu);
	gtk_menu_shell_append(GTK_MENU_SHELL(menuBar), menuItem);

	/* Help menu */
	menu = gtk_menu_new();

	menuItem = gtk_menu_item_new_with_mnemonic("_Help");
	g_signal_connect(G_OBJECT(menuItem), "activate", G_CALLBACK(OnHelp), (GtkWidget*) window);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), menuItem);

	menuItem = gtk_menu_item_new_with_mnemonic("_About");
	g_signal_connect(G_OBJECT(menuItem), "activate", G_CALLBACK(OnAbout), (GtkWidget*) window);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), menuItem);

	menuItem = gtk_menu_item_new_with_mnemonic("?");
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuItem), menu);
	gtk_menu_shell_append(GTK_MENU_SHELL(menuBar), menuItem);

	gtk_box_pack_start(GTK_BOX(mainBox), menuBar, FALSE, FALSE, 0);

	/* Horizontal Box (containing view of world and options) */
	hBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_box_pack_start(GTK_BOX(mainBox), hBox, FALSE, FALSE, 0);

	/* Drawing Area (view of world) */
	pDA = gtk_drawing_area_new ();
	//gtk_widget_set_size_request (pDA, 100, 100);
	gtk_box_pack_start(GTK_BOX(hBox), pDA, FALSE, FALSE, 0);

	gtk_widget_show_all(window);
	gtk_main();

	return 0;
}

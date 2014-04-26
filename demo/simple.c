/*
 * simple.c
 * 
 * Copyright 2014 Ikey Doherty <ikey.doherty@gmail.com>
 * 
 * gnome-app-templates is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2.1
 * of the License, or (at your option) any later version.
 */

#include <stdlib.h>

#include <gat-gnome-app-window.h>

int main(int argc, char **argv)
{
        GtkWidget *app_win = NULL;

        gtk_init(&argc, &argv);

        app_win = gat_gnome_app_window_new();
        g_signal_connect(app_win, "delete-event", gtk_main_quit, NULL);
        gtk_window_set_default_size(GTK_WINDOW(app_win), 500, 500);
        gtk_window_set_title(GTK_WINDOW(app_win), "GatGnomeAppWindow demonstration");

        /* And show */
        gtk_widget_show_all(app_win);

        gtk_main();

        return EXIT_SUCCESS;
}

/*
 * sidebar.c
 * 
 * Copyright 2014 Ikey Doherty <ikey.doherty@gmail.com>
 * 
 * gnome-app-templates is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2.1
 * of the License, or (at your option) any later version.
 */

#include <stdlib.h>

#include <gat-sidebar-window.h>

int main(int argc, char **argv)
{
        GtkWidget *app_win = NULL;
        GtkWidget *sidebar = NULL;
        GtkWidget *list = NULL;
        GtkWidget *item = NULL;
        GtkWidget *content = NULL;
        GtkWidget *main_disp = NULL;
        GtkWidget *scroller = NULL;
        gchar *label = NULL;

        gtk_init(&argc, &argv);

        app_win = gat_sidebar_window_new();
        g_signal_connect(app_win, "delete-event", gtk_main_quit, NULL);
        gtk_window_set_default_size(GTK_WINDOW(app_win), 500, 500);
        gtk_window_set_title(GTK_WINDOW(app_win), "GatSidebarWindow demonstration");

        /* Set up our sidebar*/
        sidebar = gat_sidebar_window_get_sidebar(GAT_SIDEBAR_WINDOW(app_win));
        list = gtk_list_box_new();

        /* Stick the list in a scrolled window */
        scroller = gtk_scrolled_window_new(NULL, NULL);
        /* With modern themes like Adwaita, there's only really one shadow type
         * and it looks kinda fugly in headerbar'd apps */
        gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(scroller),
                GTK_SHADOW_NONE);

        gtk_container_add(GTK_CONTAINER(scroller), list);
        gtk_container_add(GTK_CONTAINER(sidebar), scroller);
        gtk_revealer_set_reveal_child(GTK_REVEALER(sidebar), TRUE);

        /* Add some items to the sidebar */
        for (int i = 0; i < 10; i++) {
                label = g_strdup_printf("<big>Item #%d</big>", i);
                item = gtk_label_new(label);
                gtk_label_set_use_markup(GTK_LABEL(item), TRUE);
                g_free(label);
                gtk_container_add(GTK_CONTAINER(list), item);
        }

        /* Set sidebar title */
        gat_sidebar_window_set_sidebar_title(GAT_SIDEBAR_WINDOW(app_win), "Sidebar thing");

        /* And make use of the main content area */
        content = gat_sidebar_window_get_content_area(GAT_SIDEBAR_WINDOW(app_win));
        main_disp = gtk_image_new_from_icon_name("start-here-symbolic", GTK_ICON_SIZE_INVALID);
        gtk_image_set_pixel_size(GTK_IMAGE(main_disp), 256);
        gtk_box_pack_start(GTK_BOX(content), main_disp, TRUE, TRUE, 0);

        /* And show */
        gtk_widget_show_all(app_win);

        gtk_main();

        return EXIT_SUCCESS;
}

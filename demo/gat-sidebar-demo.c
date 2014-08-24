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
#include <gat-sidebar.h>

int main(int argc, char **argv)
{
        GtkWidget *app_win = NULL;
        GtkWidget *sidebar = NULL;
        GtkWidget *content = NULL;
        GtkWidget *sidebar_widg = NULL;
        GtkWidget *stack = NULL;
        GtkWidget *child = NULL;
        gchar *child_txt, *child_title;

        gtk_init(&argc, &argv);

        app_win = gat_sidebar_window_new();
        g_signal_connect(app_win, "delete-event", gtk_main_quit, NULL);
        gtk_window_set_default_size(GTK_WINDOW(app_win), 700, 500);
        gtk_window_set_title(GTK_WINDOW(app_win), "GatSidebar demonstration");

        /* Set up our sidebar*/
        sidebar = gat_sidebar_window_get_sidebar(GAT_SIDEBAR_WINDOW(app_win));
        sidebar_widg = gat_sidebar_new();
        gtk_container_add(GTK_CONTAINER(sidebar), sidebar_widg);
        gtk_revealer_set_reveal_child(GTK_REVEALER(sidebar), TRUE);

        /* Set sidebar title */
        gat_sidebar_window_set_sidebar_title(GAT_SIDEBAR_WINDOW(app_win), "Sidebar");

        /* And make use of the main content area */
        content = gat_sidebar_window_get_content_area(GAT_SIDEBAR_WINDOW(app_win));
        stack = gtk_stack_new();
        gtk_stack_set_transition_type(GTK_STACK(stack),
                GTK_STACK_TRANSITION_TYPE_SLIDE_UP_DOWN);
        gat_sidebar_set_stack(GAT_SIDEBAR(sidebar_widg), GTK_STACK(stack));
        gtk_box_pack_start(GTK_BOX(content), stack, TRUE, TRUE, 0);

        for (int i = 1; i < 8; i++) {
                child_txt = g_strdup_printf("<big>Page %d</big>", i);
                child_title = g_strdup_printf("Item %d", i);
                child = gtk_label_new(child_txt);
                gtk_label_set_use_markup(GTK_LABEL(child), TRUE);
                gtk_stack_add_titled(GTK_STACK(stack), child,
                        child_title, child_title);
                g_free(child_txt);
                g_free(child_title);
        }

        /* And show */
        gtk_widget_show_all(app_win);

        /* Remember you've performed show, so the first item in the stack
         * would be exposed. i.e. do this after "show" on GtkStack */
        gtk_stack_set_visible_child_name(GTK_STACK(stack), "Item 5");

        gtk_main();

        return EXIT_SUCCESS;
}

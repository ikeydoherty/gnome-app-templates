/*
 * gnome-app-window.c
 * 
 * Copyright 2014 Ikey Doherty <ikey.doherty@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#include "sidebar-window.h"

struct _SidebarWindowPriv {
        GtkWidget *left_header;
        GtkWidget *right_header;
};

G_DEFINE_TYPE_WITH_CODE(SidebarWindow, sidebar_window, GNOME_APP_WINDOW_TYPE, G_ADD_PRIVATE(SidebarWindow))

/* Boilerplate GObject code */
static void sidebar_window_class_init(SidebarWindowClass *klass);
static void sidebar_window_init(SidebarWindow *self);
static void sidebar_window_dispose(GObject *object);

/* Initialisation */
static void sidebar_window_class_init(SidebarWindowClass *klass)
{
        GObjectClass *g_object_class;

        g_object_class = G_OBJECT_CLASS(klass);
        g_object_class->dispose = &sidebar_window_dispose;
}

static void sidebar_window_init(SidebarWindow *self)
{
        GtkWidget *left_header, *right_header;
        GtkWidget *header;
        GtkStyleContext *style;

        self->priv = sidebar_window_get_instance_private(self);

        /* Left hand side */
        left_header = gtk_header_bar_new();
        gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(left_header), FALSE);
        style = gtk_widget_get_style_context(left_header);
        gtk_style_context_add_class(style, "titlebar");
        self->priv->left_header = left_header;

        /* Set up headerbar */
        right_header = gtk_header_bar_new();
        gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(right_header), TRUE);
        style = gtk_widget_get_style_context(right_header);
        gtk_style_context_add_class(style, "titlebar");
        self->priv->right_header = right_header;

        /* Set top header */
        header = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
        gtk_box_pack_start(GTK_BOX(header), left_header, FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX(header), right_header, TRUE, TRUE, 0);
        gtk_window_set_titlebar(GTK_WINDOW(self), header);
}

static void sidebar_window_dispose(GObject *object)
{
        /* Destruct */
        G_OBJECT_CLASS (sidebar_window_parent_class)->dispose (object);
}

/* Utility; return a new SidebarWindow */
GtkWidget *sidebar_window_new(void)
{
        SidebarWindow *self;

        self = g_object_new(SIDEBAR_WINDOW_TYPE, NULL);
        return GTK_WIDGET(self);
}

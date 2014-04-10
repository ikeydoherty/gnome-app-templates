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

#include "gnome-app-window.h"

struct _GatGnomeAppWindowPriv {
        GtkWidget *header;
};

G_DEFINE_TYPE_WITH_CODE(GatGnomeAppWindow, gat_gnome_app_window, GTK_TYPE_WINDOW, G_ADD_PRIVATE(GatGnomeAppWindow))

/* Boilerplate GObject code */
static void gat_gnome_app_window_class_init(GatGnomeAppWindowClass *klass);
static void gat_gnome_app_window_init(GatGnomeAppWindow *self);
static void gat_gnome_app_window_dispose(GObject *object);

static void init_styles(void);

/* Initialisation */
static void gat_gnome_app_window_class_init(GatGnomeAppWindowClass *klass)
{
        GObjectClass *g_object_class;

        g_object_class = G_OBJECT_CLASS(klass);
        g_object_class->dispose = &gat_gnome_app_window_dispose;
}

static void gat_gnome_app_window_init(GatGnomeAppWindow *self)
{
        GtkWidget *header;

        self->priv = gat_gnome_app_window_get_instance_private(self);

        /* Set up headerbar */
        header = gtk_header_bar_new();
        gtk_window_set_titlebar(GTK_WINDOW(self), header);
        gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(header), TRUE);

        self->priv->header = header;

        /* Initialise styles */
        init_styles();
}

static void gat_gnome_app_window_dispose(GObject *object)
{
        /* Destruct */
        G_OBJECT_CLASS (gat_gnome_app_window_parent_class)->dispose (object);
}

/* Utility; return a new GatGnomeAppWindow */
GtkWidget *gat_gnome_app_window_new(void)
{
        GatGnomeAppWindow *self;

        self = g_object_new(GAT_GNOME_APP_WINDOW_TYPE, NULL);
        return GTK_WIDGET(self);
}

static void init_styles()
{
        GtkCssProvider *css_provider;
        GFile *file = NULL;
        GdkScreen *screen;

        screen = gdk_screen_get_default();

        css_provider = gtk_css_provider_new();
        file = g_file_new_for_uri("resource://com/gmail/ikeydoherty/gat/style.css");
        if (gtk_css_provider_load_from_file(css_provider, file, NULL)) {
                gtk_style_context_add_provider_for_screen(screen,
                        GTK_STYLE_PROVIDER(css_provider),
                        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
        }
        g_object_unref(css_provider);
        g_object_unref(file);
}

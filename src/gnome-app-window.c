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

struct _GnomeAppWindowPriv {
        GtkWidget *header;
};

G_DEFINE_TYPE_WITH_CODE(GnomeAppWindow, gnome_app_window, GTK_TYPE_WINDOW, G_ADD_PRIVATE(GnomeAppWindow))

/* Boilerplate GObject code */
static void gnome_app_window_class_init(GnomeAppWindowClass *klass);
static void gnome_app_window_init(GnomeAppWindow *self);
static void gnome_app_window_dispose(GObject *object);

/* Initialisation */
static void gnome_app_window_class_init(GnomeAppWindowClass *klass)
{
        GObjectClass *g_object_class;

        g_object_class = G_OBJECT_CLASS(klass);
        g_object_class->dispose = &gnome_app_window_dispose;
}

static void gnome_app_window_init(GnomeAppWindow *self)
{
        GtkWidget *header;

        self->priv = gnome_app_window_get_instance_private(self);

        /* Set up headerbar */
        header = gtk_header_bar_new();
        gtk_window_set_titlebar(GTK_WINDOW(self), header);

        self->priv->header = header;
}

static void gnome_app_window_dispose(GObject *object)
{
        /* Destruct */
        G_OBJECT_CLASS (gnome_app_window_parent_class)->dispose (object);
}

/* Utility; return a new GnomeAppWindow */
GnomeAppWindow *gnome_app_window_new(void)
{
        GnomeAppWindow *self;

        self = g_object_new(GNOME_APP_WINDOW_TYPE, NULL);
        return self;
}

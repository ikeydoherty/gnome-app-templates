/*
 * gnome-app-window.h
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
#ifndef gat_gnome_app_window_h
#define gat_gnome_app_window_h

#include <glib-object.h>
#include <gtk/gtk.h>

typedef struct _GatGnomeAppWindow GatGnomeAppWindow;
typedef struct _GatGnomeAppWindowClass   GatGnomeAppWindowClass;
typedef struct _GatGnomeAppWindowPriv GatGnomeAppWindowPrivate;

#define GAT_GNOME_APP_WINDOW_TYPE (gat_gnome_app_window_get_type())
#define GAT_GNOME_APP_WINDOW(obj)                  (G_TYPE_CHECK_INSTANCE_CAST ((obj), GAT_GNOME_APP_WINDOW_TYPE, GatGnomeAppWindow))
#define GAT_IS_GNOME_APP_WINDOW(obj)               (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GAT_GNOME_APP_WINDOW_TYPE))
#define GAT_GNOME_APP_WINDOW_CLASS(klass)          (G_TYPE_CHECK_CLASS_CAST ((klass), GAT_GNOME_APP_WINDOW_TYPE, GatGnomeAppWindowClass))
#define GAT_IS_GNOME_APP_WINDOW_CLASS(klass)       (G_TYPE_CHECK_CLASS_TYPE ((klass), GAT_GNOME_APP_WINDOW_TYPE))
#define GAT_GNOME_APP_WINDOW_GET_CLASS(obj)        (G_TYPE_INSTANCE_GET_CLASS ((obj), GAT_GNOME_APP_WINDOW_TYPE, GatGnomeAppWindowClass))

/* GatGnomeAppWindow object */
struct _GatGnomeAppWindow {
        GtkWindow parent;
        GatGnomeAppWindowPrivate *priv;
};

/* GatGnomeAppWindow class definition */
struct _GatGnomeAppWindowClass {
        GtkWindowClass parent_class;
};

GType gat_gnome_app_window_get_type(void);

/* GatGnomeAppWindow methods */

/**
 * Construct a new GatGnomeAppWindow
 * @return A new GatGnomeAppWindow
 */
GtkWidget *gat_gnome_app_window_new(void);

#endif /* gat_gnome_app_window_h */

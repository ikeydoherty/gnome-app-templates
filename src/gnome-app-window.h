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
#ifndef gnome_app_window_h
#define gnome_app_window_h

#include <glib-object.h>
#include <gtk/gtk.h>

typedef struct _GnomeAppWindow GnomeAppWindow;
typedef struct _GnomeAppWindowClass   GnomeAppWindowClass;
typedef struct _GnomeAppWindowPriv GnomeAppWindowPrivate;

#define GNOME_APP_WINDOW_TYPE (gnome_app_window_get_type())
#define GNOME_APP_WINDOW(obj)                  (G_TYPE_CHECK_INSTANCE_CAST ((obj), GNOME_APP_WINDOW_TYPE, GnomeAppWindow))
#define IS_GNOME_APP_WINDOW(obj)               (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GNOME_APP_WINDOW_TYPE))
#define GNOME_APP_WINDOW_CLASS(klass)          (G_TYPE_CHECK_CLASS_CAST ((klass), GNOME_APP_WINDOW_TYPE, GnomeAppWindowClass))
#define IS_GNOME_APP_WINDOW_CLASS(klass)       (G_TYPE_CHECK_CLASS_TYPE ((klass), GNOME_APP_WINDOW_TYPE))
#define GNOME_APP_WINDOW_GET_CLASS(obj)        (G_TYPE_INSTANCE_GET_CLASS ((obj), GNOME_APP_WINDOW_TYPE, GnomeAppWindowClass))

/* GnomeAppWindow object */
struct _GnomeAppWindow {
        GtkWindow parent;
        GnomeAppWindowPrivate *priv;
};

/* GnomeAppWindow class definition */
struct _GnomeAppWindowClass {
        GtkWindowClass parent_class;
};

GType gnome_app_window_get_type(void);

/* GnomeAppWindow methods */

/**
 * Construct a new GnomeAppWindow
 * @return A new GnomeAppWindow
 */
GnomeAppWindow *gnome_app_window_new(void);

#endif /* gnome_app_window_h */

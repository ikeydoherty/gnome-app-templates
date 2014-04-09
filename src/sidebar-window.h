/*
 * sidebar-window.h
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
#ifndef sidebar_window_h
#define sidebar_window_h

#include <glib-object.h>
#include <gtk/gtk.h>

#include "gnome-app-window.h"

typedef struct _SidebarWindow SidebarWindow;
typedef struct _SidebarWindowClass   SidebarWindowClass;
typedef struct _SidebarWindowPriv SidebarWindowPrivate;

#define SIDEBAR_WINDOW_TYPE (sidebar_window_get_type())
#define SIDEBAR_WINDOW(obj)                  (G_TYPE_CHECK_INSTANCE_CAST ((obj), SIDEBAR_WINDOW_TYPE, SidebarWindow))
#define IS_SIDEBAR_WINDOW(obj)               (G_TYPE_CHECK_INSTANCE_TYPE ((obj), SIDEBAR_WINDOW_TYPE))
#define SIDEBAR_WINDOW_CLASS(klass)          (G_TYPE_CHECK_CLASS_CAST ((klass), SIDEBAR_WINDOW_TYPE, SidebarWindowClass))
#define IS_SIDEBAR_WINDOW_CLASS(klass)       (G_TYPE_CHECK_CLASS_TYPE ((klass), SIDEBAR_WINDOW_TYPE))
#define SIDEBAR_WINDOW_GET_CLASS(obj)        (G_TYPE_INSTANCE_GET_CLASS ((obj), SIDEBAR_WINDOW_TYPE, SidebarWindowClass))

/* SidebarWindow object */
struct _SidebarWindow {
        GnomeAppWindow parent;
        SidebarWindowPrivate *priv;
};

/* SidebarWindow class definition */
struct _SidebarWindowClass {
        GnomeAppWindowClass parent_class;
};

GType sidebar_window_get_type(void);

/* SidebarWindow methods */

/**
 * Construct a new SidebarWindow
 * @return A new SidebarWindow
 */
GtkWidget *sidebar_window_new(void);

#endif /* sidebar_window_h */

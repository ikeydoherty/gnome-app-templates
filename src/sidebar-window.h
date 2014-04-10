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
#ifndef gat_sidebar_window_h
#define gat_sidebar_window_h

#include <glib-object.h>
#include <gtk/gtk.h>

#include "gnome-app-window.h"

typedef struct _GatSidebarWindow GatSidebarWindow;
typedef struct _GatSidebarWindowClass   GatSidebarWindowClass;
typedef struct _GatSidebarWindowPriv GatSidebarWindowPrivate;

#define GAT_SIDEBAR_WINDOW_TYPE (gat_sidebar_window_get_type())
#define GAT_SIDEBAR_WINDOW(obj)                  (G_TYPE_CHECK_INSTANCE_CAST ((obj), GAT_SIDEBAR_WINDOW_TYPE, GatSidebarWindow))
#define GAT_IS_SIDEBAR_WINDOW(obj)               (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GAT_SIDEBAR_WINDOW_TYPE))
#define GAT_SIDEBAR_WINDOW_CLASS(klass)          (G_TYPE_CHECK_CLASS_CAST ((klass), GAT_SIDEBAR_WINDOW_TYPE, GatSidebarWindowClass))
#define GAT_IS_SIDEBAR_WINDOW_CLASS(klass)       (G_TYPE_CHECK_CLASS_TYPE ((klass), GAT_SIDEBAR_WINDOW_TYPE))
#define GAT_SIDEBAR_WINDOW_GET_CLASS(obj)        (G_TYPE_INSTANCE_GET_CLASS ((obj), GAT_SIDEBAR_WINDOW_TYPE, GatSidebarWindowClass))

/* GatSidebarWindow object */
struct _GatSidebarWindow {
        GatGnomeAppWindow parent;
        GatSidebarWindowPrivate *priv;
};

/* GatSidebarWindow class definition */
struct _GatSidebarWindowClass {
        GatGnomeAppWindowClass parent_class;
};

GType gat_sidebar_window_get_type(void);

/* GatSidebarWindow methods */

/**
 * Construct a new GatSidebarWindow
 * @return A new GatSidebarWindow
 */
GtkWidget *gat_sidebar_window_new(void);

/**
 * Get the sidebar widget
 * @return the sidebar
 */
GtkWidget *gat_sidebar_window_get_sidebar(GatSidebarWindow *self);

/**
 * Return the content area
 * @return the content area
 */
GtkWidget *gat_sidebar_window_get_content_area(GatSidebarWindow *self);

/**
 * Update the sidebar title
 * @param title The new sidebar title
 */
void gat_sidebar_window_set_title(GatSidebarWindow *self, const gchar *title);

/**
 * Get the current sidebar title
 * @return Current sidebar title
 */
const gchar *gat_sidebar_window_get_title(GatSidebarWindow *self);

#endif /* gat_sidebar_window_h */

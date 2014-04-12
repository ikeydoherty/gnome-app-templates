/*
 * gat-sidebar.h
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
#ifndef gat_sidebar_h
#define gat_sidebar_h

#include <glib-object.h>
#include <gtk/gtk.h>

typedef struct _GatSidebar GatSidebar;
typedef struct _GatSidebarClass   GatSidebarClass;
typedef struct _GatSidebarPriv GatSidebarPrivate;

#define GAT_SIDEBAR_TYPE (gat_sidebar_get_type())
#define GAT_SIDEBAR(obj)                  (G_TYPE_CHECK_INSTANCE_CAST ((obj), GAT_SIDEBAR_TYPE, GatSidebar))
#define GAT_IS_SIDEBAR(obj)               (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GAT_SIDEBAR_TYPE))
#define GAT_SIDEBAR_CLASS(klass)          (G_TYPE_CHECK_CLASS_CAST ((klass), GAT_SIDEBAR_TYPE, GatSidebarClass))
#define GAT_IS_SIDEBAR_CLASS(klass)       (G_TYPE_CHECK_CLASS_TYPE ((klass), GAT_SIDEBAR_TYPE))
#define GAT_SIDEBAR_GET_CLASS(obj)        (G_TYPE_INSTANCE_GET_CLASS ((obj), GAT_SIDEBAR_TYPE, GatSidebarClass))

/* GatSidebar object */
struct _GatSidebar {
        GtkScrolledWindow parent;
        GatSidebarPrivate *priv;
};

/* GatSidebar class definition */
struct _GatSidebarClass {
        GtkScrolledWindowClass parent_class;
};

GType gat_sidebar_get_type(void);

/* GatSidebar methods */

/**
 * gat_sidebar_new:
 * Construct a new GatSidebar
 * 
 * Returns: (transfer full): a new GatSidebar
 */
GtkWidget *gat_sidebar_new(void);

/**
 * gat_sidebar_set_stack:
 * @sidebar A GatSidebar
 * @stack a GtkStack
 *
 * Set the stack associated with this GatSidebar
 */
void gat_sidebar_set_stack(GatSidebar *sidebar, GtkStack *stack);

/**
 * gat_sidebar_get_stack:
 * @sidebar A GatSidebar
 *
 * Returns: (transfer full): the associated GtkStack
 */
GtkStack *gat_sidebar_get_stack(GatSidebar *sidebar);

#endif /* gat_sidebar_h */

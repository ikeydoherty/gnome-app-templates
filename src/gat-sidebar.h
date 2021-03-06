/*
 * gat-sidebar.h
 * 
 * Copyright 2014 Ikey Doherty <ikey.doherty@gmail.com>
 * 
 * gnome-app-templates is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2.1
 * of the License, or (at your option) any later version.
 */

#ifndef gat_sidebar_h
#define gat_sidebar_h

#include <glib-object.h>
#include <gtk/gtk.h>

typedef struct _GatSidebar GatSidebar;
typedef struct _GatSidebarClass   GatSidebarClass;
typedef struct _GatSidebarPriv GatSidebarPrivate;

#ifndef __GTK_DOC_IGNORE__
#define GAT_SIDEBAR_TYPE (gat_sidebar_get_type())
#endif
#define GAT_SIDEBAR(obj)                  (G_TYPE_CHECK_INSTANCE_CAST ((obj), GAT_SIDEBAR_TYPE, GatSidebar))
#define GAT_IS_SIDEBAR(obj)               (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GAT_SIDEBAR_TYPE))
#define GAT_SIDEBAR_CLASS(klass)          (G_TYPE_CHECK_CLASS_CAST ((klass), GAT_SIDEBAR_TYPE, GatSidebarClass))
#define GAT_IS_SIDEBAR_CLASS(klass)       (G_TYPE_CHECK_CLASS_TYPE ((klass), GAT_SIDEBAR_TYPE))
#define GAT_SIDEBAR_GET_CLASS(obj)        (G_TYPE_INSTANCE_GET_CLASS ((obj), GAT_SIDEBAR_TYPE, GatSidebarClass))

/**
 * SECTION:gat-sidebar
 * @short_description: An automatic sidebar widget
 * @title: GatSidebar
 *
 * A GatSidebarWindow enables you to quickly and easily provide a consistent
 * "sidebar" object for your user interface.
 *
 * In order to use a GatSidebar, you simply use a GtkStack to organise
 * your UI flow, and add the sidebar to your sidebar area. You can use
 * #gat_sidebar_set_stack to connect the #GatSidebar to the #GtkStack
 *
 * The GatSidebar will obtain the titles from the "title" child-property
 * of the item within the GtkStack. Theming is automatically handled within
 * the library to ensure a consistent look across applications. Note that
 * users may use the touch, key or mouse events to interact with this
 * widget and select an item within your #GtkStack instance.
 *
 */

/* GatSidebar object */
struct _GatSidebar {
        GtkListBox parent;
        GatSidebarPrivate *priv;
};

/* GatSidebar class definition */
struct _GatSidebarClass {
        GtkListBoxClass parent_class;
};

GType gat_sidebar_get_type(void);

/* GatSidebar methods */

/**
 * gat_sidebar_new:
 *
 * Construct a new GatSidebar
 * 
 * Returns: (transfer full): a new GatSidebar
 */
GtkWidget *gat_sidebar_new(void);

/**
 * gat_sidebar_set_stack:
 * @sidebar: A GatSidebar
 * @stack: a GtkStack
 *
 * Set the #GtkStack associated with this #GatSidebar. This sidebar widget
 * will automatically update according to the order (packing) and items
 * within the given #GtkStack.
 */
void gat_sidebar_set_stack(GatSidebar *sidebar, GtkStack *stack);

/**
 * gat_sidebar_get_stack:
 * @sidebar: A GatSidebar
 *
 * Returns: (transfer full): the associated GtkStack
 */
GtkStack *gat_sidebar_get_stack(GatSidebar *sidebar);

#endif /* gat_sidebar_h */

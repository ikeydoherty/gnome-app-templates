/*
 * gnome-app-window.h
 * 
 * Copyright 2014 Ikey Doherty <ikey.doherty@gmail.com>
 * 
 * gnome-app-templates is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2.1
 * of the License, or (at your option) any later version.
 */

#ifndef gat_gnome_app_window_h
#define gat_gnome_app_window_h

#include <glib-object.h>
#include <gtk/gtk.h>

typedef struct _GatGnomeAppWindow GatGnomeAppWindow;
typedef struct _GatGnomeAppWindowClass   GatGnomeAppWindowClass;
typedef struct _GatGnomeAppWindowPriv GatGnomeAppWindowPrivate;

#ifndef __GTK_DOC_IGNORE__
#define GAT_GNOME_APP_WINDOW_TYPE (gat_gnome_app_window_get_type())
#endif
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
 * gat_gnome_app_window_new:
 *
 * Construct a new GatGnomeAppWindow
 *
 * Returns: (transfer full): a new GatGnomeAppWindow
 */
GtkWidget *gat_gnome_app_window_new(void);

#endif /* gat_gnome_app_window_h */

/*
 * sidebar-window.h
 * 
 * Copyright 2014 Ikey Doherty <ikey.doherty@gmail.com>
 * 
 * gnome-app-templates is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2.1
 * of the License, or (at your option) any later version.
 */

#ifndef gat_sidebar_window_h
#define gat_sidebar_window_h

#include <glib-object.h>
#include <gtk/gtk.h>

#include <gat-gnome-app-window.h>

typedef struct _GatSidebarWindow GatSidebarWindow;
typedef struct _GatSidebarWindowClass   GatSidebarWindowClass;
typedef struct _GatSidebarWindowPriv GatSidebarWindowPrivate;

#ifndef __GTK_DOC_IGNORE__
#define GAT_SIDEBAR_WINDOW_TYPE (gat_sidebar_window_get_type())
#endif
#define GAT_SIDEBAR_WINDOW(obj)                  (G_TYPE_CHECK_INSTANCE_CAST ((obj), GAT_SIDEBAR_WINDOW_TYPE, GatSidebarWindow))
#define GAT_IS_SIDEBAR_WINDOW(obj)               (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GAT_SIDEBAR_WINDOW_TYPE))
#define GAT_SIDEBAR_WINDOW_CLASS(klass)          (G_TYPE_CHECK_CLASS_CAST ((klass), GAT_SIDEBAR_WINDOW_TYPE, GatSidebarWindowClass))
#define GAT_IS_SIDEBAR_WINDOW_CLASS(klass)       (G_TYPE_CHECK_CLASS_TYPE ((klass), GAT_SIDEBAR_WINDOW_TYPE))
#define GAT_SIDEBAR_WINDOW_GET_CLASS(obj)        (G_TYPE_INSTANCE_GET_CLASS ((obj), GAT_SIDEBAR_WINDOW_TYPE, GatSidebarWindowClass))

/**
 * SECTION:gat-sidebar-window
 * @short_description: A window with an automatic sidebar
 * @title: GatSidebarWindow
 *
 * A GatSidebarWindow enables you to quickly build an application UI
 * that contains a content area, and a sidebar area.
 *
 * The application window is automatically split into two major parts,
 * and enables separate "headers" (titles) for the sidebar area, and
 * the main content area.
 *
 * When adding content to the window, you should use #gat_sidebar_window_get_content_area
 * This returns a #GtkBox in a vertical orientation, enabling you to add
 * anything you wish.
 *
 * When manipulating the sidebar area, you should use #gat_sidebar_window_get_sidebar
 * This returns a #GtkRevealer which has its content hidden by default.
 * This enables derived UIs to hide the sidebar when it is not required.
 * Note no transition is enabled by default, this is left to the application
 * developer to implement.
 */

/* GatSidebarWindow object */
struct _GatSidebarWindow {
        GatGnomeAppWindow parent;
        GatSidebarWindowPrivate *priv;
};

/* GatSidebarWindow class definition */
struct _GatSidebarWindowClass {
        GatGnomeAppWindowClass parent_class;
};

/**
 * GatHeaderbarPosition:
 * @GAT_HEADERBAR_POSITION_SIDEBAR: Left (sidebar) header widget
 * @GAT_HEADERBAR_POSITION_MAIN: Center (main) header widget
 *
 * Used to specify the positon of the headerbar widget being retrieved
 * via #gat_sidebar_window_get_headerbar
 */
typedef enum {
        GAT_HEADERBAR_POSITION_MIN = 0,
        GAT_HEADERBAR_POSITION_SIDEBAR,
        GAT_HEADERBAR_POSITION_MAIN,
        GAT_HEADERBAR_POSITION_MAX
} GatHeaderbarPosition;

GType gat_sidebar_window_get_type(void);

/**
 * gat_sidebar_window_new:
 * 
 * Construct a new GatSidebarWindow
 *
 * Returns: (transfer full): a new GatSidebarWindow
 */
GtkWidget *gat_sidebar_window_new(void);

/**
 * gat_sidebar_window_get_sidebar:
 * @window: A GatSidebarWindow
 *
 * This method returns the sidebar area of the #GatSidebarWindow. By
 * default this is a #GtkRevealer, which is hidden. When adding to
 * the sidebar area, do so as with any normal #GtkContainer.
 *
 * This uses the left-hand side of the UI, and will only use as much
 * space as required by the widget. Notice that the sidebar header
 * will match the size of the sidebar itself.
 *
 * Returns: (transfer none): the sidebar
 */
GtkWidget *gat_sidebar_window_get_sidebar(GatSidebarWindow *window);

/**
 * gat_sidebar_window_get_content_area:
 * @window: A GatSidebarWindow
 *
 * This method returns the main content area of the #GatSidebarWindow
 * This is by default a vertical #GtkBox, which is configured to use
 * as much space as possible within the UI.
 * 
 * Returns: (transfer none): content area
 */
GtkWidget *gat_sidebar_window_get_content_area(GatSidebarWindow *window);

/**
 * gat_sidebar_window_set_sidebar_title:
 * @window: A GatSidebarWindow
 * @title: The new sidebar title
 *
 * Update the sidebar title of the #GatSidebarWindow. This will be displayed
 * in the header area above the sidebar itself. The UI will automatically
 * adjust the allocation using a #GtkSizeGroup
 */
void gat_sidebar_window_set_sidebar_title(GatSidebarWindow *window, const gchar *title);

/**
 * gat_sidebar_window_get_sidebar_title:
 * @window: A GatSidebarWindow
 * 
 * Get the currently set sidebar title. Do not free this string, as
 * #GatSidebarWindow owns this reference.
 *
 * Returns: (transfer none): Current sidebar title
 */
const gchar *gat_sidebar_window_get_sidebar_title(GatSidebarWindow *window);

/**
 * gat_sidebar_window_get_headerbar:
 * @window: A GatSidebarWindow
 * @position: Which header to return
 *
 * Get a specific #GtkHeaderBar widget for this #GatSidebarWindow. This
 * enables developers to add custom widgets to the headers to add their
 * own forms of interaction.
 *
 * Returns: (transfer none): Underlying #GtkHeaderBar
 */
GtkWidget *gat_sidebar_window_get_headerbar(GatSidebarWindow *window,
                                            GatHeaderbarPosition position);
#endif /* gat_sidebar_window_h */

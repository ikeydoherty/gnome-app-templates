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

#include "sidebar-window.h"

struct _GatSidebarWindowPriv {
        GtkWidget *left_header;
        GtkWidget *right_header;
        GtkWidget *sidebar;
        GtkWidget *content;
        GtkSizeGroup *size_group;
        gchar *side_title;
};

G_DEFINE_TYPE_WITH_CODE(GatSidebarWindow, gat_sidebar_window, GAT_GNOME_APP_WINDOW_TYPE, G_ADD_PRIVATE(GatSidebarWindow))

/* Boilerplate GObject code */
static void gat_sidebar_window_class_init(GatSidebarWindowClass *klass);
static void gat_sidebar_window_init(GatSidebarWindow *self);
static void gat_sidebar_window_dispose(GObject *object);

static void gat_sidebar_window_get_property(GObject *object,
                                        guint prop_id,
                                        GValue *value,
                                        GParamSpec *pspec);

static void gat_sidebar_window_set_property(GObject *object,
                                        guint prop_id,
                                        const GValue *value,
                                        GParamSpec *pspec);

enum {
        PROP_0, PROP_SIDEBAR_TITLE, N_PROPERTIES
};
static GParamSpec *obj_properties[N_PROPERTIES] = { NULL, };


static void title_cb(GtkWidget *widget,
                    GParamSpec *param,
                    gpointer userdata);
static void container_add_cb(GtkWidget *container,
                             GtkWidget *child,
                             gpointer userdata);

static void container_remove_cb(GtkWidget *container,
                                GtkWidget *child,
                                gpointer userdata);

/* Initialisation */
static void gat_sidebar_window_class_init(GatSidebarWindowClass *klass)
{
        GObjectClass *g_object_class;

        g_object_class = G_OBJECT_CLASS(klass);

        obj_properties[PROP_SIDEBAR_TITLE] =
        g_param_spec_string("side-title", "Side title", "Side title",
                "Sidebar",
                G_PARAM_READWRITE);

        g_object_class->dispose = &gat_sidebar_window_dispose;
        g_object_class->set_property = &gat_sidebar_window_set_property;
        g_object_class->get_property = &gat_sidebar_window_get_property;
        g_object_class_install_properties(g_object_class, N_PROPERTIES,
                obj_properties);
}

static void gat_sidebar_window_set_property(GObject *object,
                                        guint prop_id,
                                        const GValue *value,
                                        GParamSpec *pspec)
{
        GatSidebarWindow *self;

        self = GAT_SIDEBAR_WINDOW(object);
        switch (prop_id) {
                case PROP_SIDEBAR_TITLE:
                        if (self->priv->side_title) {
                                g_free(self->priv->side_title);
                        }
                        self->priv->side_title = g_value_dup_string(value);
                        gtk_header_bar_set_title(GTK_HEADER_BAR(self->priv->left_header),
                                self->priv->side_title);
                        break;
                default:
                        G_OBJECT_WARN_INVALID_PROPERTY_ID (object,
                                prop_id, pspec);
                        break;
        }
}

static void gat_sidebar_window_get_property(GObject *object,
                                        guint prop_id,
                                        GValue *value,
                                        GParamSpec *pspec)
{
        GatSidebarWindow *self;

        self = GAT_SIDEBAR_WINDOW(object);
        switch (prop_id) {
                case PROP_SIDEBAR_TITLE:
                        g_value_set_string(value, self->priv->side_title);
                        break;
                default:
                        G_OBJECT_WARN_INVALID_PROPERTY_ID (object,
                                prop_id, pspec);
                        break;
        }
}


static void gat_sidebar_window_init(GatSidebarWindow *self)
{
        GtkWidget *left_header, *right_header;
        GtkWidget *header;
        GtkWidget *sidebar;
        GtkWidget *content;
        GtkWidget *layout;
        GtkSizeGroup *size;
        GtkWidget *sep;
        GtkStyleContext *style;

        self->priv = gat_sidebar_window_get_instance_private(self);

        /* Left hand side */
        left_header = gtk_header_bar_new();
        gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(left_header), FALSE);
        style = gtk_widget_get_style_context(left_header);
        gtk_style_context_add_class(style, "titlebar");
        gtk_style_context_add_class(style, "gat-titlebar-left");
        self->priv->left_header = left_header;

        /* Set up headerbar */
        right_header = gtk_header_bar_new();
        gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(right_header), TRUE);
        style = gtk_widget_get_style_context(right_header);
        gtk_style_context_add_class(style, "titlebar");
        gtk_style_context_add_class(style, "gat-titlebar-right");
        self->priv->right_header = right_header;

        /* Set top header */
        header = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
        gtk_box_pack_start(GTK_BOX(header), left_header, FALSE, FALSE, 0);
        /* add a separator to the end of the left title */
        sep = gtk_separator_new(GTK_ORIENTATION_VERTICAL);
        gtk_box_pack_start(GTK_BOX(header), sep, FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX(header), right_header, TRUE, TRUE, 0);
        gtk_window_set_titlebar(GTK_WINDOW(self), header);

        /* Ensure we're notified when the title changes */
        g_signal_connect(self, "notify::title", G_CALLBACK(title_cb), NULL);

        /* Add a sidebar, which is merely a box right now. */
        sidebar = gtk_revealer_new();
        content = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
        layout = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

        /* We'll match sidebar area to child size automatically */
        g_signal_connect(sidebar, "add", G_CALLBACK(container_add_cb), self);
        g_signal_connect(sidebar, "remove", G_CALLBACK(container_remove_cb), self);

        gtk_box_pack_start(GTK_BOX(layout), sidebar, FALSE, FALSE, 0);
        gtk_box_pack_start(GTK_BOX(layout), content, TRUE, TRUE, 0);
        gtk_container_add(GTK_CONTAINER(self), layout);

        self->priv->sidebar = sidebar;
        self->priv->content = content;

        /* Ensure sidebar matches top left header */
        size = gtk_size_group_new(GTK_SIZE_GROUP_HORIZONTAL);
        gtk_size_group_add_widget(size, left_header);
        self->priv->size_group = size;
}

static void gat_sidebar_window_dispose(GObject *object)
{
        GatSidebarWindow *self = GAT_SIDEBAR_WINDOW(object);

        if (self->priv->side_title) {
                g_free(self->priv->side_title);
                self->priv->side_title = NULL;
        }

        /* Destruct */
        G_OBJECT_CLASS (gat_sidebar_window_parent_class)->dispose (object);
}

/* Utility; return a new GatSidebarWindow */
GtkWidget *gat_sidebar_window_new(void)
{
        GatSidebarWindow *self;

        self = g_object_new(GAT_SIDEBAR_WINDOW_TYPE, NULL);
        return GTK_WIDGET(self);
}


GtkWidget *gat_sidebar_window_get_sidebar(GatSidebarWindow *self)
{
        return self->priv->sidebar;
}

GtkWidget *gat_sidebar_window_get_content_area(GatSidebarWindow *self)
{
        return self->priv->content;
}

void gat_sidebar_window_set_sidebar_title(GatSidebarWindow *self, const gchar *title)
{
        g_object_set(self, "side-title", title, NULL);
}

const gchar *gat_sidebar_window_get_sidebar_title(GatSidebarWindow *self)
{
        return (const gchar*)self->priv->side_title;
}

static void title_cb(GtkWidget *widget,
                     GParamSpec *param,
                     gpointer userdata)
{
        GatSidebarWindow *self = GAT_SIDEBAR_WINDOW(widget);
        /* We only get called when the title changes */
        const gchar *title = gtk_window_get_title(GTK_WINDOW(widget));

        gtk_header_bar_set_title(GTK_HEADER_BAR(self->priv->right_header),
                title);
}

static void container_add_cb(GtkWidget *container,
                             GtkWidget *child,
                             gpointer userdata)
{
        GatSidebarWindow *self = GAT_SIDEBAR_WINDOW(userdata);
        gtk_size_group_add_widget(self->priv->size_group, child);
}

static void container_remove_cb(GtkWidget *container,
                                GtkWidget *child,
                                gpointer userdata)
{
        GatSidebarWindow *self = GAT_SIDEBAR_WINDOW(userdata);
        gtk_size_group_remove_widget(self->priv->size_group, child);
}

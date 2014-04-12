/*
 * gat-sidebar.c
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

#include "gat-sidebar.h"

struct _GatSidebarPriv {
        GtkWidget *stack;
};

G_DEFINE_TYPE_WITH_CODE(GatSidebar, gat_sidebar, GTK_TYPE_SCROLLED_WINDOW, G_ADD_PRIVATE(GatSidebar))

/* Boilerplate GObject code */
static void gat_sidebar_class_init(GatSidebarClass *klass);
static void gat_sidebar_init(GatSidebar *self);
static void gat_sidebar_dispose(GObject *object);
static void gat_sidebar_set_property(GObject *object,
                                     guint prop_id,
                                     const GValue *value,
                                     GParamSpec *pspec);
static void gat_sidebar_get_property(GObject *object,
                                     guint prop_id,
                                     GValue *value,
                                     GParamSpec *pspec);

enum {
        PROP_0, PROP_STACK, N_PROPERTIES
};
static GParamSpec *obj_properties[N_PROPERTIES] = { NULL, };

/* Initialisation */
static void gat_sidebar_class_init(GatSidebarClass *klass)
{
        GObjectClass *g_object_class;

        obj_properties[PROP_STACK] =
        g_param_spec_string("stack", "Stack", "Stack",
                "Stack",
                G_PARAM_READWRITE);

        g_object_class = G_OBJECT_CLASS(klass);
        g_object_class->dispose = &gat_sidebar_dispose;
        g_object_class->set_property = &gat_sidebar_set_property;
        g_object_class->get_property = &gat_sidebar_get_property;
        g_object_class_install_properties(g_object_class, N_PROPERTIES,
                obj_properties);
}

static void gat_sidebar_set_property(GObject *object,
                                     guint prop_id,
                                     const GValue *value,
                                     GParamSpec *pspec)
{
        GatSidebar *self;

        self = GAT_SIDEBAR(object);
        switch (prop_id) {
                case PROP_STACK:
                        self->priv->stack = GTK_WIDGET(g_value_get_pointer(value));
                        break;
                default:
                        G_OBJECT_WARN_INVALID_PROPERTY_ID (object,
                                prop_id, pspec);
                        break;
        }
}

static void gat_sidebar_get_property(GObject *object,
                                     guint prop_id,
                                     GValue *value,
                                     GParamSpec *pspec)
{
        GatSidebar *self;

        self = GAT_SIDEBAR(object);
        switch (prop_id) {
                case PROP_STACK:
                        g_value_set_pointer(value, self->priv->stack);
                        break;
                default:
                        G_OBJECT_WARN_INVALID_PROPERTY_ID (object,
                                prop_id, pspec);
                        break;
        }
}

static void gat_sidebar_init(GatSidebar *self)
{
        self->priv = gat_sidebar_get_instance_private(self);

        /* By default we're not scrollable */
        gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(self),
                GTK_POLICY_NEVER, GTK_POLICY_NEVER);
}

static void gat_sidebar_dispose(GObject *object)
{
        /* Destruct */
        G_OBJECT_CLASS (gat_sidebar_parent_class)->dispose(object);
}

/* Utility; return a new GatSidebar */
GtkWidget *gat_sidebar_new(void)
{
        GatSidebar *self;

        self = g_object_new(GAT_SIDEBAR_TYPE, NULL);
        return GTK_WIDGET(self);
}

void gat_sidebar_set_stack(GatSidebar *sidebar, GtkStack *stack)
{
        g_assert(sidebar != NULL);
        g_assert(stack != NULL);

        g_object_set(sidebar, "stack", stack, NULL);
}

GtkStack *gat_sidebar_get_stack(GatSidebar *sidebar)
{
        return GTK_STACK(sidebar->priv->stack);
}

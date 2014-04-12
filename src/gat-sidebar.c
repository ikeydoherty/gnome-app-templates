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
        int x; /* Reserved */
};

G_DEFINE_TYPE_WITH_CODE(GatSidebar, gat_sidebar, GTK_TYPE_SCROLLED_WINDOW, G_ADD_PRIVATE(GatSidebar))

/* Boilerplate GObject code */
static void gat_sidebar_class_init(GatSidebarClass *klass);
static void gat_sidebar_init(GatSidebar *self);
static void gat_sidebar_dispose(GObject *object);

/* Initialisation */
static void gat_sidebar_class_init(GatSidebarClass *klass)
{
        GObjectClass *g_object_class;

        g_object_class = G_OBJECT_CLASS(klass);
        g_object_class->dispose = &gat_sidebar_dispose;
}

static void gat_sidebar_init(GatSidebar *self)
{
}

static void gat_sidebar_dispose(GObject *object)
{
        /* Destruct */
        G_OBJECT_CLASS (gat_sidebar_parent_class)->dispose (object);
}

/* Utility; return a new GatSidebar */
GtkWidget *gat_sidebar_new(void)
{
        GatSidebar *self;

        self = g_object_new(GAT_SIDEBAR_TYPE, NULL);
        return GTK_WIDGET(self);
}

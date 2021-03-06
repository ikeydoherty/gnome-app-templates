/*
 * gat-sidebar.c
 * 
 * Copyright 2014 Ikey Doherty <ikey.doherty@gmail.com>
 * 
 * gnome-app-templates is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2.1
 * of the License, or (at your option) any later version.
 */

#include "gat-sidebar.h"

struct _GatSidebarPriv {
        GtkWidget *stack;
        GHashTable *table;
        gulong add_id;
        gulong remove_id;
        gulong change_id;
        gulong active_id;
};

G_DEFINE_TYPE_WITH_CODE(GatSidebar, gat_sidebar, GTK_TYPE_LIST_BOX, G_ADD_PRIVATE(GatSidebar))

/* Used privately to track stack pages */
typedef struct StackPageMeta {
        gchar *title;
        GtkWidget *widget;
        GtkWidget *sidebar_item;
        GtkWidget *sidebar_row;
        gulong notify_id;
} StackPageMeta;

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

static void rebuild_stack(GatSidebar *self);
static void cleanup_val(gpointer data);

enum {
        PROP_0, PROP_STACK, N_PROPERTIES
};
static GParamSpec *obj_properties[N_PROPERTIES] = { NULL, };

/* Initialisation */
static void gat_sidebar_class_init(GatSidebarClass *klass)
{
        GObjectClass *g_object_class;

        obj_properties[PROP_STACK] =
        g_param_spec_pointer("stack", "Stack",
                "Associated stack for this GatSidebar",
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
                        /* Disconnect old handlers */
                        if (self->priv->stack) {
                                g_signal_handler_disconnect(self->priv->stack,
                                        self->priv->add_id);
                                self->priv->add_id = 0;
                                g_signal_handler_disconnect(self->priv->stack,
                                        self->priv->remove_id);
                                self->priv->remove_id = 0;
                                g_signal_handler_disconnect(self->priv->stack,
                                        self->priv->change_id);
                                self->priv->change_id = 0;
                        }
                        self->priv->stack = GTK_WIDGET(g_value_get_pointer(value));
                        rebuild_stack(self);
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

static void update_header(GtkListBoxRow *row,
                          GtkListBoxRow *before,
                          gpointer userdata)
{
        GtkWidget *ret = NULL;

        if (before && !gtk_list_box_row_get_header(row)) {
                ret = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
                gtk_list_box_row_set_header(row, ret);
        }
}

static gint sort_list(GtkListBoxRow *row1,
                      GtkListBoxRow *row2,
                      gpointer userdata)
{
        StackPageMeta *meta = NULL;
        GtkWidget *kidlet = NULL;
        gint left = 0; gint right = 0;
        GatSidebar *self;

        self = GAT_SIDEBAR(userdata);

        if (row1) {
                kidlet = gtk_bin_get_child(GTK_BIN(row1));
                meta = g_object_get_data(G_OBJECT(kidlet), "gat-meta");
                gtk_container_child_get(GTK_CONTAINER(self->priv->stack),
                        meta->widget, "position", &left, NULL);
        }

        if (row2) {
                kidlet = gtk_bin_get_child(GTK_BIN(row2));
                meta = g_object_get_data(G_OBJECT(kidlet), "gat-meta");
                gtk_container_child_get(GTK_CONTAINER(self->priv->stack),
                        meta->widget, "position", &right, NULL);
        }

        if (left < right) {
                return  -1;
        }
        if (left == right) {
                return 0;
        }
        return 1;
}
static void row_selected(GtkListBox *box,
                          GtkListBoxRow *row,
                          gpointer userdata)
{
        GatSidebar *self;
        GtkWidget *child = NULL;
        StackPageMeta *meta = NULL;

        self = GAT_SIDEBAR(userdata);
        if (!row) {
                return;
        }

        child = gtk_bin_get_child(GTK_BIN(row));
        meta = g_object_get_data(G_OBJECT(child), "gat-meta");
        if (!meta) {
                return;
        }

        gtk_stack_set_visible_child(GTK_STACK(self->priv->stack),
                meta->widget);
}

static void gat_sidebar_init(GatSidebar *self)
{
        GtkStyleContext *style;

        self->priv = gat_sidebar_get_instance_private(self);

        /* We add items to a vertical box */
        gtk_list_box_set_header_func(GTK_LIST_BOX(self), update_header,
                self, NULL);
        gtk_list_box_set_sort_func(GTK_LIST_BOX(self), sort_list,
                self, NULL);

        style = gtk_widget_get_style_context(GTK_WIDGET(self));
        gtk_style_context_add_class(style, "sidebar");

        /* Store this for later abuse */
        self->priv->table = g_hash_table_new_full(g_direct_hash,
                g_direct_equal, NULL, cleanup_val);

        /* Enable switching pages with us. */
        self->priv->active_id = g_signal_connect(self,
                "row-selected", G_CALLBACK(row_selected), self);
}

static void gat_sidebar_dispose(GObject *object)
{
        GatSidebar *self;

        self = GAT_SIDEBAR(object);

        /* Ensure we kill signals first */
        if (self->priv->add_id != 0) {
                g_signal_handler_disconnect(self->priv->stack, self->priv->add_id);
                self->priv->add_id = 0;
        }
        if (self->priv->remove_id != 0) {
                g_signal_handler_disconnect(self->priv->stack, self->priv->remove_id);
                self->priv->remove_id = 0;
        }
        if (self->priv->change_id != 0) {
                g_signal_handler_disconnect(self->priv->stack, self->priv->change_id);
                self->priv->change_id = 0;
        }

        if (self->priv->table) {
                g_hash_table_unref(self->priv->table);
                self->priv->table = NULL;
        }
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

static void child_cb(GtkWidget *widget,
                     GParamSpec *prop,
                     gpointer userdata)
{
        StackPageMeta *meta = NULL;
        gchar *title = NULL;
        GatSidebar *self;

        self = GAT_SIDEBAR(userdata);
        meta = g_hash_table_lookup(self->priv->table, widget);
        g_assert(meta != NULL);

        if (g_str_equal(prop->name, "title")) {
                gtk_container_child_get(GTK_CONTAINER(self->priv->stack), widget,
                        "title", &title, NULL);

                /* We only have a label widget now for the row */
                gtk_label_set_text(GTK_LABEL(meta->sidebar_item), title);
                if (meta->title) {
                        g_free(meta->title);
                        meta->title = title;
                }
        } else if (g_str_equal(prop->name, "position")) {
                gtk_list_box_invalidate_sort(GTK_LIST_BOX(self));
        }
}

static void add_cb(GtkContainer *container,
                   GtkWidget *widget,
                   gpointer userdata)
{
        GtkStyleContext *style;
        StackPageMeta *meta = NULL;
        GatSidebar *self = NULL;
        GtkWidget *item = NULL;
        GtkWidget *row = NULL;

        self = GAT_SIDEBAR(userdata);

        /* Check we don't actually already know about this widget */
        if (g_hash_table_lookup(self->priv->table, widget)) {
                return;
        }

        /* Make a pretty item when we add kids */
        item = gtk_label_new("item");
        gtk_widget_set_halign(item, GTK_ALIGN_START);
        gtk_widget_set_valign(item, GTK_ALIGN_CENTER);
        row = gtk_list_box_row_new();
        gtk_container_add(GTK_CONTAINER(row), item);
        gtk_widget_show(item);

        /* Fix up styling */
        style = gtk_widget_get_style_context(row);
        gtk_style_context_add_class(style, "sidebar-item");

        /* Store the meta info */
        meta = g_new0(StackPageMeta, 1);
        meta->widget = widget;
        meta->sidebar_item = item;
        meta->sidebar_row = row;
        /* Hook up for events */
        meta->notify_id = g_signal_connect(widget, "child-notify::title",
                G_CALLBACK(child_cb), self);

        g_object_set_data(G_OBJECT(item), "gat-meta", meta);
        g_hash_table_insert(self->priv->table, widget, meta);

        gtk_container_add(GTK_CONTAINER(self), row);
}

static void remove_cb(GtkContainer *container,
                      GtkWidget *widget,
                      gpointer userdata)
{
        GatSidebar *self;
        StackPageMeta *meta = NULL;

        self = GAT_SIDEBAR(userdata);
        meta = g_hash_table_lookup(self->priv->table, widget);
        if (!meta) {
                return;
        }
        /* Remove from sidebar */
        g_signal_handler_disconnect(widget, meta->notify_id);
        gtk_widget_destroy(meta->sidebar_item);
        meta->sidebar_item = NULL;
        g_hash_table_remove(self->priv->table, widget);
}

static void visible_cb(GtkWidget *widget,
                       GParamSpec *prop,
                       gpointer userdata)
{
        StackPageMeta *item = NULL;
        GtkWidget *child = NULL;
        GatSidebar *self;

        self = GAT_SIDEBAR(userdata);
        g_object_get(widget, "visible-child", &child, NULL);
        if (!child) {
                return;
        }
        item = g_hash_table_lookup(self->priv->table, child);
        if (!item) {
                g_warning("Unknown child in GatSidebar");
                return;
        }
        /* Lets not force a chain here */
        g_signal_handler_block(self, self->priv->active_id);
        gtk_list_box_select_row(GTK_LIST_BOX(self),
                GTK_LIST_BOX_ROW(item->sidebar_row));
        g_signal_handler_unblock(self, self->priv->active_id);
}

static void rebuild_stack(GatSidebar *self)
{
        GList *sprogs, *kid = NULL;

        /* Rebuild ourselves */
        self->priv->add_id = g_signal_connect(self->priv->stack, "add",
                G_CALLBACK(add_cb), self);
        self->priv->remove_id = g_signal_connect(self->priv->stack,
                "remove", G_CALLBACK(remove_cb), self);
        self->priv->change_id = g_signal_connect(self->priv->stack,
                "notify::visible-child", G_CALLBACK(visible_cb), self);

        /* Fire add for each kid */
        sprogs = gtk_container_get_children(GTK_CONTAINER(self->priv->stack));
        if (!sprogs) {
                return;
        }

        for (kid = sprogs; kid->next != NULL; kid = kid->next) {
                /* Add existing kids */
                add_cb(GTK_CONTAINER(self->priv->stack), GTK_WIDGET(kid->data), self);
        }
}

/* Cleanup a StackPageMeta */
static void cleanup_val(gpointer data)
{
        StackPageMeta *meta = (StackPageMeta*)data;
        if (!meta) {
                return;
        }
        if (meta->title) {
                g_free(meta->title);
                meta->title = NULL;
        }
        g_free(data);
}

-include $(top_srcdir)/common.mk
-include $(INTROSPECTION_MAKEFILE)

DISTCHECK_CONFIGURE_FLAGS = --enable-introspection

lib_LTLIBRARIES = libgapptemplates.la

libgapptemplates_la_SOURCES = \
	gat-sidebar.h \
	gat-sidebar.c \
	gat-gnome-app-window.h \
	gat-gnome-app-window.c \
	gat-sidebar-window.h \
	gat-sidebar-window.c \
	../data/gat-resources.h \
	../data/gat-resources.c

include_HEADERS = \
	gat-sidebar.h \
	gat-gnome-app-window.h \
	gat-sidebar-window.h

libgapptemplates_la_CFLAGS = \
	$(GTK3_CFLAGS) \
	$(AM_CFLAGS)

libgapptemplates_la_LIBADD = \
	$(GTK3_LIBS)

INTROSPECTION_GIRS =
INTROSPECTION_SCANNER_ARGS = --add-include-path=$(top_srcdir)/src --warn-all
INTROSPECTION_COMPILER_ARGS = --includedir=$(top_srcdir)

if HAVE_INTROSPECTION
introspection_sources = $(libgapptemplates_la_SOURCES)

Gat-1.0.gir: libgapptemplates.la
Gat_1_0_gir_INCLUDES = GObject-2.0 Gtk-3.0
Gat_1_0_gir_CFLAGS = $(INCLUDES) -I $(top_srcdir)/src/
Gat_1_0_gir_LIBS = libgapptemplates.la
Gat_1_0_gir_FILES = $(introspection_sources)
INTROSPECTION_GIRS += Gat-1.0.gir

girdir = $(datadir)/gir-1.0
gir_DATA = $(INTROSPECTION_GIRS)

typelibdir = $(libdir)/girepository-1.0
typelib_DATA = $(INTROSPECTION_GIRS:.gir=.typelib)

CLEANFILES = $(gir_DATA) $(typelib_DATA)
endif

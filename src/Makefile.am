-include $(top_srcdir)/common.mk

lib_LTLIBRARIES = libgapptemplates.la

libgapptemplates_la_SOURCES = \
	gnome-app-window.h \
	gnome-app-window.c \
	sidebar-window.c \
	sidebar-window.h

libgapptemplates_la_CFLAGS = \
	$(GTK3_CFLAGS) \
	$(AM_CFLAGS)

libgapptemplates_la_LIBADD = \
	$(GTK3_LIBS)

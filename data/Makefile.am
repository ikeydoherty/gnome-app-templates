-include $(top_srcdir)/common.mk

resource_files = $(shell glib-compile-resources --sourcedir=$(srcdir) --generate-dependencies $(srcdir)/gat.gresource.xml)

EXTRA_DIST = \
	gat.gresource.xml \
	style.css \
	gat.xml

BUILT_SOURCES = \
	gat-resources.h \
	gat-resources.c

gat-resources.h: gat.gresource.xml $(resource_files)
	glib-compile-resources --target=$@ --sourcedir=$(srcdir) --generate-header --c-name gat $<

gat-resources.c: gat.gresource.xml $(resource_files)
	glib-compile-resources --target=$@ --sourcedir=$(srcdir) --generate-source --c-name gat $<

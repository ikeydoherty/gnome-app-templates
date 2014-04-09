-include $(top_srcdir)/common.mk

if BUILD_DEMOS

bin_PROGRAMS = \
	simple-demo

simple_demo_SOURCES = \
	simple.c

simple_demo_CFLAGS = \
	$(GTK3_CFLAGS) \
	$(AM_CFLAGS)

simple_demo_LDADD = \
	$(GTK3_LIBS) \
	../src/libgapptemplates.la

endif

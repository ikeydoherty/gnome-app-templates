AC_INIT([GNOME App Templates], 1, [ikey.doherty@gmail.com], [gnome-app-templates], [https://github.com/ikeydoherty/gnome-app-templates/])
AM_INIT_AUTOMAKE([-Wno-portability no-dist-gzip dist-xz foreign subdir-objects])
AC_PROG_CC
AC_PROG_CC_STDC
LT_PREREQ(2.2)
AC_CONFIG_HEADERS([config.h])
AC_PREFIX_DEFAULT(/usr/local)
AM_SILENT_RULES([yes])
LT_INIT([disable-static])

# Package requirements
PKG_CHECK_MODULES([GOBJECT], [gobject-2.0 >= 2.38.0])
PKG_CHECK_MODULES([GTK3], [gtk+-3.0 >= 3.10.0])


GOBJECT_INTROSPECTION_CHECK([1.38.0])

# check for gtk-doc
m4_ifdef([GTK_DOC_CHECK], [
GTK_DOC_CHECK([1.14],[--flavour no-tmpl])
],[
AM_CONDITIONAL([ENABLE_GTK_DOC], false)
])

AC_CONFIG_MACRO_DIR([m4])

AC_ARG_ENABLE(demos, AS_HELP_STRING([--enable-demos], [enable demos @<:@default=no@:>@]),
	      [], [enable_demos=no])
AS_IF([test "x$enable_demos" = "xyes"],
	[AC_DEFINE([DEMOS], [1], [Building demos])],
	[])
AM_CONDITIONAL([BUILD_DEMOS], [test x$enable_demos = x"yes"])

AC_CONFIG_FILES(Makefile
		data/Makefile
                src/Makefile
		demo/Makefile
		docs/Makefile)
AC_OUTPUT


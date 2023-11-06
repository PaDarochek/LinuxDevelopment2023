#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([rhasher], [1.0.0])
AM_INIT_AUTOMAKE([foreign 1.13])
AC_CONFIG_SRCDIR([rhasher.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB([rhash],[rhash_library_init, rhash_msg, rhash_file, rhash_print_bytes],
    [],[AC_MSG_ERROR([Rhash is needed])])

AC_ARG_WITH([readline],
    [AS_HELP_STRING([--without-readline],
        [disable support for readline])],
    [],
    [with_readline=yes])
LIBREADLINE=
AS_IF([test "x$with_readline" == xyes],
    [AC_CHECK_LIB([readline], [readline, add_history],
        [AC_SUBST([LIBREADLINE], ["-lreadline"])
         AC_DEFINE([USE_READLINE], [],
                    [Define if you have libreadline])
        ])])

# Checks for header files.
AC_CHECK_HEADER([rhash.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([strerror])

AC_OUTPUT

AC_INIT([kanaedit], [0.1])
AC_PROG_SED
AC_PROG_CXX
AC_CHECK_HEADERS_ONCE([SFML/System.hpp] [SFML/Window.hpp] [SFML/Graphics.hpp])
AC_CHECK_LIB([sfml-system], [String])
AC_CHECK_LIB([sfml-window], [Window])
AC_CHECK_LIB([sfml-graphics], [Font])
AC_CHECK_FUNCS_ONCE([sprintf] [snprintf] [execv])
AC_CHECK_PROG([UNZIP], [unzip], [yes])
AS_IF([test "x$UNZIP" = xyes], [AC_DEFINE([HAVE_UNZIP], [1], [unzip detected.])])
AM_INIT_AUTOMAKE([-Wall foreign])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT

AC_INIT([kanaedit], [0.1])

SAVED_LDFLAGS=$LDFLAGS

AC_PROG_SED
AC_PROG_CXX
AC_LANG_PUSH([C++])
AC_REQUIRE_CPP
AC_CHECK_HEADERS([SFML/System.hpp] [SFML/Window.hpp] [SFML/Graphics.hpp], , [AC_MSG_ERROR([Could not find SFML header file.])])

LDFLAGS="$LDFLAGS -lsfml-system"
AC_MSG_CHECKING([for link against -lsfml-system])
AC_LINK_IFELSE([AC_LANG_PROGRAM([#include <SFML/System.hpp>], [sf::String dummy])], 
    [AC_DEFINE([HAVE_SFML_SYSTEM], [1], [SFML system library])] , [AC_MSG_ERROR([Could not link to libsfml-system.])])
AC_MSG_RESULT([success])
LDFLAGS=$SAVED_LDFLAGS

LDFLAGS="$LDFLAGS -lsfml-window"
AC_MSG_CHECKING([for link against -lsfml-window])
AC_LINK_IFELSE([AC_LANG_PROGRAM([#include <SFML/Window.hpp>], [sf::Window dummy])], 
    [AC_DEFINE([HAVE_SFML_WINDOW], [1], [SFML window library])] , [AC_MSG_ERROR([Could not link to libsfml-window.])])
AC_MSG_RESULT([success])
LDFLAGS=$SAVED_LDFLAGS

LDFLAGS="$LDFLAGS -lsfml-graphics"
AC_MSG_CHECKING([for link against -lsfml-graphics])
AC_LINK_IFELSE([AC_LANG_PROGRAM([#include <SFML/Graphics.hpp>], [sf::Font dummy])], 
    [AC_DEFINE([HAVE_SFML_GRAPHICS], [1], [SFML graphics library])] , [AC_MSG_ERROR([Could not link to libsfml-graphics.])])
AC_MSG_RESULT([success])
LDFLAGS=$SAVED_LDFLAGS

#AC_CHECK_LIB([sfml-graphics], [Font], , [AC_MSG_ERROR([Could not find libsfml-graphics.])])
AC_LANG_POP()
AC_CHECK_FUNCS_ONCE([sprintf] [snprintf] [execvp])
AC_CHECK_PROG([UNZIP], [unzip], [yes])
AS_IF([test "x$UNZIP" != xyes], [AC_MSG_ERROR([Could not find unzip in PATH])])
AM_INIT_AUTOMAKE([-Wall foreign])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT

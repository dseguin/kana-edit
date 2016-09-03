AC_INIT([kanaedit], [0.2.1])

KANA_DEFAULT_SAVE_DIR="$HOME/Documents"
SAVED_LIBS=$LIBS

AC_PROG_CXX
AC_PROG_CXXCPP
AC_LANG_PUSH([C++])
AX_CXX_COMPILE_STDCXX_11([noext], [optional])
AC_REQUIRE_CPP
AC_CHECK_HEADERS([SFML/System.hpp] [SFML/Window.hpp] [SFML/Graphics.hpp], , [AC_MSG_ERROR([Could not find SFML header file.])])

LIBS="-lsfml-system"
AC_MSG_CHECKING([for link against -lsfml-system])
AC_LINK_IFELSE([AC_LANG_PROGRAM([#include <SFML/System.hpp>], [sf::String dummy])], 
    [AC_DEFINE([HAVE_SFML_SYSTEM], [1], [SFML system library])] , [AC_MSG_ERROR([Could not link to libsfml-system.])])
AC_MSG_RESULT([success])
LIBS=$SAVED_LIBS

LIBS="-lsfml-window"
AC_MSG_CHECKING([for link against -lsfml-window])
AC_LINK_IFELSE([AC_LANG_PROGRAM([#include <SFML/Window.hpp>], [sf::Window dummy])], 
    [AC_DEFINE([HAVE_SFML_WINDOW], [1], [SFML window library])] , [AC_MSG_ERROR([Could not link to libsfml-window.])])
AC_MSG_RESULT([success])
LIBS=$SAVED_LIBS

LIBS="-lsfml-graphics"
AC_MSG_CHECKING([for link against -lsfml-graphics])
AC_LINK_IFELSE([AC_LANG_PROGRAM([#include <SFML/Graphics.hpp>], [sf::Font dummy])], 
    [AC_DEFINE([HAVE_SFML_GRAPHICS], [1], [SFML graphics library])] , [AC_MSG_ERROR([Could not link to libsfml-graphics.])])
AC_MSG_RESULT([success])
LIBS=$SAVED_LIBS

AC_DEFINE_UNQUOTED([DEFAULT_SAVE_PATH], ["$KANA_DEFAULT_SAVE_DIR"], [Default save path for text files])
AC_LANG_POP()
AC_CHECK_FUNCS_ONCE([sprintf] [snprintf] [execvp])
AC_CHECK_PROG([UNZIP], [unzip], [yes])
AS_IF([test "x$UNZIP" != xyes], [AC_MSG_ERROR([Could not find unzip in PATH])])

AC_CONFIG_COMMANDS([unzip], [find "${ac_abs_top_srcdir}"/resources/ -type f -name "*.h.zip" -exec unzip -d "${ac_abs_top_srcdir}"/include/ {} ';'])
AM_INIT_AUTOMAKE([-Wall foreign])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT

dnl $Id$
dnl config.m4 for extension tmpy

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(tmpy, for tmpy support,
dnl Make sure that the comment is aligned:
dnl [  --with-tmpy             Include tmpy support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(tmpy, whether to enable tmpy support,
Make sure that the comment is aligned:
[  --enable-tmpy           Enable tmpy support])

if test "$PHP_TMPY" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-tmpy -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/tmpy.h"  # you most likely want to change this
  dnl if test -r $PHP_TMPY/$SEARCH_FOR; then # path given as parameter
  dnl   TMPY_DIR=$PHP_TMPY
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for tmpy files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       TMPY_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$TMPY_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the tmpy distribution])
  dnl fi

  dnl # --with-tmpy -> add include path
  dnl PHP_ADD_INCLUDE($TMPY_DIR/include)

  dnl # --with-tmpy -> check for lib and symbol presence
  dnl LIBNAME=tmpy # you may want to change this
  dnl LIBSYMBOL=tmpy # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $TMPY_DIR/lib, TMPY_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_TMPYLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong tmpy lib version or lib not found])
  dnl ],[
  dnl   -L$TMPY_DIR/lib -lm
  dnl ])
  dnl
  dnl PHP_SUBST(TMPY_SHARED_LIBADD)

  PHP_NEW_EXTENSION(tmpy, tmpy.c, $ext_shared)
fi

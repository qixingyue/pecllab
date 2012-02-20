dnl $Id$
dnl config.m4 for extension first_ext

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(first_ext, for first_ext support,
dnl Make sure that the comment is aligned:
dnl [  --with-first_ext             Include first_ext support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(first_ext, whether to enable first_ext support,
Make sure that the comment is aligned:
[  --enable-first_ext           Enable first_ext support])

if test "$PHP_FIRST_EXT" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-first_ext -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/first_ext.h"  # you most likely want to change this
  dnl if test -r $PHP_FIRST_EXT/$SEARCH_FOR; then # path given as parameter
  dnl   FIRST_EXT_DIR=$PHP_FIRST_EXT
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for first_ext files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       FIRST_EXT_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$FIRST_EXT_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the first_ext distribution])
  dnl fi

  dnl # --with-first_ext -> add include path
  dnl PHP_ADD_INCLUDE($FIRST_EXT_DIR/include)

  dnl # --with-first_ext -> check for lib and symbol presence
  dnl LIBNAME=first_ext # you may want to change this
  dnl LIBSYMBOL=first_ext # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $FIRST_EXT_DIR/lib, FIRST_EXT_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_FIRST_EXTLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong first_ext lib version or lib not found])
  dnl ],[
  dnl   -L$FIRST_EXT_DIR/lib -lm
  dnl ])
  dnl
  dnl PHP_SUBST(FIRST_EXT_SHARED_LIBADD)

  PHP_NEW_EXTENSION(first_ext, first_ext.c, $ext_shared)
fi

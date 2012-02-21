/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2012 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id: header 321634 2012-01-01 13:15:04Z felipe $ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_tmpy.h"

ZEND_DECLARE_MODULE_GLOBALS(tmpy)

/* True global resources - no need for thread safety here */
static int le_tmpy;

/* {{{ tmpy_functions[]
 *
 * Every user visible function must have an entry in tmpy_functions[].
 */
const zend_function_entry tmpy_functions[] = {
	PHP_FE(tmpy_getpy,	NULL)
	PHP_FE(tmpy_getszm,	NULL)
	PHP_FE_END	/* Must be the last line in tmpy_functions[] */
};
/* }}} */

/* {{{ tmpy_module_entry
 */
zend_module_entry tmpy_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"tmpy",
	tmpy_functions,
	PHP_MINIT(tmpy),
	PHP_MSHUTDOWN(tmpy),
	PHP_RINIT(tmpy),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(tmpy),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(tmpy),
#if ZEND_MODULE_API_NO >= 20010901
	"0.1", /* Replace with version number for your extension */
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_TMPY
ZEND_GET_MODULE(tmpy)
#endif

/* {{{ PHP_INI
 */
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("tmpy.ckpath", "qxy", PHP_INI_ALL, OnUpdateString, ckpath, zend_tmpy_globals, tmpy_globals)
PHP_INI_END()
/* }}} */

/* {{{ php_tmpy_init_globals
 */
static void php_tmpy_init_globals(zend_tmpy_globals *tmpy_globals)
{
	tmpy_globals->ckpath = NULL;
}
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(tmpy)
{
	REGISTER_MAIN_STRING_CONSTANT("TMPYAUTHOR","<A HREF=\"http://istrone.com\">ISTRONE</A>",CONST_CS | CONST_PERSISTENT);
	REGISTER_INI_ENTRIES();
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(tmpy)
{
	UNREGISTER_INI_ENTRIES();
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(tmpy)
{
	if(strcmp(TMPY_G(ckpath),"qxy")==0) {
	   php_error(E_ERROR,"dictionary not setted!");
	}
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(tmpy)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(tmpy)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "tmpy support", "enabled");
	php_info_print_table_end();

	DISPLAY_INI_ENTRIES();
}
/* }}} */


/**
* parse a line to an php array item
*/
zval *parseLine(char *line,int l){
   zval *resArray;
   char *tmp=line,keys[3][8]={"yin","shengmu","yunmu"},*bp= (char *)emalloc(sizeof(char)*l),*bpp=bp;
   int f=0;
   MAKE_STD_ZVAL(resArray);
   array_init(resArray);		//make resArray to an array
   memset(bp,0,l);
   while(tmp++ && *tmp!='\0'){
	if(*tmp == ',' ) {
           f++;
	   if(f>=2 && f<=4) {
	      add_assoc_string(resArray,keys[f-2],bp,1);
	   }
           memset(bp,0,l);
	   bpp = bp;
	} else {
	   *bpp++ = *tmp;
	}
        
   }
   return resArray;
}



/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/

/* {{{ proto array tmpy_getpy(string hz)
   getPinyins */
PHP_FUNCTION(tmpy_getpy)
{
	char *hz = NULL;
	int argc = ZEND_NUM_ARGS();
	int hz_len;

	if (zend_parse_parameters(argc TSRMLS_CC, "s", &hz, &hz_len) == FAILURE) 
		return;
	char **items[hz_len][30];
	php_stream *stream;
	char *mode="r",*line=(char *)emalloc(30*sizeof(char));
	memset(line,0,30);
	int options = ENFORCE_SAFE_MODE | REPORT_ERRORS,pos;
	stream = php_stream_open_wrapper(TMPY_G(ckpath),mode,options,NULL);
	if(!stream){
	    RETURN_FALSE;
	}
	array_init(return_value);
	while(php_stream_gets(stream,line,30)){
	     if(strncmp(line,hz,hz_len)==0) {
		add_next_index_zval(return_value,parseLine(line,strlen(line)));
	     }
		memset(line,0,30);
	}
	php_stream_close(stream);
	efree(line);
}
/* }}} */

/* {{{ proto array tmpy_getszm(string hz)
   get Shou zi mu */
PHP_FUNCTION(tmpy_getszm)
{
	char *hz = NULL;
	int argc = ZEND_NUM_ARGS();
	int hz_len;

	if (zend_parse_parameters(argc TSRMLS_CC, "s", &hz, &hz_len) == FAILURE) 
		return;

	php_error(E_WARNING, "tmpy_getszm: not yet implemented");
}
/* }}} */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */

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
#include "php_first_ext.h"

ZEND_DECLARE_MODULE_GLOBALS(first_ext)

/* True global resources - no need for thread safety here */
static int le_first_ext;

/* {{{ first_ext_functions[]
 *
 * Every user visible function must have an entry in first_ext_functions[].
 */
const zend_function_entry first_ext_functions[] = {
	PHP_FE(confirm_first_ext_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE(calcpi,	NULL)
	PHP_FE(reverse,	NULL)
	PHP_FE(uniquechars,	NULL)
	PHP_FE_END	/* Must be the last line in first_ext_functions[] */
};
/* }}} */

/* {{{ first_ext_module_entry
 */
zend_module_entry first_ext_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"first_ext",
	first_ext_functions,
	PHP_MINIT(first_ext),
	PHP_MSHUTDOWN(first_ext),
	PHP_RINIT(first_ext),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(first_ext),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(first_ext),
#if ZEND_MODULE_API_NO >= 20010901
	"0.1", /* Replace with version number for your extension */
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_FIRST_EXT
ZEND_GET_MODULE(first_ext)
#endif

/* {{{ PHP_INI
 */
PHP_INI_BEGIN()
   PHP_INI_ENTRY("first_ext.greeting","Helloworld",PHP_INI_ALL,NULL)
PHP_INI_END()
/* }}} */

/* {{{ php_first_ext_init_globals
 */
static void php_first_ext_init_globals(zend_first_ext_globals *first_ext_globals)
{
	first_ext_globals->global_value = 0;
	first_ext_globals->global_string = NULL;
}
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
*/
PHP_MINIT_FUNCTION(first_ext)
{
	REGISTER_INI_ENTRIES();
	REGISTER_STRING_CONSTANT("FEXTAUTHOR","<a href=\"http://istrone.com\">istrone</a>",CONST_CS | CONST_PERSISTENT);
	FIRST_EXT_G(global_value)=300;
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(first_ext)
{
	UNREGISTER_INI_ENTRIES();
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(first_ext)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(first_ext)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(first_ext)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "first_ext support", "enabled");
	php_info_print_table_end();

	DISPLAY_INI_ENTRIES();
}
/* }}} */


/* Remove the following function when you have succesfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_first_ext_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_first_ext_compiled)
{
	char *arg = NULL;
	int arg_len, len;
	char *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "first_ext", arg);
	RETURN_STRINGL(strg, len, 0);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/

/* {{{ proto double calcpi(int iterations)
   Calculate Pi */
PHP_FUNCTION(calcpi)
{
	zend_printf("%ld",FIRST_EXT_G(global_value));
	const char *greeting = INI_STR("first_ext.greeting");
	zend_printf("%s<br>",greeting);
	int argc = ZEND_NUM_ARGS();
	long iterations;
	int index, hits = 0;
	double randx, randy, distance, value;
	if (zend_parse_parameters(argc TSRMLS_CC, "l", &iterations) == FAILURE) 
		return;
	for(index = 0; index < iterations; index++ ) {
	    randx = rand();
	    randy = rand();
	    randx /= RAND_MAX;
	    randy /= RAND_MAX;
	    distance = sqrt( (randx * randx) + (randy * randy) );
	    if(distance < 1.0) {
	     	hits++;
	    }
	   value =( (double) hits / (double) iterations) ;
	   value *= 4.0;
	}
       value =( (double) hits / (double) iterations) ;
       value *= 4.0;
       RETVAL_DOUBLE( value );
}
/* }}} */

/* {{{ proto string reverse(string input)
   Reverse the input string */
PHP_FUNCTION(reverse)
{
	char *input = NULL;
	int argc = ZEND_NUM_ARGS();
	int input_len;
	char *workstr = NULL;
	int index;
	if (zend_parse_parameters(argc TSRMLS_CC, "s", &input, &input_len) == FAILURE) 
		return;
	workstr = (char*) emalloc(input_len+1);
	memset(workstr,0,input_len+1);	//all to zero
	for(index = 0 ; index < input_len ; index++ ) {
		workstr[index] = input[input_len-(index+1)];
	}
	RETVAL_STRING(workstr,1);
	efree(workstr);

}
/* }}} */

/* {{{ proto array uniquechars(string input [, bool case_sensitive])
   Return the unique */
PHP_FUNCTION(uniquechars)
{
	char *input = NULL;
	int argc = ZEND_NUM_ARGS();
	int input_len;
	zend_bool case_sensitive;
	char* workbuf;
	int index, work_index;
	if (zend_parse_parameters(argc TSRMLS_CC, "s|b", &input, &input_len, &case_sensitive) == FAILURE) 
		return;
	if ( argc == 1 ) {
		case_sensitive = 1;
	}
	work_index = 0 ;
	workbuf = (char*) emalloc(input_len + 1);
	memset( workbuf, 0, input_len + 1 );
	for ( index = 0; index<input_len; index++) {
		if( case_sensitive ) {
			if( !strchr(workbuf, input[index]) ){
				workbuf[work_index] = input[index];
				work_index++;
			}
		} else {
			if( !strchr(workbuf,tolower(input[index]))) {
				workbuf[work_index] = input[index];
				work_index++;
			}	 
			
		}
	}
	array_init( return_value );	//init return to array
	for(index = 0; index < input_len; index++) {
		if(workbuf[index] != '\0') {
			add_next_index_stringl(return_value, &workbuf[index],1,1);
		}
	}
	efree(workbuf);
}



/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */

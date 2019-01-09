/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2018 The PHP Group                                |
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

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_jiaozi.h"

/* If you declare any globals in php_jiaozi.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(jiaozi)
*/

/* True global resources - no need for thread safety here */
static int le_jiaozi;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("jiaozi.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_jiaozi_globals, jiaozi_globals)
    STD_PHP_INI_ENTRY("jiaozi.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_jiaozi_globals, jiaozi_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_jiaozi_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_jiaozi_compiled)
{
	char *arg = NULL;
	size_t arg_len, len;
	zend_string *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	strg = strpprintf(0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "jiaozi", arg);

	RETURN_STR(strg);
}

//
PHP_FUNCTION(jiaozi_write)
{
	char *arg = NULL;
	size_t arg_len, len;
	zend_string *strg;

	zend_string *filename;
	zend_string *content;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(filename)
		Z_PARAM_STR(content)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_STR(filename);

	strg = strpprintf(0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "jiaozi", arg);

	RETURN_STR(strg);
}

ZEND_METHOD(fucker, getName) {
    zend_string *ret = zend_string_init("hello world", 11, 0);
    RETURN_STR(ret);
}



/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_jiaozi_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_jiaozi_init_globals(zend_jiaozi_globals *jiaozi_globals)
{
	jiaozi_globals->global_value = 0;
	jiaozi_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(jiaozi)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(jiaozi)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */


/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(jiaozi)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(jiaozi)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "jiaozi support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ jiaozi_functions[]
 *
 * Every user visible function must have an entry in jiaozi_functions[].
 */
const zend_function_entry jiaozi_functions[] = {
	PHP_FE(confirm_jiaozi_compiled,	NULL)
	PHP_FE(jiaozi_write,	NULL)
	PHP_FE_END	/* Must be the last line in jiaozi_functions[] */
};

const zend_function_entry fucker_functions[] = {
    PHP_ME(fucker, getName, NULL, 0)
    PHP_FE_END
};

/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(jiaozi)
{
#if defined(COMPILE_DL_JIAOZI) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

    zend_class_entry class_entry;
    INIT_CLASS_ENTRY(class_entry, "fucker", fucker_functions);
    zend_register_internal_class_ex(&class_entry, NULL);

	return SUCCESS;
}
/* }}} */

/* {{{ jiaozi_module_entry
 */
// 这个变量必需是 xxx_module_entry. 与ZEND_GET_MODULE对应
// 如果是静态编译, 这个变量会以外部变量的形式被内联到PHP内部
// 如果是动态编译, 这个变量会以get_module方法的形式导出.
zend_module_entry jiaozi_module_entry = {
	STANDARD_MODULE_HEADER,
	"jiaozi",
	jiaozi_functions,
	PHP_MINIT(jiaozi),
	PHP_MSHUTDOWN(jiaozi),
	PHP_RINIT(jiaozi),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(jiaozi),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(jiaozi),
	PHP_JIAOZI_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_JIAOZI
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
// 导出一个 get_module 方法.
ZEND_GET_MODULE(jiaozi)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */

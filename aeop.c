/* aeop extension for PHP */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_aeop.h"

/* For compatibility with older PHP versions */
#ifndef ZEND_PARSE_PARAMETERS_NONE
#define ZEND_PARSE_PARAMETERS_NONE() \
	ZEND_PARSE_PARAMETERS_START(0, 0) \
	ZEND_PARSE_PARAMETERS_END()
#endif


PHP_MINIT_FUNCTION(aeop)
{
    printf("Module aeop init");
}

/* request init 函数
 */
PHP_RINIT_FUNCTION(aeop)
{
#if defined(ZTS) && defined(COMPILE_DL_AEOP)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	return SUCCESS;
}

PHP_RSHUTDOWN_FUNCTION(aeop)
{
    printf("request shutdown");
}

PHP_MSHUTDOWN_FUNCTION(aeop)
{
    printf("Module shutdown");
}

/* }}} */

/* module init 函数
 */
PHP_MINFO_FUNCTION(aeop)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "aeop support", "enabled");
	php_info_print_table_end();
}

PHP_FUNCTION(start_pool)
{
    zval * param;
    if (zend_parse_parameter(ZEND_NUM_ARGS() TSRMLS_CACHE, param, "l")) {
        RETURN_NULL();
    }

    RETURN_TRUE;
}
/* }}} */

/*
 */
ZEND_BEGIN_ARG_INFO(arginfo_aeop_test1, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_aeop_test2, 0)
	ZEND_ARG_INFO(0, str)
ZEND_END_ARG_INFO()
/* }}} */

/* {{{ aeop_functions[]
 */
static const zend_function_entry aeop_functions[] = {
	PHP_FE_END
};
/* }}} */

/* {{{ aeop_module_entry
 */
zend_module_entry aeop_module_entry = {
	STANDARD_MODULE_HEADER,
	"aeop",					/* Extension name */
	aeop_functions,			/* zend_function_entry */
	NULL,							/* PHP_MINIT - Module initialization */
	NULL,							/* PHP_MSHUTDOWN - Module shutdown */
	PHP_RINIT(aeop),			/* PHP_RINIT - Request initialization */
	NULL,							/* PHP_RSHUTDOWN - Request shutdown */
	PHP_MINFO(aeop),			/* PHP_MINFO - Module info */
	PHP_AEOP_VERSION,		/* Version */
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_AEOP
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(aeop)
#endif

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


static zend_function_entry class_methods[] = {
    {NULL, NULL, NULL}
};

zend_class_entry * class;



PHP_MINIT_FUNCTION(aeop)
{
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "MyClass", class_methods);
    class = zend_register_internal_class(&ce TSRMLS_CACHE);
    zend_declare_property(&ce, "name", sizeof("name"), NULL, ZEND_ACC_PUBLIC);
    printf("Module aeop init");
}

ZEND_METHOD(MyClass, __construct)
{
    printf("oh it is a new MyClass!");
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

/**
 * aeop($title, $message);
 * @param execute_data
 * @param return_value
 */
PHP_FUNCTION(aeop_test)
{
    char * title;
    int titleLength;
    char * message;
    int messageLength;

    if (zend_parse_parameter(ZEND_NUM_ARGS() TSRMLS_CACHE, "ss", &title, &titleLength, &message, &messageLength) == FAILURE) {
        RETURN_NULL();
    }
    HashTable * hs;
    ALLOC_HASHTABLE(hs);
    zend_hash_init(hs, 16, NULL, hashTableDestructor, 0);
    zend_string * key = zend_string_init("abc", sizeof("abc"), 0);
    zval * data = emalloc(sizeof(long));
    ZVAL_LONG(data, 123412423);
    zend_hash_add(hs, key, data);

    char * string;
    if (sprintf("%s%s", string, title, message) == 0) {
        RETURN_NULL();
    }
    php_printf("%s", string);
    RETURN_TRUE;
}


void hashTableDestructor(void * element)
{

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

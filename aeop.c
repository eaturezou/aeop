/* aeop extension for PHP */

#ifdef HAVE_CONFIG_H
#include "config.h"
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

    ZEND_METHOD(MyClass, __construct)
    {
        php_printf("oh it is a new MyClass!\n");
    }

    /* +---------------------------------
     * | SortTree
     * +---------------------------------
     */
    ZEND_METHOD(AeopSortTree, __construct)
    {
        php_printf("oh it is a new MyClass!\n");
    }

    ZEND_METHOD(AeopSortTree, minSort)
    {

    }

    ZEND_METHOD(AeopSortTree, maxSort)
    {

    }

    ZEND_METHOD(AeopSortTree, find)
    {

    }

    /* +---------------------------------
     * | SortTreeNode
     * +---------------------------------
     */
    ZEND_METHOD(AeopSortTreeNode, __construct)
    {

    }

    ZEND_METHOD(AeopSortTreeNode, getData)
    {

    }

    ZEND_METHOD(AeopSortTreeNode, getLeftChild)
    {

    }

    ZEND_METHOD(AeopSortTreeNode, getRightChild)
    {

    }

    ZEND_METHOD(AeopSortTreeNode, isLeaf)
    {

    }


    static zend_function_entry class_methods[] = {
        ZEND_ME(MyClass, __construct, NULL, ZEND_ACC_PUBLIC)
    };

	static zend_function_entry sort_tree_methods[] = {
            ZEND_ME(AeopSortTree, __construct, NULL, ZEND_ACC_PUBLIC)
	        ZEND_ME(AeopSortTree, minSort, NULL, ZEND_ACC_PUBLIC)
	        ZEND_ME(AeopSortTree, maxSort, NULL, ZEND_ACC_PUBLIC)
	        ZEND_ME(AeopSortTree, find, NULL, ZEND_ACC_PUBLIC)
	};

	static zend_function_entry sort_tree_node_methods[] = {
            ZEND_ME(AeopSortTreeNode, __construct, NULL, ZEND_ACC_PUBLIC)
            ZEND_ME(AeopSortTreeNode, getData, NULL, ZEND_ACC_PUBLIC)
            ZEND_ME(AeopSortTreeNode, getLeftChild, NULL, ZEND_ACC_PUBLIC)
            ZEND_ME(AeopSortTreeNode, getRightChild, NULL, ZEND_ACC_PUBLIC)
            ZEND_ME(AeopSortTreeNode, isLeaf, NULL, ZEND_ACC_PUBLIC)
	};


PHP_MINIT_FUNCTION(aeop)
{
    zend_class_entry ce, sort_tree, sort_tree_node;
    INIT_CLASS_ENTRY(ce, "AeopWorker", class_methods);
    INIT_CLASS_ENTRY(sort_tree, "AeopSortTree", sort_tree_methods)
    INIT_CLASS_ENTRY(sort_tree_node, "AeopSortTreeNode", sort_tree_node_methods)
    zend_register_internal_class(&ce);
    zend_register_internal_class(&sort_tree);
    zend_register_internal_class(&sort_tree_node);

    zval *sort_tree_length = emalloc(sizeof(zval));
    zval *sort_tree_height = emalloc(sizeof(zval));
    zval *sort_tree_tree = emalloc(sizeof(zval));

    zend_declare_property(&sort_tree, "length", sizeof(zval), sort_tree_length, ZEND_ACC_PROTECTED);
    zend_declare_property(&sort_tree, "height", sizeof(zval), sort_tree_height, ZEND_ACC_PROTECTED);
    zend_declare_property(&sort_tree, "tree", sizeof(zval), sort_tree_tree, ZEND_ACC_PROTECTED);


    return SUCCESS;
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
    php_printf("request shutdown");
}

PHP_MSHUTDOWN_FUNCTION(aeop)
{
    php_printf("Module shutdown");
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
    HashTable * hs;
    ALLOC_HASHTABLE(hs);
    zend_hash_init(hs, 16, NULL, (void*)hashTableDestructor, 0);
    zend_string * key = zend_string_init("abc", sizeof("abc"), 0);
    zval * data = emalloc(sizeof(long));
    ZVAL_LONG(data, 123412423);
    zend_hash_add(hs, key, data);
    php_printf("Hello World");
    RETURN_TRUE;
}


void hashTableDestructor(void * element)
{

}
/* }}} */

/*
 */
ZEND_BEGIN_ARG_INFO(arginfo_aeop_aeop_test, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO(arginfo_aeop_test2, 0)
	ZEND_ARG_INFO(0, str)
ZEND_END_ARG_INFO()
/* }}} */

/* {{{ aeop_functions[]
 */
static const zend_function_entry aeop_functions[] = {
	PHP_FE(aeop_test, arginfo_aeop_aeop_test)
	PHP_FE_END
};
/* }}} */

/* define aeop extension
 */
zend_module_entry aeop_module_entry = {
	STANDARD_MODULE_HEADER,
	"aeop",					/* Extension name */
	aeop_functions,			/* zend_function_entry */
    PHP_MINIT(aeop),							/* PHP_MINIT - Module initialization */
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

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

	void start_pthread()
	{

	}

    /* +---------------------------------
     * | AeopPool
     * +---------------------------------
     */

    //AeopPool::__construct
    ZEND_BEGIN_ARG_INFO(aeop_pool_ctor_info, NULL)
        ZEND_ARG_INFO(0, task_num)
        ZEND_ARG_INFO(0, master_name)
    ZEND_END_ARG_INFO()
    ZEND_METHOD(AeopPool, __construct)
    {
    	zend_long task_num;
    	zend_string* master_name;
    	if (zend_parse_parameters(ZEND_NUM_ARGS(), "lS", &task_num, &master_name) == FAILURE) {
    		//todo throw exception
    		RETURN_FALSE;
    	}
		struct poolMaster* master = (struct poolMaster*)emalloc(sizeof(struct poolMaster) + task_num * sizeof(ThreadItem));
    	master->thread_num = task_num;
    	master->pool_name = master_name->val;
    	while (task_num -- > 0) {
			pthread_t t;
			int argument;
			if (pthread_create(&t, NULL, (void *)&start_pthread, (void *)&argument) < 0) {
				//todo throw exception
			}
			ThreadItem* threadItem = (ThreadItem *)emalloc(sizeof(ThreadItem));
			threadItem->thread_id = t;
			threadItem->status = THREAD_SLEEP;
			master->pool_name ++;
			master->thread[master->thread_num - 1] = threadItem;
    	}

    }

    //AeopPool::addTask
    ZEND_BEGIN_ARG_INFO(aeop_pool_add_task_info, NULL)
    	ZEND_ARG_INFO(FALSE, callback)
    ZEND_END_ARG_INFO()
    ZEND_METHOD(AeopPool, addTask)
	{
    	zend_fcall_info callback;
    	zend_fcall_info_cache callback_cache;
    	if (zend_parse_parameters(ZEND_NUM_ARGS(), "f", &callback, &callback_cache) == FAILURE) {
    		//todo throw exception
    		RETURN_FALSE;
    	}

	}

	static const zend_function_entry sort_tree_node_methods[] = {
            ZEND_ME(AeopPool, __construct, aeop_pool_ctor_info, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
            ZEND_ME(AeopPool, addTask, aeop_pool_add_task_info, ZEND_ACC_PUBLIC)
            ZEND_FE_END
	};


PHP_MINIT_FUNCTION(aeop)
{
    zend_class_entry sort_tree_node;
    INIT_CLASS_ENTRY(sort_tree_node, "AeopPool", sort_tree_node_methods)
    zend_register_internal_class(&sort_tree_node);


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

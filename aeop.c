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

    static zend_class_entry * aeop_pool;

	void handler_sigchld()
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
    	zend_long work_num;
    	zend_string* master_name;
    	if (zend_parse_parameters(ZEND_NUM_ARGS(), "lS", &work_num, &master_name) == FAILURE) {
    		RETURN_FALSE;
    	}
    	if (work_num <= 0) {
    	    work_num = 4;
    	}
        //magner process
        struct poolMaster* master = (struct poolMaster*)emalloc(sizeof(struct poolMaster) + work_num * sizeof(ThreadItem));
        master->thread_num = work_num;
        master->pool_name = master_name->val;
        zend_declare_property_long(aeop_pool, "work_num", sizeof(zend_long), work_num, ZEND_ACC_PRIVATE);
        zend_declare_property_string(aeop_pool, "master_name", sizeof(zend_string), master_name->val, ZEND_ACC_PRIVATE);
    }

    ZEND_BEGIN_ARG_INFO(aeop_pool_run_info, NULL)
    ZEND_END_ARG_INFO()
    ZEND_METHOD(AeopPool, run)
    {
        signal(SIGCHLD, (void *)handler_sigchld);
        prctl(PR_SET_NAME, "master", NULL, NULL, NULL);

        zval *work_num_val = emalloc(sizeof(zval));
        zend_read_property(aeop_pool, getThis(), "work_name", sizeof("work_name")-1, TRUE, work_num_val);
        //master process
        pid_t pid;
        pid = fork();
        if (pid < 0) {
            php_error_docref(NULL, E_ERROR, "create master process error");
            RETURN_FALSE;
        } else if (pid > 0) {
            pause();
        } else {
            zend_long work_num = zval_get_long(work_num_val);
            for (int i = 0; i < work_num; i ++) {
                pid_t work_pid;
                work_pid = fork();
                if (work_pid > 0) {
                    break;
                } else if (work_pid < 0) {
                    php_error_docref(NULL, E_ERROR, "create worker process error");
                    RETURN_FALSE;
                } else {
                    prctl(PR_SET_NAME, "master", NULL, NULL, NULL);
                    while (TRUE) {
                        php_printf("Hello World");
                    }
                }
            }
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
            ZEND_ME(AeopPool, run, aeop_pool_run_info, ZEND_ACC_PUBLIC)
            ZEND_ME(AeopPool, addTask, aeop_pool_add_task_info, ZEND_ACC_PUBLIC)
            ZEND_FE_END
	};


PHP_MINIT_FUNCTION(aeop)
{
    zend_class_entry sort_tree_node;
    INIT_CLASS_ENTRY(sort_tree_node, "AeopPool", sort_tree_node_methods)
    aeop_pool = zend_register_internal_class(&sort_tree_node);


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

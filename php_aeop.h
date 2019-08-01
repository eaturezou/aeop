/* aeop extension for PHP */

#ifndef PHP_AEOP_H
# define PHP_AEOP_H

extern zend_module_entry aeop_module_entry;
# define phpext_aeop_ptr &aeop_module_entry

#include <pthread.h>

# define PHP_AEOP_VERSION "0.1.0"
#define THREAD_SLEEP 0
#define THREAD_WORKING 1
#define THREAD_DEAD 2

#define TRUE 1
#define FALSE 0

struct thread {
    pthread_t thread_id;
    int status;
};

typedef struct thread ThreadItem;

struct poolMaster {
    long thread_num;
    char* pool_name;
    ThreadItem* thread[1];
};


# if defined(ZTS) && defined(COMPILE_DL_AEOP)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

void hashTableDestructor(void * element);

#endif	/* PHP_AEOP_H */
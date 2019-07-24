/* aeop extension for PHP */

#ifndef PHP_AEOP_H
# define PHP_AEOP_H

extern zend_module_entry aeop_module_entry;
# define phpext_aeop_ptr &aeop_module_entry

# define PHP_AEOP_VERSION "0.1.0"

# if defined(ZTS) && defined(COMPILE_DL_AEOP)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

void hashTableDestructor(void * element);

#endif	/* PHP_AEOP_H */
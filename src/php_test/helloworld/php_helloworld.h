/* helloworld extension for PHP */

#ifndef PHP_HELLOWORLD_H
# define PHP_HELLOWORLD_H

extern zend_module_entry helloworld_module_entry;
# define phpext_helloworld_ptr &helloworld_module_entry

# define PHP_HELLOWORLD_VERSION "0.1.0"

# if defined(ZTS) && defined(COMPILE_DL_HELLOWORLD)
ZEND_TSRMLS_CACHE_EXTERN()
# endif

#endif	/* PHP_HELLOWORLD_H */

PHP_FUNCTION(hello);


#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php_rdns.h"

#define PHP_RDNS_VERSION "0.1.0"
#define PHP_RDNS_EXTNAME "RDNS"

static zend_class_entry *rdns_ce = NULL;

extern zend_module_entry rdns_module_entry;
#define phpext_rdns_ptr &rdns_module_entry

static PHP_METHOD(RDNS, __construct);
static PHP_METHOD(RDNS, addServer);
static PHP_METHOD(RDNS, addRequest);
static PHP_METHOD(RDNS, getReplies);

#define RDNS_ME(name, args) PHP_ME(RDNS, name, args, ZEND_ACC_PUBLIC)
static zend_function_entry rdns_class_methods[] = {
  /* RDNS_ME(__construct, arginfo___construct) */
  RDNS_ME(__construct, NULL)
  RDNS_ME(addServer,   NULL)
  RDNS_ME(addRequest,  NULL)
  RDNS_ME(getReplies,  NULL)
  PHP_FE_END
};
#undef RDNS_ME
/* }}} */

// the following code creates an entry for the module and registers it with Zend.
zend_module_entry rdns_module_entry = {
#if ZEND_MODULE_API_NO >= 20050922
  STANDARD_MODULE_HEADER_EX,
  NULL,
  NULL,
#else
  STANDARD_MODULE_HEADER,
#endif
  PHP_RDNS_EXTNAME,
  NULL,
  PHP_MINIT(rdns),
  NULL, // SHUTDOWN
  NULL, // name of the RINIT function or NULL if not applicable
  NULL, // name of the RSHUTDOWN function or NULL if not applicable
  PHP_MINFO(rdns),
  PHP_RDNS_VERSION,
  STANDARD_MODULE_PROPERTIES
};

ZEND_GET_MODULE(rdns)

/* {{{ RDNS::__construct() */
static PHP_METHOD(RDNS, __construct)
{
  zval *object = getThis();
}
/* }}} */


/* {{{ RDNS::addServer(string $server [, int $port = 53 [, int $prio = 0 ] ]) */
static PHP_METHOD(RDNS, addServer)
{
  /* TODO: implement */
  RETURN_FALSE;
}
/* }}} */


/* {{{ RDNS::addRequest(string $hostname, int $type, float $timeout) */
static PHP_METHOD(RDNS, addRequest)
{
  /* TODO: implement */
  RETURN_FALSE;
}
/* }}} */


/* {{{ RDNS::getReplies() */
static PHP_METHOD(RDNS, getReplies)
{
  /* TODO: implement */
  RETURN_FALSE;
}
/* }}} */


/* {{{ PHP_MINIT_FUNCTION */
static PHP_MINIT_FUNCTION(rdns)
{
  zend_class_entry ce;
  INIT_CLASS_ENTRY(ce, "RDNS", rdns_class_methods);
  rdns_ce = zend_register_internal_class(&ce TSRMLS_CC);
  /* rdns_ce->create_object = php_rdns_new; */

  return SUCCESS;
}
/* }}} */


/* {{{ PHP_MINIT_FUNCTION */
static PHP_MINFO_FUNCTION(rdns)
{
  php_info_print_table_start();
  php_info_print_table_header(2, "RDNS Support", "enabled");
  php_info_print_table_header(2, "RDNS GitHub", "http://github.com/weheartwebsites/php-rdns");
  php_info_print_table_row(2, "RDNS Version", PHP_RDNS_VERSION);
  php_info_print_table_row(2, "RDNS librdns", "44e4c9ba12d2504379443e7f7a7f94ad088a28e3");
  php_info_print_table_end();
}
/* }}} */

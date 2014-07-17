#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>

#include "php_rdns.h"


#define PHP_RDNS_VERSION "0.1.0"
#define PHP_RDNS_EXTNAME "RDNS"

static zend_class_entry *rdns_ce = NULL;

extern zend_module_entry rdns_module_entry;
#define phpext_rdns_ptr &rdns_module_entry

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

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(rdns)
{
  return SUCCESS;
}
/* {{{ PHP_MINIT_FUNCTION */
PHP_MINFO_FUNCTION(rdns)
{
  php_info_print_table_start();
  php_info_print_table_header(2, "RDNS Support", "enabled");
  php_info_print_table_header(2, "RDNS GitHub", "http://github.com/weheartwebsites/php-rdns");
  php_info_print_table_row(2, "RDNS Version", PHP_RDNS_VERSION);
  php_info_print_table_row(2, "RDNS librdns", "44e4c9ba12d2504379443e7f7a7f94ad088a28e3");
  php_info_print_table_end();
}

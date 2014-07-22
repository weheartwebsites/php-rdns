#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>
#include "rdns_ev.h"

#define PHP_RDNS_VERSION "0.1.0"
#define PHP_RDNS_EXTNAME "RDNS"

#define RDNS_INIT_VARS                          \
  zval *object = getThis();                     \
  php_rdns_t *i_obj = NULL;

#define RDNS_FETCH_OBJECT                                                  \
  i_obj = (php_rdns_t *) zend_object_store_get_object( object TSRMLS_CC );

typedef struct {
  zend_object obj;
  struct ev_loop *loop;
  struct rdns_resolver *resolver;
} php_rdns_t;

static zend_class_entry *rdns_ce = NULL;

extern zend_module_entry rdns_module_entry;
#define phpext_rdns_ptr &rdns_module_entry

static PHP_METHOD(RDNS, __construct);
static PHP_METHOD(RDNS, addServer);
static PHP_METHOD(RDNS, addRequest);
static PHP_METHOD(RDNS, getReplies);

ZEND_BEGIN_ARG_INFO_EX(arginfo_addServer, 0, 0, 1)
  ZEND_ARG_INFO(0, server)
  ZEND_ARG_INFO(0, port)
  ZEND_ARG_INFO(0, prio)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_addRequest, 0, 0, 3)
  ZEND_ARG_INFO(0, hostname)
  ZEND_ARG_INFO(0, type)
  ZEND_ARG_INFO(0, timeout)
ZEND_END_ARG_INFO()

static zend_function_entry rdns_class_methods[] = {
  PHP_ME(RDNS, __construct, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
  PHP_ME(RDNS, addServer,   arginfo_addServer, ZEND_ACC_PUBLIC)
  PHP_ME(RDNS, addRequest,  arginfo_addRequest, ZEND_ACC_PUBLIC)
  PHP_ME(RDNS, getReplies,  NULL, ZEND_ACC_PUBLIC)
  PHP_FE_END
};
/* }}} */

static void php_rdns_free(php_rdns_t *i_obj TSRMLS_DC)
{
  zend_object_std_dtor(&i_obj->obj TSRMLS_CC);
  rdns_resolver_release(i_obj->resolver);
  efree(i_obj);
}

static zend_object_value
php_rdns_new(zend_class_entry *ce TSRMLS_DC)
{
  zend_object_value retval;
  php_rdns_t *i_obj;
  zval *tmp;

  i_obj = ecalloc(1, sizeof(*i_obj));
  zend_object_std_init(&i_obj->obj, ce TSRMLS_CC );

  retval.handle = zend_objects_store_put(i_obj,
                                         (zend_objects_store_dtor_t)
                                         zend_objects_destroy_object,
                                         (zend_objects_free_object_storage_t)
                                         php_rdns_free, NULL TSRMLS_CC);
  retval.handlers = zend_get_std_object_handlers();

  return retval;
}

/* {{{ PHP_MINIT_FUNCTION */
static PHP_MINIT_FUNCTION(rdns)
{
  zend_class_entry ce;
  INIT_CLASS_ENTRY(ce, PHP_RDNS_EXTNAME, rdns_class_methods);
  rdns_ce = zend_register_internal_class(&ce TSRMLS_CC);
  rdns_ce->create_object = php_rdns_new;

  return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINIT_FUNCTION */
static PHP_MINFO_FUNCTION(rdns)
{
  php_info_print_table_start();
  php_info_print_table_header(2, "RDNS Support", "enabled");
  php_info_print_table_row(2, "RDNS Version", PHP_RDNS_VERSION);
  php_info_print_table_row(2, "RDNS GitHub", "http://github.com/weheartwebsites/php-rdns");
  php_info_print_table_row(2, "RDNS librdns", "44e4c9ba12d2504379443e7f7a7f94ad088a28e3");
  php_info_print_table_end();
}
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

#ifdef COMPILE_DL_RDNS
ZEND_GET_MODULE(rdns)
#endif

/* {{{ RDNS::__construct() */
static PHP_METHOD(RDNS, __construct)
{
  zval *object = getThis();
  php_rdns_t *i_obj = NULL;

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
    ZVALL_NULL(object);
    return;
  }

  i_obj = (php_rdns_t *) zend_object_store_get_object(object TSRMLS_CC);
  if (!(i_obj->resolver = rdns_resolver_new())) {
    php_error_docref(NULL TSRMLS_CC, E_ERROR, "could not create resolver structure");
  }

  i_obj->loop = ev_default_loop(0);
  rdns_bind_libev(i_obj->resolver, i_obj->loop);
}
/* }}} */


/* {{{ bool RDNS::addServer(string $server [, int $port = 53 [, int $prio = 0 ] ]) */
static PHP_METHOD(RDNS, addServer)
{
  char *server;
  size_t server_len;
  long port = 53, prio = 0;

  RDNS_INIT_VARS;

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s|ll",
                            &server, &server_len, &port, &prio) == FAILURE) {
    return;
  }

  RDNS_FETCH_OBJECT;

  RETURN_BOOL(rdns_resolver_add_server(i_obj->resolver, server, port, prio, 8));
}
/* }}} */


/* {{{ RDNS::addRequest(string $hostname, int $type, float $timeout) */
static PHP_METHOD(RDNS, addRequest)
{
  char *hostname;
  size_t hostname_len;
  long type, timeout;

  RDNS_INIT_VARS;

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sll",
                            &hostname, &hostname_len, &type, &timeout) == FAILURE) {
    ZVALL_NULL(object);
    return;
  }

  php_printf("%s %ld %ld\n", hostname, type, timeout);

  RDNS_FETCH_OBJECT;

  RETURN_FALSE;
}
/* }}} */


/* {{{ array RDNS::getReplies() */
static PHP_METHOD(RDNS, getReplies)
{
  RDNS_INIT_VARS;

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "") == FAILURE) {
    return;
  }

  RDNS_FETCH_OBJECT;

  array_init(return_value);
}
/* }}} */

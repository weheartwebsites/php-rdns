/*
  +----------------------------------------------------------------------+
  | Copyright (c) 2014 weheartwebsites UG                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 2 of the Apache license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.apache.org/licenses/LICENSE-2.0.html                      |
  +----------------------------------------------------------------------+
  | Authors: Alexander Solovets <asolovets@gmail.com>                    |
  |          Eduardo Silva <eduardo@monkey.io>                           |
  |          Gunter Grodotzki <guenter@weheartwebsites.de>               |
  +----------------------------------------------------------------------+
*/

#ifndef PHP_RDNS_H
#define PHP_RDNS_H

extern zend_module_entry rdns_module_entry;
#define phpext_rdns_ptr &rdns_module_entry

#ifdef ZTS
#include "TSRM.h"
#endif

#define PHP_RDNS_VERSION "0.1.2"
#define PHP_RDNS_EXTNAME "RDNS"

#endif   /* PHP_RDNS_H */

dnl $ Id: $
dnl config.m4 for extension rdns

PHP_ARG_WITH(rdns, for rdns support,
[  --with-rdns             Include RDNS support])

if test -z "$PHP_DEBUG"; then
  AC_ARG_ENABLE(debug,
  [  --enable-debug          compile with debugging symbols],[
    PHP_DEBUG=$enableval
  ],[    PHP_DEBUG=no
  ])
fi

if test "$PHP_RDNS" = "yes"; then
  PHP_ADD_INCLUDE(librdns/include)
  PHP_ADD_INCLUDE(librdns/contrib/uthash)
  PHP_ADD_INCLUDE(librdns/contrib/libottery)

  AC_DEFINE(HAVE_RDNS, 1, [Whether you have RDNS])

  PHP_RDNS_SOURCES=rdns.c

  PHP_RDNS_SOURCES="${PHP_RDNS_SOURCES} librdns/src/compression.c"
  PHP_RDNS_SOURCES="${PHP_RDNS_SOURCES} librdns/src/curve.c"
  PHP_RDNS_SOURCES="${PHP_RDNS_SOURCES} librdns/src/logger.c"
  PHP_RDNS_SOURCES="${PHP_RDNS_SOURCES} librdns/src/packet.c"
  PHP_RDNS_SOURCES="${PHP_RDNS_SOURCES} librdns/src/parse.c"
  PHP_RDNS_SOURCES="${PHP_RDNS_SOURCES} librdns/src/punycode.c"
  PHP_RDNS_SOURCES="${PHP_RDNS_SOURCES} librdns/src/resolver.c"
  PHP_RDNS_SOURCES="${PHP_RDNS_SOURCES} librdns/src/util.c"

  PHP_RDNS_SOURCES="${PHP_RDNS_SOURCES} librdns/contrib/libottery/chacha_merged.c"
  PHP_RDNS_SOURCES="${PHP_RDNS_SOURCES} librdns/contrib/libottery/ottery.c"
  PHP_RDNS_SOURCES="${PHP_RDNS_SOURCES} librdns/contrib/libottery/ottery_cpuinfo.c"
  PHP_RDNS_SOURCES="${PHP_RDNS_SOURCES} librdns/contrib/libottery/ottery_entropy.c"
  PHP_RDNS_SOURCES="${PHP_RDNS_SOURCES} librdns/contrib/libottery/ottery_global.c"

  PHP_ADD_LIBRARY(ev, 1, RDNS_SHARED_LIBADD)
  PHP_SUBST(RDNS_SHARED_LIBADD)
  PHP_NEW_EXTENSION(rdns, $PHP_RDNS_SOURCES, $ext_shared)
fi

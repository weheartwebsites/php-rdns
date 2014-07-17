dnl
dnl $ Id: $

PHP_ARG_ENABLE(rdns, whether to enable rdns,
[  --enable-rdns           Enable RDNS])

if test -z "$PHP_DEBUG"; then
  AC_ARG_ENABLE(debug,
  [  --enable-debug          compile with debugging symbols],[
    PHP_DEBUG=$enableval
  ],[    PHP_DEBUG=no
  ])
fi

if test "$PHP_RDNS" = "yes"; then
  AC_DEFINE(HAVE_RDNS, 1, [Whether you have RDNS])
  PHP_NEW_EXTENSION(rdns, rdns.c, $ext_shared)
fi

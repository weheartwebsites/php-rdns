--TEST--
Check if RDNS class can be instantiated
--SKIPIF--
<?php if (!extension_loaded("rdns")) print "skip"; ?>
--FILE--
<?php
$rdns = new RDNS;
$rdns->addServer('php.net');
$rdns->addServer('php.net', 42);
$rdns->addServer('php.net', 42, 101);
$rdns->addRequest('php.org', 43, 102);
$rdns->getReplies();
?>
--EXPECT--
php.net 53 0
php.net 42 0
php.net 42 101
php.org 43 102

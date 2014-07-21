--TEST--
Check RDNS::addServer
--SKIPIF--
<?php if (!extension_loaded("rdns")) print "skip"; ?>
--FILE--
<?php
$rdns = new RDNS;
# Valid addresses.
var_dump($rdns->addServer('127.0.0.1'));
var_dump($rdns->addServer('8.8.8.8', 53));
var_dump($rdns->addServer('208.67.222.222', 53, 1));
# Invalid addresses.
var_dump($rdns->addServer('1.2.3'));
?>
--EXPECT--
bool(true)
bool(true)
bool(true)
bool(false)

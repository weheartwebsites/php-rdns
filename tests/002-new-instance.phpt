--TEST--
Check if RDNS class can be instantiated
--SKIPIF--
<?php if (!extension_loaded("rdns")) print "skip"; ?>
--FILE--
<?php
$rdns = new RDNS;
$rdns->addServer();
$rdns->addRequest();
$rdns->getReplies();
?>
--EXPECT--
